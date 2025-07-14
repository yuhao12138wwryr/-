from collections import OrderedDict
import torch
from einops.layers.torch import Rearrange, Reduce
from einops import rearrange
import torch.nn as nn
import torch.nn.functional as F
from utils.batchrenorm import BatchRenorm2d
from timm.models.layers import DropPath, to_2tuple, trunc_normal_
from models import module
from models import FCA
from models import upsample
import numpy as np
class PatchEmbed(nn.Module):
    r""" Image to Patch Embedding

    Args:
        img_size (int): Image size.  Default: 224.
        patch_size (int): Patch token size. Default: 4.
        in_chans (int): Number of input image channels. Default: 3.
        embed_dim (int): Number of linear projection output channels. Default: 96.
        norm_layer (nn.Module, optional): Normalization layer. Default: None
    """

    def __init__(self, img_size=224, patch_size=4, in_chans=3, embed_dim=96, norm_layer=None):
        super().__init__()
        img_size = to_2tuple(img_size)
        patch_size = to_2tuple(patch_size)
        patches_resolution = [img_size[0] // patch_size[0], img_size[1] // patch_size[1]]
        self.img_size = img_size
        self.patch_size = patch_size
        self.patches_resolution = patches_resolution
        self.num_patches = patches_resolution[0] * patches_resolution[1]

        self.in_chans = in_chans
        self.embed_dim = embed_dim

        if norm_layer is not None:
            self.norm = norm_layer(embed_dim)
        else:
            self.norm = None

    def forward(self, x):
        x = x.flatten(2).transpose(1, 2)  # B Ph*Pw C
        if self.norm is not None:
            x = self.norm(x)
        return x

    def flops(self):
        flops = 0
        H, W = self.img_size
        if self.norm is not None:
            flops += H * W * self.embed_dim
        return flops

class PatchUnEmbed(nn.Module):
    r""" Image to Patch Unembedding

    Args:
        img_size (int): Image size.  Default: 224.
        patch_size (int): Patch token size. Default: 4.
        in_chans (int): Number of input image channels. Default: 3.
        embed_dim (int): Number of linear projection output channels. Default: 96.
        norm_layer (nn.Module, optional): Normalization layer. Default: None
    """

    def __init__(self, img_size=224, patch_size=4, in_chans=3, embed_dim=96, norm_layer=None):
        super().__init__()
        img_size = to_2tuple(img_size)
        patch_size = to_2tuple(patch_size)
        patches_resolution = [img_size[0] // patch_size[0], img_size[1] // patch_size[1]]
        self.img_size = img_size
        self.patch_size = patch_size
        self.patches_resolution = patches_resolution
        self.num_patches = patches_resolution[0] * patches_resolution[1]

        self.in_chans = in_chans
        self.embed_dim = embed_dim

    def forward(self, x, x_size):
        B, HW, C = x.shape
        x = x.transpose(1, 2).view(B, self.embed_dim, x_size[0], x_size[1])  # B Ph*Pw C
        return x

    def flops(self):
        flops = 0
        return flops
class Mlp(nn.Module):
    def __init__(self, in_features, hidden_features=None, out_features=None, act_layer=nn.GELU, drop=0.):
        super().__init__()
        out_features = out_features or in_features
        hidden_features = hidden_features or in_features
        self.fc1 = nn.Linear(in_features, hidden_features)
        self.act = act_layer()
        self.fc2 = nn.Linear(hidden_features, out_features)
        self.drop = nn.Dropout(drop)

    def forward(self, x):
        x = self.fc1(x)
        x = self.act(x)
        x = self.drop(x)
        x = self.fc2(x)
        x = self.drop(x)
        return x
# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))
# --------------------------------------------
class WindowAttention(nn.Module):
    r""" Window based multi-head self attention (W-MSA) module with relative position bias.
    It supports both of shifted and non-shifted window.

    Args:
        dim (int): Number of input channels.
        window_size (tuple[int]): The height and width of the window.
        num_heads (int): Number of attention heads.
        qkv_bias (bool, optional):  If True, add a learnable bias to query, key, value. Default: True
        qk_scale (float | None, optional): Override default qk scale of head_dim ** -0.5 if set
        attn_drop (float, optional): Dropout ratio of attention weight. Default: 0.0
        proj_drop (float, optional): Dropout ratio of output. Default: 0.0
    """

    def __init__(self, dim, window_size, num_heads, qkv_bias=True, qk_scale=None, attn_drop=0., proj_drop=0.):

        super().__init__()
        self.dim = dim
        self.window_size = window_size  # Wh, Ww
        self.num_heads = num_heads

        head_dim = dim // num_heads
        self.scale = qk_scale or head_dim ** -0.5

        # define a parameter table of relative position bias
        self.relative_position_bias_table = nn.Parameter(
            torch.zeros((2 * window_size[0] - 1) * (2 * window_size[1] - 1), num_heads))  # 2*Wh-1 * 2*Ww-1, nH

        # get pair-wise relative position index for each token inside the window
        coords_h = torch.arange(self.window_size[0])#行和列，都是0到7
        coords_w = torch.arange(self.window_size[1])

        coords = torch.stack(torch.meshgrid([coords_h, coords_w]))  # 2, Wh, Wwcoords 是一个包含两个坐标矩阵的张量，第一个矩阵表示行坐标，第二个矩阵表示列坐标，形状为 (2, 8, 8)
        coords_flatten = torch.flatten(coords, 1)  # 2, Wh*Ww战平([2, 64])，存储这64个数的横纵坐标
        relative_coords = coords_flatten[:, :, None] - coords_flatten[:, None, :]  # 2, Wh*Ww, Wh*Ww[2, 64, 64])
        relative_coords = relative_coords.permute(1, 2, 0).contiguous()  # Wh*Ww, Wh*Ww, 2
#因为采取的是相减，所以得到的索引是从负数开始的，我们加上偏移量，让其从0开始。
        relative_coords[:, :, 0] += self.window_size[0] - 1  # shift to start from 0
        relative_coords[:, :, 1] += self.window_size[1] - 1
        #通过将x,y坐标相加转换为一维偏移的时候，他的偏移量是相等的。
        #最后我们对其中做了个乘法操作，以进行区分,也就是区分0，2和2，0  把第1项乘10（2 *8-1）
        relative_coords[:, :, 0] *= 2 * self.window_size[1] - 1

        #最后一维上进行求和，展开成一个一维坐标，并注册为一个不参与网络学习的变量
        relative_position_index = relative_coords.sum(-1)  # Wh*Ww, Wh*Ww
        self.register_buffer("relative_position_index", relative_position_index)#138行使用了

        self.qkv = nn.Linear(dim, dim * 3, bias=qkv_bias)
        self.attn_drop = nn.Dropout(attn_drop)
        self.proj = nn.Linear(dim, dim)

        self.proj_drop = nn.Dropout(proj_drop)

        trunc_normal_(self.relative_position_bias_table, std=.02)
        self.softmax = nn.Softmax(dim=-1)


    def forward(self, x, mask=None):
        """
        Args:
            x: input features with shape of (num_windows*B, N, C)
            mask: (0/-inf) mask with shape of (num_windows, Wh*Ww, Wh*Ww) or None
        """
        B_, N, C = x.shape
#self.num_heads=6,x:[256, 64, 96]，256个8*8=128*128
        qkv = self.qkv(x)#[256, 64, 288]飞线性层1如3出

        qkv=qkv.reshape(B_, N, 3, self.num_heads, C // self.num_heads).permute(2, 0, 3, 1, 4)#到([3, 256, 6, 64, 16])num_heads=6，96/6=16，288拆个3出去的96，也就是6个头，3个qkv
        q, k, v = qkv[0], qkv[1], qkv[2]  # make torchscript happy (cannot use tensor as tuple)都是torch.Size([256, 6, 64, 16])

        q = q * self.scale# self.scale=0.25,形状不变

        attn = (q @ k.transpose(-2, -1)) #q 和 k 相乘后并交换最后两个维度([256, 6, 64, 64])

        relative_position_bias = self.relative_position_bias_table[self.relative_position_index.view(-1)].view(
            self.window_size[0] * self.window_size[1], self.window_size[0] * self.window_size[1], -1)  # Wh*Ww,Wh*Ww,nH，nH=6,Ww=8
        relative_position_bias = relative_position_bias.permute(2, 0, 1).contiguous()  # nH, Wh*Ww, Wh*Ww
        attn = attn + relative_position_bias.unsqueeze(0)#由qk的到的和初始化时位置编码的相加
        attn = self.mamba_layers(attn)





        if mask is not None:#mask=None
            nW = mask.shape[0]
            attn = attn.view(B_ // nW, nW, self.num_heads, N, N) + mask.unsqueeze(1).unsqueeze(0)
            attn = attn.view(-1, self.num_heads, N, N)
            attn = self.softmax(attn)
        else:
            attn = self.softmax(attn)#

        attn = self.attn_drop(attn)

        x = (attn @ v).transpose(1, 2).reshape(B_, N, C)
        x = self.proj(x)#线性层
        x = self.proj_drop(x)
        return x

    def extra_repr(self) -> str:
        return f'dim={self.dim}, window_size={self.window_size}, num_heads={self.num_heads}'

    def flops(self, N):
        # calculate flops for 1 window with token length of N
        flops = 0
        # qkv = self.qkv(x)
        flops += N * self.dim * 3 * self.dim
        # attn = (q @ k.transpose(-2, -1))
        flops += self.num_heads * N * (self.dim // self.num_heads) * N
        #  x = (attn @ v)
        flops += self.num_heads * N * N * (self.dim // self.num_heads)
        # x = self.proj(x)
        flops += N * self.dim * self.dim
        return flops





def sequential(*args):
    """Advanced nn.Sequential.

    Args:
        nn.Sequential, nn.Module

    Returns:
        nn.Sequential
    """
    if len(args) == 1:
        if isinstance(args[0], OrderedDict):
            raise NotImplementedError('sequential does not support OrderedDict input.')
        return args[0]  # No sequential is needed.
    modules = []
    for module in args:
        if isinstance(module, nn.Sequential):
            for submodule in module.children():
                modules.append(submodule)
        elif isinstance(module, nn.Module):
            modules.append(module)
    return nn.Sequential(*modules)


'''
# --------------------------------------------
# Useful blocks
# https://github.com/xinntao/BasicSR
# --------------------------------
# conv + normaliation + relu (conv)
# (PixelUnShuffle)
# (ConditionalBatchNorm2d)
# concat (ConcatBlock)
# sum (ShortcutBlock)
# resblock (ResBlock)
# Channel Attention (CA) Layer (CALayer)
# Residual Channel Attention Block (RCABlock)
# Residual Channel Attention Group (RCAGroup)
# Residual Dense Block (ResidualDenseBlock_5C)
# Residual in Residual Dense Block (RRDB)
# --------------------------------------------
'''


# --------------------------------------------
# return nn.Sequantial of (Conv + BN + ReLU)
# --------------------------------------------
# 膨胀卷积固定成了2
def conv(in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, dilation=2, mode='CBR', negative_slope=0.2):
    L = []
    for t in mode:
        if t == 'C':
            L.append(nn.Conv2d(in_channels=in_channels, out_channels=out_channels, kernel_size=kernel_size, stride=stride, padding=padding, bias=bias))
        elif t == 'T':
            L.append(nn.ConvTranspose2d(in_channels=in_channels, out_channels=out_channels, kernel_size=kernel_size, stride=stride, padding=padding, bias=bias))
        elif t == 'D': #膨胀卷积
            L.append(nn.Conv2d(in_channels=in_channels, out_channels=out_channels, kernel_size=kernel_size, stride=stride, padding=2, bias=bias,dilation=dilation))
        elif t == 'B':
            L.append(nn.BatchNorm2d(out_channels, momentum=0.9, eps=1e-04, affine=True))
        elif t == 'I':
            L.append(nn.InstanceNorm2d(out_channels, affine=True))
        elif t == 'R':
            L.append(nn.ReLU(inplace=True))
        elif t == 'r':
            L.append(nn.ReLU(inplace=False))
        elif t == 'L':
            L.append(nn.LeakyReLU(negative_slope=negative_slope, inplace=True))
        elif t == 'l':
            L.append(nn.LeakyReLU(negative_slope=negative_slope, inplace=False))
        elif t == '2':
            L.append(nn.PixelShuffle(upscale_factor=2))
        elif t == '3':
            L.append(nn.PixelShuffle(upscale_factor=3))
        elif t == '4':
            L.append(nn.PixelShuffle(upscale_factor=4))
        elif t == 'U':
            L.append(nn.Upsample(scale_factor=2, mode='nearest'))
        elif t == 'u':
            L.append(nn.Upsample(scale_factor=3, mode='nearest'))
        elif t == 'v':
            L.append(nn.Upsample(scale_factor=4, mode='nearest'))
        elif t == 'M':
            L.append(nn.MaxPool2d(kernel_size=kernel_size, stride=stride, padding=0))
        elif t == 'A':
            L.append(nn.AvgPool2d(kernel_size=kernel_size, stride=stride, padding=0))
        elif t == 'N': #BatchReNomal
            L.append(BatchRenorm2d(64))
        elif t == 'S':  # BatchReNomal
            L.append(nn.Sigmoid())
        elif t == '6':  # BatchReNomal
            L.append(nn.AdaptiveAvgPool2d(1))
            L.append(nn.Conv2d(64, 1, 1, bias=False))
            L.append(nn.ReLU())
        elif t == '7':  # BatchReNomal
            L.append(nn.AdaptiveMaxPool2d(1))
            L.append(nn.Conv2d(64, 1, 1, bias=False))
            L.append(nn.ReLU())

        else:
            raise NotImplementedError('Undefined type: '.format(t))
    return sequential(*L)

# 膨胀卷积固定成了2
def conv_cpu(in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, dilation=2, mode='CBR', negative_slope=0.2):
    L = []
    for t in mode:
        if t == 'C':
            L.append(nn.Conv2d(in_channels=in_channels, out_channels=out_channels, kernel_size=kernel_size, stride=stride, padding=padding, bias=bias).to("cpu"))
        elif t == 'T':
            L.append(nn.ConvTranspose2d(in_channels=in_channels, out_channels=out_channels, kernel_size=kernel_size, stride=stride, padding=padding, bias=bias).to("cpu"))
        elif t == 'D': #膨胀卷积
            L.append(nn.Conv2d(in_channels=in_channels, out_channels=out_channels, kernel_size=kernel_size, stride=stride, padding=2, bias=bias,dilation=dilation).to("cpu"))
        elif t == 'B':
            L.append(nn.BatchNorm2d(out_channels, momentum=0.9, eps=1e-04, affine=True).to("cpu"))
        elif t == 'I':
            L.append(nn.InstanceNorm2d(out_channels, affine=True).to("cpu"))
        elif t == 'R':
            L.append(nn.ReLU(inplace=True).to("cpu"))
        elif t == 'r':
            L.append(nn.ReLU(inplace=False).to("cpu"))
        elif t == 'L':
            L.append(nn.LeakyReLU(negative_slope=negative_slope, inplace=True).to("cpu"))
        elif t == 'l':
            L.append(nn.LeakyReLU(negative_slope=negative_slope, inplace=False).to("cpu"))
        elif t == '2':
            L.append(nn.PixelShuffle(upscale_factor=2))
        elif t == '3':
            L.append(nn.PixelShuffle(upscale_factor=3))
        elif t == '4':
            L.append(nn.PixelShuffle(upscale_factor=4))
        elif t == 'U':
            L.append(nn.Upsample(scale_factor=2, mode='nearest'))
        elif t == 'u':
            L.append(nn.Upsample(scale_factor=3, mode='nearest'))
        elif t == 'v':
            L.append(nn.Upsample(scale_factor=4, mode='nearest'))
        elif t == 'M':
            L.append(nn.MaxPool2d(kernel_size=kernel_size, stride=stride, padding=0))
        elif t == 'A':
            L.append(nn.AvgPool2d(kernel_size=kernel_size, stride=stride, padding=0))
        elif t == 'N': #BatchReNomal
            L.append(BatchRenorm2d(64))
        else:
            raise NotImplementedError('Undefined type: '.format(t))
    return sequential(*L)


# --------------------------------------------
# inverse of pixel_shuffle
# --------------------------------------------
def pixel_unshuffle(input, upscale_factor):
    r"""Rearranges elements in a Tensor of shape :math:`(C, rH, rW)` to a
    tensor of shape :math:`(*, r^2C, H, W)`.

    Authors:
        Zhaoyi Yan, https://github.com/Zhaoyi-Yan
        Kai Zhang, https://github.com/cszn/FFDNet

    Date:
        01/Jan/2019
    """
    batch_size, channels, in_height, in_width = input.size()

    out_height = in_height // upscale_factor
    out_width = in_width // upscale_factor

    '''Tensor.contiguous()函数不会对原始数据进行任何修改，而仅仅对其进行复制，
    并在内存空间上进行对齐，即在内存空间上，tensor元素的内存地址保持连续。'''
    input_view = input.contiguous().view(
        batch_size, channels, out_height, upscale_factor,
        out_width, upscale_factor)

    channels *= upscale_factor ** 2
    # 对于一个高维的Tensor执行permute，我们没有改变数据的相对位置，而只是旋转了一下这个(超)立方体。或者也可以说，改变了我们对这个(超)立方体的“观察角度”而已。
    unshuffle_out = input_view.permute(0, 1, 3, 5, 2, 4).contiguous()
    return unshuffle_out.view(batch_size, channels, out_height, out_width)


class PixelUnShuffle(nn.Module):
    r"""Rearranges elements in a Tensor of shape :math:`(C, rH, rW)` to a
    tensor of shape :math:`(*, r^2C, H, W)`.

    Authors:
        Zhaoyi Yan, https://github.com/Zhaoyi-Yan
        Kai Zhang, https://github.com/cszn/FFDNet

    Date:
        01/Jan/2019
    """

    def __init__(self, upscale_factor):
        super(PixelUnShuffle, self).__init__()
        self.upscale_factor = upscale_factor

    def forward(self, input):
        return pixel_unshuffle(input, self.upscale_factor)

    def extra_repr(self):
        return 'upscale_factor={}'.format(self.upscale_factor)


# --------------------------------------------
# conditional batch norm
# https://github.com/pytorch/pytorch/issues/8985#issuecomment-405080775
# --------------------------------------------
class ConditionalBatchNorm2d(nn.Module):
    def __init__(self, num_features, num_classes):
        super().__init__()
        self.num_features = num_features
        self.bn = nn.BatchNorm2d(num_features, affine=False)
        self.embed = nn.Embedding(num_classes, num_features * 2)
        self.embed.weight.data[:, :num_features].normal_(1, 0.02)  # Initialise scale at N(1, 0.02)
        self.embed.weight.data[:, num_features:].zero_()  # Initialise bias at 0

    def forward(self, x, y):
        out = self.bn(x)
        gamma, beta = self.embed(y).chunk(2, 1)
        out = gamma.view(-1, self.num_features, 1, 1) * out + beta.view(-1, self.num_features, 1, 1)
        return out


# --------------------------------------------
# Concat the output of a submodule to its input
# --------------------------------------------
class ConcatBlock(nn.Module):
    def __init__(self, submodule):
        super(ConcatBlock, self).__init__()
        self.sub = submodule

    def forward(self, x):
        output = torch.cat((x, self.sub(x)), dim=1)
        return output

    def __repr__(self):
        return self.sub.__repr__() + 'concat'


# --------------------------------------------
# sum the output of a submodule to its input
# --------------------------------------------
class ShortcutBlock(nn.Module):
    def __init__(self, submodule):
        super(ShortcutBlock, self).__init__()

        self.sub = submodule

    def forward(self, x):
        output = x + self.sub(x)
        return output

    def __repr__(self):
        tmpstr = 'Identity + \n|'
        modstr = self.sub.__repr__().replace('\n', '\n|')
        tmpstr = tmpstr + modstr
        return tmpstr


class ResBlock(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CRC', negative_slope=0.2):
        super(ResBlock, self).__init__()
        self.patch_unembed = PatchUnEmbed(
            img_size=(128, 128), patch_size=1, in_chans=in_channels, embed_dim=in_channels,
            norm_layer=nn.LayerNorm)
        self.patch_embed = PatchEmbed(
            img_size=(128, 128), patch_size=1, in_chans=in_channels, embed_dim=in_channels,
            norm_layer=nn.LayerNorm)
        patches_resolution = self.patch_embed.patches_resolution
        self.layer = module.RSTB(dim=in_channels,
                     input_resolution=(patches_resolution[0],
                                       patches_resolution[1]),
                     depth=6,
                     num_heads=8,
                     window_size=8,
                     mlp_ratio=4,
                     qkv_bias=True, qk_scale=None,
                     drop=0, attn_drop=0,
                     drop_path=0,  # no impact on SR results
                     norm_layer=nn.LayerNorm,
                     downsample=None,
                     use_checkpoint=False,
                     img_size= (64, 64),
                     patch_size=1,
                     resi_connection='1conv'
                     )
    def check_image_size(self, x):
        _, _, h, w = x.size()
        mod_pad_h = (8 - h % 8) % 8
        mod_pad_w = (8 - w % 8) %8
        x = F.pad(x, (0, mod_pad_w, 0, mod_pad_h), 'reflect')
        return x
    def forward(self, x):
        B1, C1, H1, W1 = x.size()
        x0=x
        x = self.check_image_size(x)  # 补齐那些不是8的倍数的
        x_size = (x.shape[2], x.shape[3])
        x = self.patch_embed(x)
        x = self.layer(x, x_size)
        x = self.patch_unembed(x, x_size)
        x = x[:, :, :H1, :W1]

        return x+x0
class ResBlock_CRD(nn.Module):
    def __init__(self, in_channels=64, out_channels=64,dct=40):
        super(ResBlock_CRD, self).__init__()
        self.fca=FCA.MultiSpectralAttentionLayer(channel=out_channels,dct_h=dct,dct_w=dct)
        self.donsampe = nn.Conv2d(in_channels, in_channels, 3, 2, 1)
        #self.avg_pool = nn.AdaptiveAvgPool2d(1)

        #self.max_pool = nn.AdaptiveMaxPool2d(1)

        #self.fc1 = nn.Conv2d(out_channels, 1, 1, bias=False)
        #self.relu1 = nn.ReLU()
        #self.fc2 = nn.Conv2d(1, out_channels, 1, bias=False)
        #self.sigmoid = nn.Sigmoid()
        #self.u=upsample.freup_Periodicpadding(in_channels,out_channels)
        #self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=1, padding=1,bias=True)
        #self.conv2 = nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=True)
        #self.relu2 = nn.ReLU()

    def forward(self, x):
        x=self.donsampe(x)
        #x = self.u(x)

        #fft_result = torch.fft.fftn(x, dim=(-2, -1))
        #avg_out = self.fc2(self.relu1(self.fc1(self.avg_pool(x))))
        #max_out = self.fc2(self.relu1(self.fc1(self.max_pool(x))))
        #out = avg_out + max_out
        # 经过 Sigmoid 激活函数，生成通道注意力权重
        #channel_attention_weights = self.sigmoid(out)
        #fft_result=self.conv2(fft_result.real)0
        #fft_result=self.relu2(fft_result)
        #ifft_result = torch.fft.ifftn(fft_result, dim=(-2, -1))
        # 将通道注意力权重应用在输入张量的每个通道上
        #weighted_x = x* channel_attention_weights
        channel_attention_weights=self.fca(x)
        return channel_attention_weights

class ResBlock_CDC(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBR',
                 negative_slope=0.2,res_t=1):
        super(ResBlock_CDC, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]
        self.kongjian = conv(in_channels=2, out_channels=1, kernel_size=3, stride=1, padding=1, bias=True, dilation=2,
                             mode='CS', negative_slope=0.2)
        #self.kongjian_xu = conv(in_channels=2, out_channels=1, kernel_size=3, stride=1, padding=1, bias=True,dilation=2, mode='CS', negative_slope=0.2)
        self.res_t=res_t
        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, 2, mode, negative_slope)

    def forward(self, x):

        x0=x

        res = self.res(x)

        avg_out = torch.mean(res, dim=1, keepdim=True)  # 用于计算在第一个维度上的均值，即对每一行进行求平均，keepdim=True表示保持结果的维度与输入的维度一致（即保持行数不变）
        max_out, _ = torch.max(res, dim=1, keepdim=True)
        out = torch.cat([avg_out, max_out], dim=1)  # 将每一行的均值和最大值连接在一起，形成一个新的张量
        #out = self.conv1(out)

        res=res*self.kongjian(out)
        #x=self.BN(x)
        if self.res_t==1:
            return res+x0
        else:return res


class ResBlock_CDCC(nn.Module):
    def __init__(self, in_channels=64, out_channels=64 ,dct=40,):
        super(ResBlock_CDCC, self).__init__()
        self.fca=FCA.MultiSpectralAttentionLayer(channel=out_channels,dct_h=dct,dct_w=dct)
        self.u=upsample.fresadd(in_channels)
        #self.up = nn.Upsample(scale_factor=2, mode="nearest")
        #self.conv = nn.Conv2d(in_channels, in_channels, 3, padding=1)
    def forward(self, x):
        x = self.u(x)
        channel_attention_weights=self.fca(x)
        return channel_attention_weights

#DoubleConv DoubleConv
class ResBlock_CCC(nn.Module):
    def __init__(self, in_channels, out_channels, mid_channels=None):
        super().__init__()
        if not mid_channels:
            mid_channels = out_channels
        self.double_conv = nn.Sequential(
            nn.Conv2d(in_channels, mid_channels, kernel_size=3, padding=1, bias=False),
            nn.BatchNorm2d(mid_channels),
            nn.ReLU(inplace=True),
            nn.Conv2d(mid_channels, out_channels, kernel_size=3, padding=1, bias=False),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True)
        )

    def forward(self, x):
        return self.double_conv(x)
class WMSA(nn.Module):
    """ Self-attention module in Swin Transformer
    """

    def __init__(self, input_dim, output_dim, head_dim, window_size, type):
        super(WMSA, self).__init__()
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.head_dim = head_dim
        self.scale = self.head_dim ** -0.5
        self.n_heads = input_dim // head_dim
        self.window_size = window_size
        self.type = type
        self.embedding_layer1 = nn.Conv2d(in_channels=input_dim, out_channels=3 * input_dim, kernel_size=1, stride=1, padding=0, bias=True)

        # TODO recover
        # self.relative_position_params = nn.Parameter(torch.zeros(self.n_heads, 2 * window_size - 1, 2 * window_size -1))
        self.relative_position_params = nn.Parameter(
            torch.zeros((2 * window_size - 1) * (2 * window_size - 1), self.n_heads))

        self.linear1 = nn.Conv2d(in_channels=input_dim, out_channels=input_dim, kernel_size=1, stride=1, padding=0, bias=True)


        trunc_normal_(self.relative_position_params, std=.02)
        self.relative_position_params = torch.nn.Parameter(
            self.relative_position_params.view(2 * window_size - 1, 2 * window_size - 1, self.n_heads).transpose(1,
                                                                                                                 2).transpose(
                0, 1))

    def generate_mask(self, h, w, p, shift):
        """ generating the mask of SW-MSA
        Args:
            shift: shift parameters in CyclicShift.
        Returns:
            attn_mask: should be (1 1 w p p),
        """
        # supporting sqaure.
        attn_mask = torch.zeros(h, w, p, p, p, p, dtype=torch.bool, device=self.relative_position_params.device)
        if self.type == 'W':
            return attn_mask

        s = p - shift
        attn_mask[-1, :, :s, :, s:, :] = True
        attn_mask[-1, :, s:, :, :s, :] = True
        attn_mask[:, -1, :, :s, :, s:] = True
        attn_mask[:, -1, :, s:, :, :s] = True
        attn_mask =rearrange(attn_mask, 'w1 w2 p1 p2 p3 p4 -> 1 1 (w1 w2) (p1 p2) (p3 p4)')
        return attn_mask

    def forward(self, x):
        """ Forward pass of Window Multi-head Self-attention module.
        Args:
            x: input tensor with shape of [b h w c];
            attn_mask: attention mask, fill -inf where the value is True;
        Returns:
            output: tensor shape [b h w c]
        """
        if self.type != 'W': x = torch.roll(x, shifts=(-(self.window_size // 2), -(self.window_size // 2)), dims=(1, 2))
        x = rearrange(x, 'b (w1 p1) (w2 p2) c -> b w1 w2 p1 p2 c', p1=self.window_size, p2=self.window_size)
        h_windows = x.size(1)
        w_windows = x.size(2)
        # sqaure validation
        # assert h_windows == w_windows

        x = rearrange(x, 'b w1 w2 p1 p2 c -> b (w1 w2) (p1 p2) c', p1=self.window_size, p2=self.window_size)
        x = x.permute(0, 3, 1, 2)  # 变成 (1, 96, 64, 64)
        qkv = self.embedding_layer1(x)
        qkv = qkv.permute(0, 2, 3, 1)
        q, k, v = rearrange(qkv, 'b nw np (threeh c) -> threeh b nw np c', c=self.head_dim).chunk(3, dim=0)
        sim = torch.einsum('hbwpc,hbwqc->hbwpq', q, k) * self.scale
        # Adding learnable relative embedding
        sim = sim + rearrange(self.relative_embedding(), 'h p q -> h 1 1 p q')
        # Using Attn Mask to distinguish different subwindows.
        if self.type != 'W':
            attn_mask = self.generate_mask(h_windows, w_windows, self.window_size, shift=self.window_size // 2)
            sim = sim.masked_fill_(attn_mask, float("-inf"))

        probs = nn.functional.softmax(sim, dim=-1)
        output = torch.einsum('hbwij,hbwjc->hbwic', probs, v)
        output = rearrange(output, 'h b w p c -> b w p (h c)')
        output = output.permute(0, 3, 1, 2)  # 变成 (1, 96, 64, 64)
        output = self.linear1(output)
        output = output.permute(0, 2, 3, 1)
        output = rearrange(output, 'b (w1 w2) (p1 p2) c -> b (w1 p1) (w2 p2) c', w1=h_windows, p1=self.window_size)

        if self.type != 'W': output = torch.roll(output, shifts=(self.window_size // 2, self.window_size // 2),
                                                 dims=(1, 2))



        return output

    def relative_embedding(self):
        cord = torch.tensor(np.array([[i, j] for i in range(self.window_size) for j in range(self.window_size)]))
        relation = cord[:, None, :] - cord[None, :, :] + self.window_size - 1
        # negative is allowed
        return self.relative_position_params[:, relation[:, :, 0].long(), relation[:, :, 1].long()]

class StdPool(nn.Module):
    def __init__(self):
        super(StdPool, self).__init__()
    def forward(self, x):
        b, c, _, _ = x.size()
        std = x.view(b, c, -1).std(dim=2, keepdim=True)
        std = std.reshape(b, c, 1, 1)
        return std
class MCAGate(nn.Module):
    def __init__(self, k_size, pool_types=['avg', 'std']):
        """Constructs a MCAGate module.
        Args:
            k_size: kernel size
            pool_types: pooling type. 'avg': average pooling, 'max': max pooling, 'std': standard deviation pooling.
        """
        super(MCAGate, self).__init__()
        self.pools = nn.ModuleList([])
        for pool_type in pool_types:
            if pool_type == 'avg':
                self.pools.append(nn.AdaptiveAvgPool2d(1))
            elif pool_type == 'max':
                self.pools.append(nn.AdaptiveMaxPool2d(1))
            elif pool_type == 'std':
                self.pools.append(StdPool())
            else:
                raise NotImplementedError
        self.conv = nn.Conv2d(1, 1, kernel_size=(1, k_size), stride=1, padding=(0, (k_size - 1) // 2), bias=False)
        self.sigmoid = nn.Sigmoid()
        self.weight = nn.Parameter(torch.rand(2))
    def forward(self, x):
        feats = [pool(x) for pool in self.pools]
        if len(feats) == 1:
            out = feats[0]
        elif len(feats) == 2:
            weight = torch.sigmoid(self.weight)
            out = 1 / 2 * (feats[0] + feats[1]) + weight[0] * feats[0] + weight[1] * feats[1]
        else:
            assert False, "Feature Extraction Exception!"
        out = out.permute(0, 3, 2, 1).contiguous()
        out = self.conv(out)
        out = out.permute(0, 3, 2, 1).contiguous()
        out = self.sigmoid(out)
        out = out.expand_as(x)
        return x * out
import math
class MCALayer(nn.Module):
    def __init__(self, inp, no_spatial=False):
        """Constructs a MCA module.
        Args:
            inp: Number of channels of the input feature maps
            no_spatial: whether to build channel dimension interactions
        """
        super(MCALayer, self).__init__()
        lambd = 1.5
        gamma = 1
        temp = round(abs((math.log2(inp) - gamma) / lambd))
        kernel = temp if temp % 2 else temp - 1
        self.h_cw = MCAGate(3)
        self.w_hc = MCAGate(3)
        self.no_spatial = no_spatial
        if not no_spatial:
            self.c_hw = MCAGate(kernel)
    def forward(self, x):
        x_h = x.permute(0, 2, 1, 3).contiguous()
        x_h = self.h_cw(x_h)
        x_h = x_h.permute(0, 2, 1, 3).contiguous()
        x_w = x.permute(0, 3, 2, 1).contiguous()
        x_w = self.w_hc(x_w)
        x_w = x_w.permute(0, 3, 2, 1).contiguous()
        if not self.no_spatial:
            x_c = self.c_hw(x)
            x_out = 1 / 3 * (x_c + x_h + x_w)
        else:
            x_out = 1 / 2 * (x_h + x_w)
        return x_out
class Block(nn.Module):
    def __init__(self, input_dim, output_dim, head_dim, window_size, drop_path, type='W', input_resolution=None):
        """ SwinTransformer Block
        """
        super(Block, self).__init__()
        self.input_dim = input_dim
        self.output_dim = output_dim
        assert type in ['W', 'SW']
        self.type = type
        if input_resolution <= window_size:
            self.type = 'W'

        self.ln1 = nn.LayerNorm(input_dim)
        self.msa = WMSA(input_dim, input_dim, head_dim, window_size, self.type)
        self.drop_path = DropPath(drop_path) if drop_path > 0. else nn.Identity()
        self.ln2 = nn.LayerNorm(input_dim)
        self.mlp = nn.Sequential(
            nn.Linear(input_dim, 4 * input_dim),
            nn.GELU(),
            nn.Linear(4 * input_dim, output_dim),
        )

    def forward(self, x):
        x = x + self.drop_path(self.msa(self.ln1(x)))
        x = x + self.drop_path(self.mlp(self.ln2(x)))
        return x
class Block2(nn.Module):
    def __init__(self, input_dim, output_dim, head_dim, window_size, drop_path, type='W', input_resolution=None):
        """ SwinTransformer Block
        """
        super(Block2, self).__init__()
        self.input_dim = input_dim
        self.output_dim = output_dim
        assert type in ['W', 'SW']
        self.type = type
        if input_resolution <= window_size:
            self.type = 'W'

        self.ln1 = nn.LayerNorm(input_dim)
        from models import mamba1
        self.mamba_layers = nn.ModuleList([mamba1.create_block(d_model=self.conv_dim) for _ in range(4)])
        self.ln2 = nn.LayerNorm(input_dim)
        self.mlp = nn.Sequential(
            nn.Linear(input_dim, 4 * input_dim),
            nn.GELU(),
            nn.Linear(4 * input_dim, output_dim),
        )

    def forward(self, x):

        mamba_x=self.ln1(x)
        B, C, H, W = mamba_x.shape
        mamba_x = mamba_x.view(B, C, H * W).permute(0, 2, 1)
        residual = None

        for i, mamba in enumerate(self.mamba_layers):
            if i % 2 == 0:
                # 偶数层：处理正向序列
                mamba_x, residual = mamba(mamba_x, residual)
            else:
                mamba_x_fan, residual_fan = mamba(mamba_x.flip([1]), residual.flip([1]))
                mamba_x = mamba_x + mamba_x_fan.flip([1])
                residual = residual + residual_fan.flip([1])

        mamba_x = mamba_x.permute(0, 2, 1).view(B, C, H, W)+x
        x=self.ln2(mamba_x)
        x=self.mlp(x)+mamba_x
        return x

#最后的
class ResBlock_CD2C(nn.Module):
    def __init__(self, conv_dim, trans_dim, head_dim, window_size, drop_path, type='W', input_resolution=None):
        """ SwinTransformer and Conv Block
        """
        super(ResBlock_CD2C, self).__init__()
        self.conv_dim = conv_dim
        self.trans_dim = trans_dim
        self.head_dim = head_dim
        self.window_size = window_size
        self.drop_path = drop_path
        self.type = type
        self.input_resolution = input_resolution

        assert self.type in ['W', 'SW']
        if self.input_resolution <= self.window_size:
            self.type = 'W'

        self.trans_block = Block(self.trans_dim, self.trans_dim, self.head_dim, self.window_size, self.drop_path,
                                 self.type, self.input_resolution)
        self.conv1_1 = nn.Conv2d(self.conv_dim + self.trans_dim+self.conv_dim, self.conv_dim +self.conv_dim+ self.trans_dim, 1, 1, 0, bias=True)
        #self.conv1_2 = nn.Conv2d(self.conv_dim + self.trans_dim+self.conv_dim, self.conv_dim+self.conv_dim + self.trans_dim, 1, 1, 0, bias=True)
        self.conv3d = nn.Conv3d(in_channels=1, out_channels=1, kernel_size=(1, 1, 3), stride=1, padding=(0, 0, 1))
        self.conv_block = nn.Sequential(
            nn.Conv2d(self.conv_dim, self.conv_dim, 3, 1, 1, bias=False),
            nn.ReLU(True),
            nn.Conv2d(self.conv_dim, self.conv_dim, 3, 1, 1, bias=False)
        )
        from models import mamba1
        self.mamba_layers = nn.ModuleList([mamba1.create_block(d_model=self.conv_dim) for _ in range(4)])

        self.pcbam_module = MCALayer(inp=conv_dim*3)
    def forward(self, x):
        conv_x,mamba_x, trans_x = torch.split(self.conv1_1(x), (self.conv_dim, self.conv_dim,self.trans_dim), dim=1)
        conv_x = self.conv_block(conv_x) + conv_x
        B, C, H, W = mamba_x.shape
        mamba_x = mamba_x.view(B, C, H * W).permute(0, 2, 1)
        residual = None

        for i, mamba in enumerate(self.mamba_layers):
            if i % 2 == 0:
                # 偶数层：处理正向序列
                mamba_x, residual = mamba(mamba_x, residual)
            else:
                mamba_x_fan, residual_fan = mamba(mamba_x.flip([1]), residual.flip([1]))
                mamba_x = mamba_x + mamba_x_fan.flip([1])
                residual = residual + residual_fan.flip([1])


        mamba_x = mamba_x.permute(0, 2, 1).view(B, C, H, W)
        trans_x = Rearrange('b c h w -> b h w c')(trans_x)
        trans_x = self.trans_block(trans_x)
        trans_x = Rearrange('b h w c -> b c h w')(trans_x)

        combined = torch.zeros(B, 3 * C,  H , W).to('cuda')
        # 交替插入通道
        combined[:, 0::3, :, :] = conv_x  # 第1, 4, 7, ... 通道来自 conv_x
        combined[:, 1::3, :, :] = trans_x  # 第2, 5, 8, ... 通道来自 trans_x
        combined[:, 2::3, :, :] = mamba_x  # 第3, 6, 9, ... 通道来自 mamba_x
        combined = combined.unsqueeze(1)  # (B, 1, C, H, W)
        res = self.conv3d(combined)
        res = res.squeeze(1)  # 输出形状: (B, 1, H, W)
        res=self.pcbam_module(res)
        x = x + res

        return x


# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))    CBRCR
# --------------------------------------------
# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))
# --------------------------------------------
class ResBlock_ResDNN(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CCR',
                 negative_slope=0.2):
        super(ResBlock_ResDNN, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, 1, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res
# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))    CBRDB
# --------------------------------------------
class ResBlock_ResCBRDB(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBRDB',
                 negative_slope=0.2):
        super(ResBlock_ResCBRDB, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, 2, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res

# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))    CBRDB
# --------------------------------------------
class ResBlock_ResCBRCR(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBRCR',
                 negative_slope=0.2):
        super(ResBlock_ResCBRCR, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, 1, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res
# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))    CBRCB
# --------------------------------------------
class ResBlock_ResCBRCB(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBRCB',
                 negative_slope=0.2):
        super(ResBlock_ResCBRCB, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, 1, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res
# --------------------------------------------
# Res Block: x + conv(relu(conv(x)))    CBRCBR
# --------------------------------------------
class ResBlock_ResCBRCBR(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBRCBR',
                 negative_slope=0.2):
        super(ResBlock_ResCBRCBR, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, 1, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res
        # --------------------------------------------

# Res Block: x + conv(relu(conv(x)))    CBRDBR
# --------------------------------------------
class ResBlock_ResCBRDBR(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBRDBR',
                 negative_slope=0.2):
        super(ResBlock_ResCBRDBR, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding,bias, 2, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res
# Res Block: x + conv(relu(conv(x)))    CBRDR
# --------------------------------------------
class ResBlock_ResCBRDR(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CBRDR',
                 negative_slope=0.2):
        super(ResBlock_ResCBRDR, self).__init__()

        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R', 'L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding,bias, 2, mode, negative_slope)

    def forward(self, x):
        res = self.res(x)
        return x + res
# --------------------------------------------
# simplified information multi-distillation block (IMDB)
# x + conv1(concat(split(relu(conv(x)))x3))
# --------------------------------------------
class IMDBlock(nn.Module):
    """
    @inproceedings{hui2019lightweight,
      title={Lightweight Image Super-Resolution with Information Multi-distillation Network},
      author={Hui, Zheng and Gao, Xinbo and Yang, Yunchu and Wang, Xiumei},
      booktitle={Proceedings of the 27th ACM International Conference on Multimedia (ACM MM)},
      pages={2024--2032},
      year={2019}
    }
    @inproceedings{zhang2019aim,
      title={AIM 2019 Challenge on Constrained Super-Resolution: Methods and Results},
      author={Kai Zhang and Shuhang Gu and Radu Timofte and others},
      booktitle={IEEE International Conference on Computer Vision Workshops},
      year={2019}
    }
    """
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CL', d_rate=0.25, negative_slope=0.05):
        super(IMDBlock, self).__init__()
        self.d_nc = int(in_channels * d_rate)
        self.r_nc = int(in_channels - self.d_nc)

        assert mode[0] == 'C', 'convolutional layer first'

        self.conv1 = conv(in_channels, in_channels, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv2 = conv(self.r_nc, in_channels, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv3 = conv(self.r_nc, in_channels, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv4 = conv(self.r_nc, self.d_nc, kernel_size, stride, padding, bias, mode[0], negative_slope)
        self.conv1x1 = conv(self.d_nc*4, out_channels, kernel_size=1, stride=1, padding=0, bias=bias, mode=mode[0], negative_slope=negative_slope)

    def forward(self, x):
        d1, r1 = torch.split(self.conv1(x), (self.d_nc, self.r_nc), dim=1)
        d2, r2 = torch.split(self.conv2(r1), (self.d_nc, self.r_nc), dim=1)
        d3, r3 = torch.split(self.conv3(r2), (self.d_nc, self.r_nc), dim=1)
        d4 = self.conv4(r3)
        res = self.conv1x1(torch.cat((d1, d2, d3, d4), dim=1))
        return x + res


# --------------------------------------------
# Enhanced Spatial Attention (ESA)
# --------------------------------------------
class ESA(nn.Module):
    def __init__(self, channel=64, reduction=4, bias=True):
        super(ESA, self).__init__()
        #               -->conv3x3(conv21)-----------------------------------------------------------------------------------------+
        # conv1x1(conv1)-->conv3x3-2(conv2)-->maxpool7-3-->conv3x3(conv3)(relu)-->conv3x3(conv4)(relu)-->conv3x3(conv5)-->bilinear--->conv1x1(conv6)-->sigmoid
        self.r_nc = channel // reduction
        self.conv1 = nn.Conv2d(channel, self.r_nc, kernel_size=1)
        self.conv21 = nn.Conv2d(self.r_nc, self.r_nc, kernel_size=1)
        self.conv2 = nn.Conv2d(self.r_nc, self.r_nc, kernel_size=3, stride=2, padding=0)
        self.conv3 = nn.Conv2d(self.r_nc, self.r_nc, kernel_size=3, padding=1)
        self.conv4 = nn.Conv2d(self.r_nc, self.r_nc, kernel_size=3, padding=1)
        self.conv5 = nn.Conv2d(self.r_nc, self.r_nc, kernel_size=3, padding=1)
        self.conv6 = nn.Conv2d(self.r_nc, channel, kernel_size=1)
        self.sigmoid = nn.Sigmoid()
        self.relu = nn.ReLU(inplace=True)

    def forward(self, x):
        x1 = self.conv1(x)
        x2 = F.max_pool2d(self.conv2(x1), kernel_size=7, stride=3)  # 1/6
        x2 = self.relu(self.conv3(x2))
        x2 = self.relu(self.conv4(x2))
        x2 = F.interpolate(self.conv5(x2), (x.size(2), x.size(3)), mode='bilinear', align_corners=False)
        x2 = self.conv6(x2 + self.conv21(x1))
        return x.mul(self.sigmoid(x2))
        # return x.mul_(self.sigmoid(x2))


class CFRB(nn.Module):
    def __init__(self, in_channels=50, out_channels=50, kernel_size=3, stride=1, padding=1, bias=True, mode='CL', d_rate=0.5, negative_slope=0.05):
        super(CFRB, self).__init__()
        self.d_nc = int(in_channels * d_rate)
        self.r_nc = in_channels  # int(in_channels - self.d_nc)

        assert mode[0] == 'C', 'convolutional layer first'

        self.conv1_d = conv(in_channels, self.d_nc, kernel_size=1, stride=1, padding=0, bias=bias, mode=mode[0])
        self.conv1_r = conv(in_channels, self.r_nc, kernel_size, stride, padding, bias=bias, mode=mode[0])
        self.conv2_d = conv(self.r_nc, self.d_nc, kernel_size=1, stride=1, padding=0, bias=bias, mode=mode[0])
        self.conv2_r = conv(self.r_nc, self.r_nc, kernel_size, stride, padding, bias=bias, mode=mode[0])
        self.conv3_d = conv(self.r_nc, self.d_nc, kernel_size=1, stride=1, padding=0, bias=bias, mode=mode[0])
        self.conv3_r = conv(self.r_nc, self.r_nc, kernel_size, stride, padding, bias=bias, mode=mode[0])
        self.conv4_d = conv(self.r_nc, self.d_nc, kernel_size, stride, padding, bias=bias, mode=mode[0])
        self.conv1x1 = conv(self.d_nc*4, out_channels, kernel_size=1, stride=1, padding=0, bias=bias, mode=mode[0])
        self.act = conv(mode=mode[-1], negative_slope=negative_slope)
        self.esa = ESA(in_channels, reduction=4, bias=True)

    def forward(self, x):
        d1 = self.conv1_d(x)
        x = self.act(self.conv1_r(x)+x)
        d2 = self.conv2_d(x)
        x = self.act(self.conv2_r(x)+x)
        d3 = self.conv3_d(x)
        x = self.act(self.conv3_r(x)+x)
        x = self.conv4_d(x)
        x = self.act(torch.cat([d1, d2, d3, x], dim=1))
        x = self.esa(self.conv1x1(x))
        return x


# --------------------------------------------
# Channel Attention (CA) Layer
# --------------------------------------------
class CALayer(nn.Module):
    def __init__(self, channel=64, reduction=16):
        super(CALayer, self).__init__()

        self.avg_pool = nn.AdaptiveAvgPool2d(1)
        self.conv_fc = nn.Sequential(
                nn.Conv2d(channel, channel // reduction, 1, padding=0, bias=True),
                nn.ReLU(inplace=True),
                nn.Conv2d(channel // reduction, channel, 1, padding=0, bias=True),
                nn.Sigmoid()
        )

    def forward(self, x):
        y = self.avg_pool(x)
        y = self.conv_fc(y)
        return x * y


# --------------------------------------------
# Residual Channel Attention Block (RCAB)
# --------------------------------------------
class RCABlock(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CRC', reduction=16, negative_slope=0.2):
        super(RCABlock, self).__init__()
        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R','L']:
            mode = mode[0].lower() + mode[1:]

        self.res = conv(in_channels, out_channels, kernel_size, stride, padding, bias, mode, negative_slope)
        self.ca = CALayer(out_channels, reduction)

    def forward(self, x):
        res = self.res(x)
        res = self.ca(res)
        return res + x


# --------------------------------------------
# Residual Channel Attention Group (RG)
# --------------------------------------------
class RCAGroup(nn.Module):
    def __init__(self, in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='CRC', reduction=16, nb=12, negative_slope=0.2):
        super(RCAGroup, self).__init__()
        assert in_channels == out_channels, 'Only support in_channels==out_channels.'
        if mode[0] in ['R','L']:
            mode = mode[0].lower() + mode[1:]

        RG = [RCABlock(in_channels, out_channels, kernel_size, stride, padding, bias, mode, reduction, negative_slope)  for _ in range(nb)]
        RG.append(conv(out_channels, out_channels, mode='C'))
        self.rg = nn.Sequential(*RG)  # self.rg = ShortcutBlock(nn.Sequential(*RG))

    def forward(self, x):
        res = self.rg(x)
        return res + x


# --------------------------------------------
# Residual Dense Block
# style: 5 convs
# --------------------------------------------
class ResidualDenseBlock_5C(nn.Module):
    def __init__(self, nc=64, gc=32, kernel_size=3, stride=1, padding=1, bias=True, mode='CR', negative_slope=0.2):
        super(ResidualDenseBlock_5C, self).__init__()
        # gc: growth channel
        self.conv1 = conv(nc, gc, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv2 = conv(nc+gc, gc, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv3 = conv(nc+2*gc, gc, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv4 = conv(nc+3*gc, gc, kernel_size, stride, padding, bias, mode, negative_slope)
        self.conv5 = conv(nc+4*gc, nc, kernel_size, stride, padding, bias, mode[:-1], negative_slope)

    def forward(self, x):
        x1 = self.conv1(x)
        x2 = self.conv2(torch.cat((x, x1), 1))
        x3 = self.conv3(torch.cat((x, x1, x2), 1))
        x4 = self.conv4(torch.cat((x, x1, x2, x3), 1))
        x5 = self.conv5(torch.cat((x, x1, x2, x3, x4), 1))
        return x5.mul_(0.2) + x


# --------------------------------------------
# Residual in Residual Dense Block
# 3x5c
# --------------------------------------------
class RRDB(nn.Module):
    def __init__(self, nc=64, gc=32, kernel_size=3, stride=1, padding=1, bias=True, mode='CR', negative_slope=0.2):
        super(RRDB, self).__init__()

        self.RDB1 = ResidualDenseBlock_5C(nc, gc, kernel_size, stride, padding, bias, mode, negative_slope)
        self.RDB2 = ResidualDenseBlock_5C(nc, gc, kernel_size, stride, padding, bias, mode, negative_slope)
        self.RDB3 = ResidualDenseBlock_5C(nc, gc, kernel_size, stride, padding, bias, mode, negative_slope)

    def forward(self, x):
        out = self.RDB1(x)
        out = self.RDB2(out)
        out = self.RDB3(out)
        return out.mul_(0.2) + x


"""
# --------------------------------------------
# Upsampler
# Kai Zhang, https://github.com/cszn/KAIR
# --------------------------------------------
# upsample_pixelshuffle
# upsample_upconv
# upsample_convtranspose
# --------------------------------------------
"""


# --------------------------------------------
# conv + subp (+ relu)
# --------------------------------------------
def upsample_pixelshuffle(in_channels=64, out_channels=3, kernel_size=3, stride=1, padding=1, bias=True, mode='2R', negative_slope=0.2):
    assert len(mode)<4 and mode[0] in ['2', '3', '4'], 'mode examples: 2, 2R, 2BR, 3, ..., 4BR.'
    up1 = conv(in_channels, out_channels * (int(mode[0]) ** 2), kernel_size, stride, padding, bias, mode='C'+mode, negative_slope=negative_slope)
    return up1


# --------------------------------------------
# nearest_upsample + conv (+ R)
# --------------------------------------------
def upsample_upconv(in_channels=64, out_channels=3, kernel_size=3, stride=1, padding=1, bias=True, mode='2R', negative_slope=0.2):
    assert len(mode)<4 and mode[0] in ['2', '3', '4'], 'mode examples: 2, 2R, 2BR, 3, ..., 4BR'
    if mode[0] == '2':
        uc = 'UC'
    elif mode[0] == '3':
        uc = 'uC'
    elif mode[0] == '4':
        uc = 'vC'
    mode = mode.replace(mode[0], uc)
    up1 = conv(in_channels, out_channels, kernel_size, stride, padding, bias, mode=mode, negative_slope=negative_slope)
    return up1


# --------------------------------------------
# convTranspose (+ relu)
# --------------------------------------------
def upsample_convtranspose(in_channels=64, out_channels=3, kernel_size=2, stride=2, padding=0, bias=True, mode='2R', negative_slope=0.2):
    assert len(mode)<4 and mode[0] in ['2', '3', '4'], 'mode examples: 2, 2R, 2BR, 3, ..., 4BR.'
    kernel_size = int(mode[0])
    stride = int(mode[0])
    mode = mode.replace(mode[0], 'T')
    up1 = conv(in_channels, out_channels, kernel_size, stride, padding, bias, mode, negative_slope)
    return up1


'''
# --------------------------------------------
# Downsampler
# Kai Zhang, https://github.com/cszn/KAIR
# --------------------------------------------
# downsample_strideconv
# downsample_maxpool
# downsample_avgpool
# --------------------------------------------
'''


# --------------------------------------------
# strideconv (+ relu)
# --------------------------------------------
def downsample_strideconv(in_channels=64, out_channels=64, kernel_size=2, stride=2, padding=0, bias=True, mode='2R', negative_slope=0.2):
    assert len(mode)<4 and mode[0] in ['2', '3', '4'], 'mode examples: 2, 2R, 2BR, 3, ..., 4BR.'
    kernel_size = int(mode[0])
    stride = int(mode[0])
    mode = mode.replace(mode[0], 'C')
    down1 = conv(in_channels, out_channels, kernel_size, stride, padding, bias, mode, negative_slope)
    return down1


# --------------------------------------------
# maxpooling + conv (+ relu)
# --------------------------------------------
def downsample_maxpool(in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=0, bias=True, mode='2R', negative_slope=0.2):
    assert len(mode)<4 and mode[0] in ['2', '3'], 'mode examples: 2, 2R, 2BR, 3, ..., 3BR.'
    kernel_size_pool = int(mode[0])
    stride_pool = int(mode[0])
    mode = mode.replace(mode[0], 'MC')
    pool = conv(kernel_size=kernel_size_pool, stride=stride_pool, mode=mode[0], negative_slope=negative_slope)
    pool_tail = conv(in_channels, out_channels, kernel_size, stride, padding, bias, mode=mode[1:], negative_slope=negative_slope)
    return sequential(pool, pool_tail)


# --------------------------------------------
# averagepooling + conv (+ relu)
# --------------------------------------------
def downsample_avgpool(in_channels=64, out_channels=64, kernel_size=3, stride=1, padding=1, bias=True, mode='2R', negative_slope=0.2):
    assert len(mode)<4 and mode[0] in ['2', '3'], 'mode examples: 2, 2R, 2BR, 3, ..., 3BR.'
    kernel_size_pool = int(mode[0])
    stride_pool = int(mode[0])
    mode = mode.replace(mode[0], 'AC')
    pool = conv(kernel_size=kernel_size_pool, stride=stride_pool, mode=mode[0], negative_slope=negative_slope)
    pool_tail = conv(in_channels, out_channels, kernel_size, stride, padding, bias, mode=mode[1:], negative_slope=negative_slope)
    return sequential(pool, pool_tail)


'''
# --------------------------------------------
# NonLocalBlock2D:
# embedded_gaussian
# +W(softmax(thetaXphi)Xg)
# --------------------------------------------
'''


# --------------------------------------------
# non-local block with embedded_gaussian
# https://github.com/AlexHex7/Non-local_pytorch
# --------------------------------------------
class NonLocalBlock2D(nn.Module):
    def __init__(self, nc=64, kernel_size=1, stride=1, padding=0, bias=True, act_mode='B', downsample=False, downsample_mode='maxpool', negative_slope=0.2):

        super(NonLocalBlock2D, self).__init__()

        inter_nc = nc // 2
        self.inter_nc = inter_nc
        self.W = conv(inter_nc, nc, kernel_size, stride, padding, bias, mode='C'+act_mode)
        self.theta = conv(nc, inter_nc, kernel_size, stride, padding, bias, mode='C')

        if downsample:
            if downsample_mode == 'avgpool':
                downsample_block = downsample_avgpool
            elif downsample_mode == 'maxpool':
                downsample_block = downsample_maxpool
            elif downsample_mode == 'strideconv':
                downsample_block = downsample_strideconv
            else:
                raise NotImplementedError('downsample mode [{:s}] is not found'.format(downsample_mode))
            self.phi = downsample_block(nc, inter_nc, kernel_size, stride, padding, bias, mode='2')
            self.g = downsample_block(nc, inter_nc, kernel_size, stride, padding, bias, mode='2')
        else:
            self.phi = conv(nc, inter_nc, kernel_size, stride, padding, bias, mode='C')
            self.g = conv(nc, inter_nc, kernel_size, stride, padding, bias, mode='C')

    def forward(self, x):
        '''
        :param x: (b, c, t, h, w)
        :return:
        '''

        batch_size = x.size(0)

        g_x = self.g(x).view(batch_size, self.inter_nc, -1)
        g_x = g_x.permute(0, 2, 1)

        theta_x = self.theta(x).view(batch_size, self.inter_nc, -1)
        theta_x = theta_x.permute(0, 2, 1)
        phi_x = self.phi(x).view(batch_size, self.inter_nc, -1)
        f = torch.matmul(theta_x, phi_x)
        f_div_C = F.softmax(f, dim=-1)

        y = torch.matmul(f_div_C, g_x)
        y = y.permute(0, 2, 1).contiguous()
        y = y.view(batch_size, self.inter_nc, *x.size()[2:])
        W_y = self.W(y)
        z = W_y + x

        return z



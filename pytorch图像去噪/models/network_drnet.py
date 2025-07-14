import torch
import torch.nn as nn
from torchvision import transforms

import models.basicblock as B
from models import common
from models import FTUNET
from torch import nn, Tensor
import math
# --------------------------------------------
# DRNet
# --------------------------------------------
class DRNet(nn.Module):
    def __init__(self, in_nc=1, out_nc=1, nc=64, nb=17, act_mode='BR'):
        super(DRNet, self).__init__()
        n_feats = 160
        kernel_size = 3
        self.scale_idx = 0
        nColor = 3
        conv = common.default_conv
        act = nn.ReLU(True)

        self.DWT = common.DWT()
        self.IWT = common.IWT()

        n = 1
        m_head = [common.BBlock(conv, nColor, n_feats, kernel_size, act=act)]
        d_l0 = []
        d_l0.append(B.ResBlock_CDC(in_channels=n_feats, out_channels=n_feats))
        d_l0.append(B.conv(nc, nc, mode='R', bias=True))
        #d_l0.append(FCA.MultiSpectralAttentionLayer(channel=n_feats, dct_h=7, dct_w=7))

        d_l1 = [B.ResBlock_CRD(in_channels=n_feats , out_channels=n_feats,dct=28)]
        d_l1.append(B.ResBlock_CDC(in_channels=n_feats , out_channels=n_feats ))
        d_l1.append(B.conv(nc,nc,mode='R',bias=True))
        d_l1.append(B.ResBlock_CDC(in_channels=n_feats , out_channels=n_feats))
        d_l1.append(B.conv(nc,nc,mode='R',bias=True))
        d_l2 = []
        d_l2.append(B.ResBlock_CRD(in_channels=n_feats , out_channels=n_feats ,dct=14))
        d_l2.append(B.ResBlock_CDC(in_channels=n_feats , out_channels=n_feats ))
        d_l2.append(B.conv(nc, nc, mode='R', bias=True))
        d_l2.append(B.ResBlock_CDC(in_channels=n_feats , out_channels=n_feats))
        d_l2.append(B.conv(nc, nc, mode='R', bias=True))

        pro_l3 = []
        pro_l3.append(B.ResBlock_CRD(in_channels=n_feats, out_channels=n_feats ,dct=7))
        pro_l3.append(B.ResBlock_CDC(in_channels=n_feats, out_channels=n_feats ))
        pro_l3.append(B.conv(nc, nc, mode='R', bias=True))
        pro_l3.append(B.ResBlock_CDC(in_channels=n_feats, out_channels=n_feats))
        pro_l3.append(B.conv(nc, nc, mode='R', bias=True))
        #pro_l3.append(FTUNET.Block(dim=n_feats, num_heads=16, window_size=4))
        pro_l3.append(FTUNET.Block(dim=n_feats , num_heads=16, window_size=4))
        pro_l3.append(B.ResBlock_CDCC(in_channels=n_feats , out_channels=n_feats,dct=7))


        i_l2=[FTUNET.Block(dim=n_feats , num_heads=16, window_size=8)]

        i_l2.append(B.ResBlock_CDCC(in_channels=n_feats , out_channels=n_feats,dct=14))



        i_l1 = [FTUNET.Block(dim=n_feats , num_heads=16, window_size=8)]

        i_l1.append(B.ResBlock_CDCC(in_channels=n_feats, out_channels=n_feats ,dct=28))

        i_l0 = [FTUNET.Block(dim=n_feats , num_heads=16, window_size=8)]
        m_tail = [conv(n_feats, nColor, kernel_size)]

        self.head = nn.Sequential(*m_head)
        self.d_l2 = nn.Sequential(*d_l2)
        self.d_l1 = nn.Sequential(*d_l1)
        self.d_l0 = nn.Sequential(*d_l0)
        self.pro_l3 = nn.Sequential(*pro_l3)
        self.i_l2 = nn.Sequential(*i_l2)
        self.i_l1 = nn.Sequential(*i_l1)
        self.i_l0 = nn.Sequential(*i_l0)
        self.tail = nn.Sequential(*m_tail)
    def pad_to_multiple_of_8(self, image):
            q, channels, height, width, = image.size()
            pad_width = (8 - width % 8) % 8
            pad_height = (8 - height % 8) % 8
            padding = transforms.Pad((0, 0, pad_width, pad_height), fill=0)
            return padding(image)

    def forward(self, x):
        _, _, original_height, original_width = x.size()

        x = self.pad_to_multiple_of_8(x)
        x0 = self.d_l0(self.head(x))#[128, 64, 48, 48]
        x1 = self.d_l1(x0)#[128, 128, 24, 24]

        x2 = self.d_l2(x1)#([128, 256, 12, 12])
        x_ = self.pro_l3(x2) + x2#([128, 256, 12, 12])
        x_ =self.i_l2(x_) +  x1#([128, 128, 24, 24])
        x_ =self.i_l1(x_) + x0#([128, 64, 48, 48])
        x = self.tail(self.i_l0(x_)) + x
        x = x[:, :,:original_height, :original_width]
        return x



def print_shapes(module, input, output):
    print(f"Input shape: {input[0].shape}")
    print(f"Output shape: {output.shape}")
    print("\n")


if __name__ == '__main__':
    res = DRNet()
    res = res.to("cuda")
    number_parameters = sum(map(lambda x: x.numel(), res.parameters()))
    print(number_parameters)
    #for name, param in res.named_parameters():
        #print(f"Parameter {name} is on device {param.device}")
    input_image = torch.randn(4,3, 56, 56).to("cuda")

    # 创建一个64x64的数组B，初始化全部填充0

    # 执行前向传播
    output = res(input_image)
    print("二次传播",output.shape)

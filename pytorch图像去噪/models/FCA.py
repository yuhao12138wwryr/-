import math

import torch
from torch import nn
#https://blog.csdn.net/qq_45981086/article/details/131335416

def get_freq_indices(method):
    assert method in ['top1','top2','top4','top8','top16','top32',
                      'bot1','bot2','bot4','bot8','bot16','bot32',
                      'low1','low2','low4','low8','low16','low32']
    num_freq = int(method[3:])
    if 'top' in method:
        all_top_indices_x = [0,0,6,0,0,1,1,4,5,1,3,0,0,0,3,2,4,6,3,5,5,2,6,5,5,3,3,4,2,2,6,1]
        all_top_indices_y = [0,1,0,5,2,0,2,0,0,6,0,4,6,3,5,2,6,3,3,3,5,1,1,2,4,2,1,1,3,0,5,3]
        mapper_x = all_top_indices_x[:num_freq]
        mapper_y = all_top_indices_y[:num_freq]
    elif 'low' in method:
        all_low_indices_x = [0,0,1,1,0,2,2,1,2,0,3,4,0,1,3,0,1,2,3,4,5,0,1,2,3,4,5,6,1,2,3,4]
        all_low_indices_y = [0,1,0,1,2,0,1,2,2,3,0,0,4,3,1,5,4,3,2,1,0,6,5,4,3,2,1,0,6,5,4,3]
        mapper_x = all_low_indices_x[:num_freq]
        mapper_y = all_low_indices_y[:num_freq]
    elif 'bot' in method:
        all_bot_indices_x = [6,1,3,3,2,4,1,2,4,4,5,1,4,6,2,5,6,1,6,2,2,4,3,3,5,5,6,2,5,5,3,6]
        all_bot_indices_y = [6,4,4,6,6,3,1,4,4,5,6,5,2,2,5,1,4,3,5,0,3,1,1,2,4,2,1,1,5,3,3,3]
        mapper_x = all_bot_indices_x[:num_freq]
        mapper_y = all_bot_indices_y[:num_freq]
    else:
        raise NotImplementedError
    return mapper_x, mapper_y






class MultiSpectralDCTLayer(nn.Module):
    """
    Generate dct filters
    """

    def __init__(self, height, width, mapper_x, mapper_y, channel):
        super(MultiSpectralDCTLayer, self).__init__()

        assert len(mapper_x) == len(mapper_y)
        assert channel % len(mapper_x) == 0

        self.num_freq = len(mapper_x)

        # fixed DCT init
        # 返回一组DCT滤波器
        self.register_buffer('weight', self.get_dct_filter(height, width, mapper_x, mapper_y, channel))
        #self.weight=self.get_dct_filter(height, width, mapper_x, mapper_y, channel)
        # fixed random init
        # self.register_buffer('weight', torch.rand(channel, height, width))

        # learnable DCT init
        # self.register_parameter('weight', self.get_dct_filter(height, width, mapper_x, mapper_y, channel))

        # learnable random init
        # self.register_parameter('weight', torch.rand(channel, height, width))

        # num_freq, h, w

    def get_dct_filter(self, tile_size_x, tile_size_y, mapper_x, mapper_y, channel):
        dct_filter = torch.zeros(channel, tile_size_x, tile_size_y)

        c_part = channel // len(mapper_x)

        for i, (u_x, v_y) in enumerate(zip(mapper_x, mapper_y)):
            for t_x in range(tile_size_x):
                for t_y in range(tile_size_y):
                    # 构建DCT滤波器，对应数学公式
                    dct_filter[i * c_part: (i + 1) * c_part, t_x, t_y] = self.build_filter(t_x, u_x,
                                                                                           tile_size_x) * self.build_filter(
                        t_y, v_y, tile_size_y)

        return dct_filter

    def build_filter(self, pos, freq, POS):
        result = math.cos(math.pi * freq * (pos + 0.5) / POS) / math.sqrt(POS)
        if freq == 0:
            return result
        else:
            return result * math.sqrt(2)
    def forward(self, x):
        assert len(x.shape) == 4, 'x must been 4 dimensions, but got ' + str(len(x.shape))
        # n, c, h, w = x.shape

        # DCT变换
        # x与DCT滤波器内积
        x = x * self.weight
        # 消去x的2,3维
        result = torch.sum(x, dim=[2, 3])
        return result


class MultiSpectralAttentionLayer(torch.nn.Module):
    def __init__(self, channel, dct_h, dct_w, reduction=16, freq_sel_method='low1'):
        super(MultiSpectralAttentionLayer, self).__init__()
        self.reduction = reduction
        self.dct_h = dct_h
        self.dct_w = dct_w

        mapper_x, mapper_y = get_freq_indices(freq_sel_method)
        self.num_split = len(mapper_x)
        mapper_x = [temp_x * (dct_h // 7) for temp_x in mapper_x]
        mapper_y = [temp_y * (dct_w // 7) for temp_y in mapper_y]
        # make the frequencies in different sizes are identical to a 7x7 frequency space
        # eg, (2,2) in 14x14 is identical to (1,1) in 7x7

        # 返回x的多光谱向量
        self.dct_layer = MultiSpectralDCTLayer(dct_h, dct_w, mapper_x, mapper_y, channel)
        # 全连接层 + relu激活 + 全连接层 + sigmoid激活，返回一个通道注意力向量
        self.fc = nn.Sequential(
            nn.Linear(channel, channel // reduction, bias=False),
            nn.ReLU(inplace=True),
            nn.Linear(channel // reduction, channel, bias=False),
            nn.Sigmoid()
        )

    def forward(self, x):
        n, c, h, w = x.shape
        x_pooled = x
        if h != self.dct_h or w != self.dct_w:

            x_pooled = torch.nn.functional.adaptive_avg_pool2d(x, (self.dct_h, self.dct_w))
            # If you have concerns about one-line-change, don't worry.   :)
            # In the ImageNet models, this line will never be triggered.
            # This is for compatibility in instance segmentation and object detection.

        y = self.dct_layer(x_pooled)

        y = self.fc(y).view(n, c, 1, 1)

        # 通道注意力向量与原图像x相乘
        return x * y.expand_as(x)
class SEBlock(nn.Module):
    def __init__(self, channel, reduction=16):
        super().__init__()
        # Squeeze: 全局平均池化 (GAP)
        self.gap = nn.AdaptiveAvgPool2d(1)
        # Excitation: 全连接层 + 激活函数
        self.fc = nn.Sequential(
            nn.Linear(channel, channel // reduction, bias=False),
            nn.ReLU(inplace=True),
            nn.Linear(channel // reduction, channel, bias=False),
            nn.Sigmoid()
        )

    def forward(self, x):
        b, c, _, _ = x.shape
        # Squeeze
        y = self.gap(x).view(b, c)  # [b, c, 1, 1] -> [b, c]
        # Excitation
        y = self.fc(y).view(b, c, 1, 1)  # [b, c] -> [b, c, 1, 1]
        # 通道加权
        return x * y.expand_as(x)
if __name__ == '__main__':
    import torch
    import time


    def measure_multispectral_attention(model, x, repeat=100):
        model.eval()
        device = x.device
        torch.cuda.empty_cache()

        with torch.no_grad():
            # Warm-up
            for _ in range(10):
                _ = model(x)

            if device.type == "cuda":
                start_event = torch.cuda.Event(enable_timing=True)
                end_event = torch.cuda.Event(enable_timing=True)

                torch.cuda.synchronize()
                start_event.record()

                for _ in range(repeat):
                    _ = model(x)

                end_event.record()
                torch.cuda.synchronize()

                elapsed_time_ms = start_event.elapsed_time(end_event)
                avg_time = elapsed_time_ms / repeat
            else:
                start = time.time()
                for _ in range(repeat):
                    _ = model(x)
                end = time.time()
                elapsed_time_ms = (end - start) * 1000
                avg_time = elapsed_time_ms / repeat

        print(f"运行 {repeat} 次 MultiSpectralAttentionLayer 平均耗时: {avg_time:.3f} ms")
        return avg_time


    # ----------------------------------------------
    # 使用示例
    # ----------------------------------------------
    if __name__ == "__main__":
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        # 假设通道为64，图像尺寸为32x32
        model = MultiSpectralAttentionLayer(channel=64, dct_h=56, dct_w=56, freq_sel_method='top16').to(device)
        input_tensor = torch.randn(8, 64, 56, 56).to(device)

        measure_multispectral_attention(model, input_tensor, repeat=100000)
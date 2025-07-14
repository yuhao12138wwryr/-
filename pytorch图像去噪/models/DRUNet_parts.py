import torch
import torch.nn as nn


class InputCov(nn.Module):
    """
    处理原始图像
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.input_cov = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=(3, 3), padding=(1, 1), stride=(1, 1)),

            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=1, stride=1),
            nn.ReLU(inplace=False),
            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=1, stride=1),

            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=2, stride=1, dilation=2),
            nn.ReLU(inplace=False),
            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=2, stride=1, dilation=2)
        )

    def forward(self, initial_data):
        input_cov = self.input_cov(initial_data)  # (batch,C,W,H)
        input_cov = torch.add(input_cov , initial_data) #特征融合
        return input_cov


class StdCovLocalResBlock(nn.Module):
    """
    使用标准卷积的局部残差模块
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.std_lrb = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1, stride=1),
            nn.ReLU(inplace=False),
            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=1, stride=1)
        )

    def forward(self, input_map):
        std_lrb = self.std_lrb(input_map)  # (btch,C,W,H)
        add_map = torch.sum(input_map, dim=1)  # (batch,W,H)
        add_map_1 = torch.div(add_map, input_map.shape[1]) #加和求均值
        add_map_2 = add_map_1.unsqueeze(1)  # （batch,1,W,H）
        output_map= torch.add(std_lrb , add_map_2) #特征融合
        return output_map


class DilCovLocalResBlock(nn.Module):
    """
    使用空洞卷积的局部残差模块
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.dil_lrb = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=2, stride=1, dilation=2),
            nn.ReLU(inplace=False),
            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=2, stride=1, dilation=2)
        )

    def forward(self, input_map):
        dil_lrb= self.dil_lrb(input_map)  # (abtch,C,W,H)
        add_map = torch.sum(input_map, dim=1)  # (batch_size,W,H)
        add_map_1 = torch.div(add_map, input_map.shape[1])
        add_map_2 = add_map_1.unsqueeze(1)  # （batch,1,W,H）
        output_map= torch.add(dil_lrb, add_map_2)
        return output_map


class LeftGlobalResBlock(nn.Module):
    """
    网络左半部分的全局残差模块
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.std_cov = StdCovLocalResBlock(in_channels, out_channels)
        self.dil_cov = DilCovLocalResBlock(out_channels, out_channels)

    def forward(self, down_map):
        std_cov = self.std_cov(down_map)
        dil_cov = self.dil_cov(std_cov)
        add_map = torch.sum(down_map, dim=1)
        add_map_1 = torch.div(add_map, down_map.shape[1])
        add_map_2 = add_map_1.unsqueeze(1)  # （batch,1,W,H）
        output_map= torch.add(dil_cov, add_map_2)
        return output_map


class RightGlobalResBlock(nn.Module):
    """
    网络右半部分的全局残差模块
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.std_cov_1 = StdCovLocalResBlock(in_channels, out_channels)
        self.std_cov_2 = StdCovLocalResBlock(out_channels, out_channels)

    def forward(self, up_map):
        std_cov_1 = self.std_cov_1(up_map)
        std_cov_2 = self.std_cov_2(std_cov_1)
        add_map = torch.sum(up_map, dim=1)
        add_map_1 = torch.div(add_map, up_map.shape[1])
        add_map_2 = add_map_1.unsqueeze(1)  # （batch,1,W,H）
        output_map= torch.add(std_cov_2, add_map_2)
        return output_map


class Down(nn.Module):
    """
    下采样模块
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.down = nn.Conv2d(in_channels, out_channels, kernel_size=2, padding=0, stride=2)

    def forward(self, input_map):
        return self.down(input_map)


class Up(nn.Module):
    """
    上采样模块
    """

    def __init__(self):
        super().__init__()
        self.up = nn.PixelShuffle(2)

    def forward(self, input_map, skip_map):
        up = self.up(input_map)
        up_map = torch.sum(up, dim=1)
        up_map_1 = torch.div(up_map, input_map.shape[1])
        up_map_2 = up_map_1.unsqueeze(1)  # （batch,1,W,H）
        output_map= torch.add(skip_map, up_map_2)
        return output_map


class OutputCov(nn.Module):
    """
    输出
    """

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.cov = nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1, stride=1)

    def forward(self, input_map):
        return self.cov(input_map)


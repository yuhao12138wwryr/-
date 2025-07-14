import torch
import torch.nn as nn
from torchvision import transforms

import models.basicblock as B
from models import common
from models import FTUNET
from torch import nn, Tensor
import math
# --------------------
class TokenRouter(nn.Module):
    def __init__(self, embed_dim):
        super().__init__()
        self.weight_predictor =nn.Conv2d(embed_dim, 1, kernel_size=1)

    def forward(self, x):
        a,b, s, d = x.shape
        weights = self.weight_predictor(x).squeeze(1)  # [batch_size, seq_len]
        weights = weights.view(a, -1)
        return weights

class MoD(nn.Module):
    def __init__(self, capacity, block,dim):
        super().__init__()
        self.router = TokenRouter(dim)
        self.block = block
        self.capacity = capacity

    def forward(self, x: Tensor):

        a1, b1, s1, d1 = x.shape
        weights = self.router(x)
        x = x.view(a1, b1, -1)
        x = x.permute(0, 2, 1)
        b, s, d = x.shape
        # Compute B-th percentil for router weightsto determine the capacity threshold
        k = int(self.capacity * s)#计算保留多少个像素
        top_k_values, _ = torch.topk(weights, k, dim=1, sorted=True)#把前K各像素存一个数字

        threshold = top_k_values[:, -1]#找出前K各像素的最后一个

        # Determine which tokens exceed the threshold
        selected_mask = weights > threshold.unsqueeze(-1)#生成掩码，把特征图上大于最后一个像素的掩码设为1

        # Process onlys elected tokens through the block
        processed_tokens = torch.zeros_like(x)
        for i in range(b):#遍历所有bachsize
            # Process tokens for each block
            selected_tokens = x[i][selected_mask[i]]#一种掩码的用法，X中对应掩码为0的删除
            if selected_tokens.size(0) > 0:
                selected_tokens = selected_tokens.permute(1, 0)#下面程序目的是对特征图补0，ceil函数向上截断

                chang=selected_tokens.size(1)
                chang1 = selected_tokens.size(1)
                while chang%(s1*math.ceil(d1 * self.capacity))!=0:
                      chang=chang+1
                padding_size = chang - chang1
                selected_tokens = torch.nn.functional.pad(selected_tokens, (0, padding_size))

                selected_tokens = selected_tokens.view(d, s1, math.ceil(d1 * self.capacity))#把补了0的一位像素序列恢复成2维特征图

                temp = self.block(selected_tokens.unsqueeze(0)).squeeze(0)#插入一个bachsize，送入模块
                temp = temp.view(d, s1 * math.ceil(d1 * self.capacity))#恢复成一维序列
                temp = temp[:, :chang1]#把上面补的0删除
                temp = temp.permute(1, 0)
                processed_tokens[i][selected_mask[i]] = temp

                # Combine processed tokens with unprocessed ones
        output = processed_tokens + (
                x * (~selected_mask).unsqueeze(-1).to(x.dtype)
        )
        output = output.permute(0, 2, 1)
        output = output.view(a1, b1, s1, d1)
        return output

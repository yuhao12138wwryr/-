import torch

# 假设我们有四张形状为 (3, 3) 的特征图
feature_maps = torch.randn(1, 4, 3, 3)  # 随机生成数据作为示例

# 首先，在高度维度（dim=2）上将前两张和后两张特征图分别拼接
group1 = torch.cat((feature_maps[:, :2, :, 0], feature_maps[:, :2, :, 1]), dim=1)  # 得到形状 (1, 2, 3, 2)
group2 = torch.cat((feature_maps[:, 2:, :, 0], feature_maps[:, 2:, :, 1]), dim=1)  # 得到形状 (1, 2, 3, 2)

# 然后，在宽度维度（dim=3）上将两组拼接的特征图拼接
combined_maps_horizontal = torch.cat((group1, group2), dim=3)  # 得到形状 (1, 2, 3, 4)

# 接着，将得到的特征图在通道维度（dim=1）上拼接
combined_maps_vertical = torch.cat((combined_maps_horizontal, combined_maps_horizontal), dim=1)  # 得到形状 (1, 4, 3, 4)

# 最后，将特征图在高度和宽度维度上同时扩展，得到形状 (1, 1, 6, 6)
combined_maps = combined_maps_vertical.view(1, 1, -1)  # -1 表示该维度的大小由其他维度的大小和总元素数自动计算
combined_maps = combined_maps.repeat(1, 1, 1, 2)  # 在宽度维度上重复，得到形状 (1, 1, 6, 6)

# 输出结果以检查形状
print(combined_maps.shape)  # 应该输出 torch.Size([1, 1, 6, 6])
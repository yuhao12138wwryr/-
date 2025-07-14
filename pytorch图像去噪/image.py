import os
import cv2

# 设置输入和输出文件夹路径
input_folder = 'A'
output_folder = 'B'

# 创建输出文件夹(如果不存在)
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# 设置输出文件名前缀和起始数字
output_filename_prefix = 'test_'
start_number = 401

# 遍历输入文件夹中的所有文件
for filename in os.listdir(input_folder):
    # 检查是否为图像文件
    if filename.endswith('.jpg') or filename.endswith('.png'):
        # 构建输入和输出文件路径
        input_path = os.path.join(input_folder, filename)
        output_filename = f"{output_filename_prefix}{start_number}.png"
        output_path = os.path.join(output_folder, output_filename)

        # 读取彩色图像
        img = cv2.imread(input_path)

        # 将彩色图像转换为灰度图像
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # 保存灰度图像
        cv2.imwrite(output_path, gray_img)
        print(f"已处理文件: {filename}, 保存为: {output_filename}")

        # 更新输出文件名的起始数字
        start_number += 1

print("所有图像已成功转换为灰度图像并保存到文件夹B。")
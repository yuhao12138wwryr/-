import os
import shutil
import subprocess
from pathlib import Path

# 定义路径
fenzhiceshi_path = Path("trainsets/fenzhiceshi")  # 包含所有文件夹的路径
json_path = Path("options/train_drnet.json")  # JSON 文件路径
script_path = Path("main_train_DRNet.py")  # 要执行的脚本路径
models_path = Path("denoising/DRNet25/models")  # 包含 185020_G.pth 的路径
models_reward_path = Path("denoising/DRNet25/models_reward")  # 存放新建文件夹的路径

# 确保路径存在
if not fenzhiceshi_path.exists():
    raise FileNotFoundError(f"路径 {fenzhiceshi_path} 不存在。")
if not json_path.exists():
    raise FileNotFoundError(f"路径 {json_path} 不存在。")
if not script_path.exists():
    raise FileNotFoundError(f"路径 {script_path} 不存在。")
#if not models_path.exists():
    #raise FileNotFoundError(f"路径 {models_path} 不存在。")
#if not models_reward_path.exists():
#    models_reward_path.mkdir(parents=True, exist_ok=True)
 #   print(f"路径 {models_reward_path} 已创建。")

# 获取所有文件夹的名称
folders = [folder for folder in fenzhiceshi_path.iterdir() if folder.is_dir()]
print(f"找到 {len(folders)} 个文件夹。")

# 遍历每个文件夹
for folder in folders:
    folder_name = folder.name  # 获取文件夹名称
    print(f"正在处理文件夹: {folder_name}")

    # 读取 JSON 文件
    with open(json_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    # 修改第 21 行（注意：Python 中索引从 0 开始，所以第 21 行是 lines[20]）
    if len(lines) >= 21:
        lines[20] = f'      , "dataroot_H": "trainsets/fenzhiceshi/{folder_name}"\n'
    else:
        raise IndexError(f"JSON 文件行数不足 21 行。")

    # 写入修改后的 JSON 文件
    with open(json_path, "w", encoding="utf-8") as f:
        f.writelines(lines)
    print(f"已修改 {json_path} 第 21 行，替换为 {folder_name}。")

    # 执行 main_train_DRNet.py
    try:
        print(f"开始执行 {script_path}...")
        subprocess.run(["python", str(script_path)], check=True)
        print(f"成功执行 {script_path}。")
    except subprocess.CalledProcessError as e:
        print(f"执行 {script_path} 失败: {e}")
        break  # 如果脚本执行失败，停止迭代

    # 在 models_reward_path 下新建文件夹
 #   new_folder = models_reward_path / folder_name
#    if not new_folder.exists():
  #      new_folder.mkdir(parents=True, exist_ok=True)
 #       print(f"文件夹 {new_folder} 已创建。")

    # 将 185020_G.pth 剪切到新建文件夹中
    #pth_file = models_path / "185020_G.pth"
    #if pth_file.exists():
    #    shutil.move(str(pth_file), str(new_folder / "185020_G.pth"))
    #    print(f"已将 185020_G.pth 剪切到 {new_folder}。")
    #else:
    #    print(f"警告：文件 {pth_file} 不存在。")

print("所有文件夹处理完成。")
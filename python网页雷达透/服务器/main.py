import subprocess
import time

# 设置脚本路径
script_path = 'gubao.py'

while True:
    # 使用 subprocess 运行脚本
    process = subprocess.Popen([r'python', script_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # 等待脚本执行完成
    stdout, stderr = process.communicate()


    # 等待一些时间再重新运行（如果需要的话）
    # 可以根据需求添加 sleep，避免立即循环
    print("脚本运行完毕，正在重新启动...")
    time.sleep(0.1)  # 可选的暂停，防止频繁启动

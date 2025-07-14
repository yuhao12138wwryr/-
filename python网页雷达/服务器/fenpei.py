import os
from flask import Flask, request, jsonify
import threading
import subprocess
import psutil
app = Flask(__name__)

# 文件路径
A_TXT_PATH = "a.txt"

# 初始化已分配数字的记录文件
if not os.path.exists(A_TXT_PATH):
    with open(A_TXT_PATH, "w") as f:
        pass


def get_allocated_numbers():
    """读取已分配的数字"""
    with open(A_TXT_PATH, "r") as f:
        lines = f.readlines()
    return set(int(line.strip()) for line in lines if line.strip().isdigit())


def allocate_number():
    """分配一个未使用的数字"""
    allocated = get_allocated_numbers()
    for num in range(1000):
        if num not in allocated:
            with open(A_TXT_PATH, "a") as f:
                f.write(f"{num}\n")
            return num
    return None  # 所有数字都已分配

import os
@app.route('/request_number', methods=['GET'])
def request_number():
    """处理分配数字的请求"""
    allocated_number = allocate_number()
    if allocated_number is not None:
        return jsonify({"number": allocated_number}), 200
    return jsonify({"error": "No available numbers"}), 400
# 全局集合用于记录已执行的数字
executed_numbers = {}  # 存储 {number: timer_object}
processes = {}  # 存储 {number: process_object}

def terminate_process(number):
    """终止与指定 number 对应的进程及其子进程"""
    if number in processes:
        process = processes.pop(number)  # 获取并移除进程
        try:
            # 获取进程树并终止所有子进程
            for proc in psutil.Process(process.pid).children(recursive=True):
                proc.terminate()  # 尝试终止子进程
                proc.wait(timeout=5)  # 等待子进程退出
            # 最后终止主进程
            if process.poll() is None:  # 检查进程是否仍在运行
                process.terminate()
                process.wait(timeout=5)  # 等待主进程退出
                if process.poll() is None:
                    process.kill()  # 如果未退出，强制终止主进程
            print(f"进程 {number} 及其子进程已终止")
        except psutil.NoSuchProcess as e:
            print(f"进程 {number} 不存在: {e}")
        except psutil.AccessDenied as e:
            print(f"访问被拒绝: {e}")
        except Exception as e:
            print(f"终止进程 {number} 时发生错误: {e}")

    if number in executed_numbers:
        executed_numbers.pop(number)  # 移除计时器记录

def modify_and_execute_script(number):
    """修改古堡1.py并执行"""
    script_path = "gubao.py"
    if not os.path.exists(script_path):
        print(f"脚本 {script_path} 不存在")
        return

    # 读取并修改脚本内容
    with open(script_path, "r", encoding="UTF-8") as f:
        lines = f.readlines()

    # 修改特定行内容
    lines[320] = f"    app.run(host='0.0.0.0', port=1000+{number})\n"
    lines[323] = f"    app2.run(host='0.0.0.0', port=2000+{number})\n"

    # 写回文件
    with open(script_path, "w",encoding="UTF-8") as f:
        f.writelines(lines)

    print(f"已修改 {script_path}，即将执行")


    # 立即执行脚本
    script_path1 = "main.py"
    process =subprocess.Popen(["python", script_path1])
    processes[number] = process  # 保存进程对象
    print(f"进程 {number} 启动")

@app.route('/report_number', methods=['POST'])
def report_number():
    """记录客户端返回的数字"""
    data = request.json
    if not data or "number" not in data:
        return jsonify({"error": "Invalid request"}), 400

    number = data["number"]
    allocated = get_allocated_numbers()
    if number in allocated:
        print(f"收到已注册用户: {number}")
        if number not in executed_numbers:
            modify_and_execute_script(number)

        else:
            # 重置定时器
            executed_numbers[number].cancel()
        # 创建新的定时器并启动
        timer = threading.Timer(30 * 60, terminate_process, args=(number,))
        executed_numbers[number] = timer
        timer.start()


        return jsonify({"message": "Number already exists"}), 200
    else:
        # 如果数字不存在，记录到文件
        with open(A_TXT_PATH, "a", encoding="UTF-8") as f:
            f.write(f"{number}\n")
        return jsonify({"message": "Number recorded"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=12138)

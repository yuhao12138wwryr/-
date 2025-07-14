import socket
import threading
import time
import subprocess
import json
from pathlib import Path
# 3. 读取并解析JSON
with open("zhuce.json", 'r', encoding='utf-8') as f:
    config = json.load(f)

# 4. 转换为二维数组
result = [
    # 必须字段
    ["主机ip(不是本机)", config["必须字段"]["主机ip(不是本机)"]],
    ["本机名", config["必须字段"]["本机名"]],

]
list1=[]
i=0
for k, v in config["扩展算法"].items():
    list1.append([k,v['项目路径'],v["python解释器路径"]])
    i=i+1

# 5. 打印验证
print("二维数组结果：")
print(list1)
process={}
fasongxinxi=result[1][1]
suanfabiao=result[2:]#除了前2个，都录入
for i in list1:
    fasongxinxi=fasongxinxi+","+i[0]
print(fasongxinxi)

def get_local_ip():
    """获取本地IP地址"""
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except:
        return "127.0.0.1"

def send_message_to_qt(message, host='127.0.0.1', port=12345):
    """
    向Qt应用程序发送消息

    参数:
        message (str): 要发送的消息内容
        host (str): Qt应用程序所在主机的IP地址
        port (int): Qt应用程序监听的端口号
    """
    try:
        local_ip = get_local_ip()
        full_message = f"{local_ip}:{message}"

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall(full_message.encode('utf-8'))
        print(f"保持连接: {full_message}")
    except Exception as e:
        print(f"发送消息失败: {e}")

def start_receiver(port=4999):
    """
    启动消息接收服务器
    :param port: 监听的端口号
    """
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(('0.0.0.0', port))
        s.listen()
        print(f"接收服务器已启动，监听端口 {port}")

        while True:
            conn, addr = s.accept()
            with conn:
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    message = data.decode('utf-8')
                    if int(message)>=100000000:
                        print("ss")
                        print(list1[int(message) - 1972008941][1])
                        try:
                            key = int(message) - 1972008941 + 5000
                            if key not in process:
                                process[int(message) - 1972008941 + 5000] = subprocess.Popen(
                                    [list1[int(message) - 1972008941][2], list1[int(message) - 1972008941][1], "--port",
                                     str(int(message) - 1972008941 + 5000)],
                                    stdout=subprocess.DEVNULL,  # 丢弃标准输出
                                    stderr=subprocess.DEVNULL,  # 丢弃错误输出
                                    stdin=subprocess.DEVNULL,  # 关闭输入
                                    creationflags=subprocess.CREATE_NO_WINDOW
                                )
                            print(process)
                        except Exception as e:
                            print(f"请将全部电脑重启")
                    elif int(message)<10000:
                        try:
                            process[int(message)+5000].kill()
                            del process[int(message)+5000]
                            print(process)
                        except Exception as e:
                            print(f"请将全部电脑重启")
                    print(f"收到来自 {addr[0]}:{addr[1]} 的消息: {message}")

def sender_loop(interval=1):
    """循环发送消息的线程函数"""
    while True:
        send_message_to_qt(fasongxinxi)
        time.sleep(interval)

if __name__ == "__main__":
    # 启动接收器线程
    receiver_thread = threading.Thread(target=start_receiver, daemon=True)
    receiver_thread.start()

    # 启动发送器线程
    sender_thread = threading.Thread(target=sender_loop, daemon=True)
    sender_thread.start()

    # 保持主线程运行
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\n程序关闭")
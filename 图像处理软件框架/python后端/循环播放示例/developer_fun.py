import a5000
from flask import Flask, render_template, request, redirect, url_for, send_from_directory, jsonify
import os
from werkzeug.utils import secure_filename
import glob
import io
import base64
import time, shutil
import threading
from datetime import datetime
import sys
import argparse
#如果你要调整前端按钮或其他组件的名字，在当前路径templates/index.html中搜索并修改

class UserPicutureApp(a5000.FlaskVideoApp):

  def __init__(self, port=5000, upload_folder=r'D:\C++窗体项目\图像处理软件框架\python后端\循环播放示例\user_uploads',
               b_folder=r'D:\C++窗体项目\图像处理软件框架\python后端\循环播放示例\B', c_folder=r'D:\C++窗体项目\图像处理软件框架\python后端\循环播放示例\C'):
    # 调用父类初始化

    super().__init__(port=port, upload_folder=upload_folder,
                     b_folder=b_folder, c_folder=c_folder)


  def button1_fun(self, user_ip):
      print(f"来自 {user_ip} 的按钮1被点击")
      self.show_b_images = True
      self.play_video = True
      self.processing_status = "启动运行！"

      if not self.is_playing:
          self.is_playing = True
          self.xiancheng_stop = 0
          self.xiancheng_stop = 0
          threading.Thread(target=self.update_frame, daemon=True).start()#启动update_frame的线程函数，也就是下面的

# 下面是点击运行按钮后会执行的程序，提供的例程是循环播放当前路径文件夹C中的图片，如果你不需要循环执行来播放动画（算法程序是单次的），那么函数体内从程序可以全部删除
  def update_frame(self):
    frame_files1 = []
    for ext in ['*.png', '*.jpg', '*.jpeg', '*.gif']:
      frame_files1.extend(glob.glob(os.path.join(self.app.config['C_FOLDER'], ext)))
    frame_count1 = len(frame_files1)

    frame_index1 = 0

    while self.is_playing and frame_count1 > 0:
      print(self.prams)  # 这是点击发送后从消息框获取的参数，默认是1，从这里启动你的程序，后面可以删除
      current_frame = frame_files1[frame_index1]
      self.frame_data = self._get_image_data_original(
        current_frame)  # self.frame_data 是每一帧刷新的图像内容，会自动提交给网页，你只要在这里更新就行，按住CTRL查看编码协议，不要像我这样从磁盘读取，将算法输出的PIL格式转换成这个格式直接显示到前端
      frame_index1 = (frame_index1 + 1) % frame_count1
      self.zhuangtai=frame_index1#右上角的状态显示栏的内容
      time.sleep(0.05)  # 控制动画播放间隔
      if self.xiancheng_stop == 1:  # 由结束按钮，删除装置图像按钮，显示缓存按钮控制共同控制，退出while循环
        self.is_playing = False  # 避免线程重复执行，不要动
        break
#如果要调整按钮的功能，请像上面一样每个按钮开新的线程
  def button2_fun(self,user_ip):
      print(f"来自 {user_ip} 的按钮2被点击")
      self.xiancheng_stop = 0
      self._clean_folders()
      self.processing_status = "清除完成！"

  def button3_fun(self,user_ip):
      print(f"来自 {user_ip} 的按钮3被点击")
      self.show_b_images = True
      self.processing_status = "重新显示！"
  def button4_fun(self,user_ip):
      self.xiancheng_stop = 1
      self.processing_status = "结束执行！"
      print(f"来自 {user_ip} 的按钮4被点击")
  def buttonM_fun(self, user_ip):
      message = request.form['message']
      print(f"来自 {user_ip} 的消息: {message}")
      self.prams = message


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", type=int, default=5000, help="Port to run the server")
    args = parser.parse_args()

    app1 = UserPicutureApp(port=args.port)
    app1.run()

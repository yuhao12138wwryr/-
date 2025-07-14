from flask import Flask, render_template, request, redirect, url_for, send_from_directory, jsonify
import os
from werkzeug.utils import secure_filename
import glob
import base64
import time
import shutil
import threading
from datetime import datetime
import sys

class FlaskVideoApp:
    def __init__(self, port=5000, upload_folder='user_uploads', b_folder='B', c_folder='C'):
        self.app = Flask(__name__)
        self.port = port
        self.upload_folder = upload_folder
        self.b_folder = b_folder
        self.c_folder = c_folder
        self.prams="1"
        # 配置
        self.allowed_extensions = {'png', 'jpg', 'jpeg', 'gif', 'mp4', 'mov', 'avi', 'pdf',
                                   'txt', 'doc', 'docx', 'xls', 'xlsx', 'zip', 'rar'}

        self.app.config['UPLOAD_FOLDER'] = self.upload_folder
        self.app.config['B_FOLDER'] = self.b_folder
        self.app.config['C_FOLDER'] = self.c_folder
        self.app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024

        # 状态变量
        self.frame_data = None
        self.frame_index = 0
        self.frame_count = 0
        self.is_playing = False
        self.frame_files = []
        self.xiancheng_stop = 0
        self.processing_status = ""
        self.show_b_images = False
        self.play_video = False
        self.zhuangtai="正常"
        # 确保目录存在
        os.makedirs(self.upload_folder, exist_ok=True)
        os.makedirs(self.b_folder, exist_ok=True)
        os.makedirs(self.c_folder, exist_ok=True)

        # 注册路由
        self._register_routes()

    def button1_fun(self, user_ip):
        print(f"来自 {user_ip} 的按钮1被点击")
        self.show_b_images = True
        self.play_video = True
        self.processing_status = "启动运行！"

        if not self.is_playing:
            self.is_playing = True
            self.xiancheng_stop = 0
            self.xiancheng_stop = 0
            threading.Thread(target=self.update_frame, daemon=True).start()
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
    def _register_routes(self):
        @self.app.route('/get_current_time')
        def get_current_time():
            return jsonify({'current_time': self.zhuangtai})

        @self.app.route('/', methods=['GET', 'POST'])
        def upload_file():
            user_ip = request.remote_addr
            user_folder = self._get_user_folder(user_ip)

            self.show_b_images = False
            self.play_video = False

            if request.method == 'POST':
                if 'files' in request.files:
                    self._handle_file_upload(request.files.getlist('files'), user_folder)
                    return redirect(request.url)

                if 'button1' in request.form:
                    self.button1_fun(user_ip)

                elif 'button2' in request.form:
                   self.button2_fun(user_ip)

                elif 'button3' in request.form:
                    self.button3_fun(user_ip)

                elif 'button4' in request.form:
                    self.button4_fun(user_ip)

                elif 'message' in request.form:
                    self.buttonM_fun(request)


            b_images = []
            if self.show_b_images:
                b_images = self._get_b_images()

            return render_template('index.html',
                                   show_b_images=self.show_b_images,
                                   b_images=b_images,
                                   user_ip=user_ip,
                                   processing_status=self.processing_status,
                                   play_video=self.play_video,
                                   frame_count=self.frame_count)

        @self.app.route('/get_frame')
        def get_frame():
            return jsonify({
                'image_data': self.frame_data,
                'frame_index': self.frame_index,
                'frame_count': self.frame_count
            })

        @self.app.route('/uploads/<ip_folder>/<filename>')
        def uploaded_file(ip_folder, filename):
            return send_from_directory(os.path.join(self.app.config['UPLOAD_FOLDER'], ip_folder), filename)

    def _get_user_folder(self, ip):
        ip_folder = os.path.join(self.app.config['UPLOAD_FOLDER'], "1")
        os.makedirs(ip_folder, exist_ok=True)
        return ip_folder

    def _get_b_images(self):
        b_images = []
        for img_path in self._get_b_folder_images():
            img_data = self._get_image_data_original(img_path)
            if img_data:
                b_images.append({
                    'data': img_data,
                    'path': img_path
                })
        return b_images

    def _get_b_folder_images(self):
        self.frame_files = []
        for ext in ['*.png', '*.jpg', '*.jpeg', '*.gif']:
            self.frame_files.extend(glob.glob(os.path.join(self.app.config['B_FOLDER'], ext)))
        return self.frame_files

    def _get_image_data_original(self, image_path):
        try:
            with open(image_path, 'rb') as f:
                image_data = f.read()

            ext = os.path.splitext(image_path)[1].lower()
            mime_type = f"image/{ext[1:]}" if ext[1:] in ['png', 'jpeg', 'gif'] else 'image/jpeg'

            img_str = base64.b64encode(image_data).decode('utf-8')
            return f"data:{mime_type};base64,{img_str}"
        except Exception as e:
            print(f"Error reading image {image_path}: {e}")
            return None

    def _handle_file_upload(self, files, user_folder):
        for file in files:
            if file.filename == '':
                continue
            if file and self._allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join(user_folder, filename))

    def _allowed_file(self, filename):
        return '.' in filename and \
               filename.rsplit('.', 1)[1].lower() in self.allowed_extensions

    def _clean_folders(self):
        for d in ['B', 'user_uploads']:
            shutil.rmtree(d, ignore_errors=True)
            os.makedirs(d, exist_ok=True)

    def update_frame(self):
        frame_files1 = []
        for ext in ['*.png', '*.jpg', '*.jpeg', '*.gif']:
            frame_files1.extend(glob.glob(os.path.join(self.app.config['C_FOLDER'], ext)))
        frame_count1 = len(frame_files1)

        frame_index1 = 0

        while self.is_playing and frame_count1 > 0:
            current_frame = frame_files1[frame_index1]
            self.frame_data = self._get_image_data_original(current_frame)

            frame_index1 = (frame_index1 + 1) % frame_count1


            time.sleep(0.05)
            if self.xiancheng_stop == 1:
                self.is_playing = False
                break

    def run(self):
        self.app.run(host='0.0.0.0', port=self.port, debug=True, use_reloader=False)




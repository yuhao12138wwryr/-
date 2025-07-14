from flask import Flask, render_template_string, jsonify, request
import io
import base64
from PIL import Image, ImageDraw
import threading
from flask_cors import CORS#前后端不同服务器，例如fetch('http://101.35.50.189:5000/update_map',
image_info_dict = {
    'ditu/youlechang.png': {
        'x': -90,          # 替换为实际的x坐标
        'y': -10,          # 替换为实际的y坐标
        'beilv': 0.0195,     # 替换为实际的比例
        'beilv2': 0.0195     # 替换为实际的比例
    },
    'ditu/xongmaoguan.png': {
        'x': -80,          # 替换为实际的x坐标
        'y': 0,          # 替换为实际的y坐标
        'beilv': 0.0175,     # 替换为实际的比例
        'beilv2': 0.0175     # 替换为实际的比例
    },
    'ditu/gubao1.png': {
        'x': -80,          # 替换为实际的x坐标
        'y': 0,          # 替换为实际的y坐标
        'beilv': 0.025,     # 替换为实际的比例
        'beilv2': 0.025     # 替换为实际的比例
    },
    'ditu/gubao2.png': {
        'x': -90,          # 替换为实际的x坐标
        'y': 0,          # 替换为实际的y坐标
        'beilv': 0.025,     # 替换为实际的比例
        'beilv2': 0.025     # 替换为实际的比例
    },
    'ditu/gubao3.png': {
        'x': -95,          # 替换为实际的x坐标
        'y': 10,          # 替换为实际的y坐标
        'beilv': 0.028,    # 替换为实际的比例
        'beilv2': 0.028     # 替换为实际的比例
    },
    'ditu/tiangong.png': {
        'x': -100,  # 替换为实际的x坐标
        'y': -110,  # 替换为实际的y坐标
        'beilv': 0.019, # 替换为实际的比例
        'beilv2': 0.019 # 替换为实际的比例
    },
    'ditu/taikong1.png': {
        'x': -85,  # 替换为实际的x坐标
        'y': 5,  # 替换为实际的y坐标
        'beilv': 0.03,  # 替换为实际的比例
        'beilv2': 0.03  # 替换为实际的比例
    },
    'ditu/taikong2.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': 0,  # 替换为实际的y坐标
        'beilv': 0.028, # 替换为实际的比例
        'beilv2': 0.028 # 替换为实际的比例
    },
    'ditu/taikong3.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': -15,  # 替换为实际的y坐标
        'beilv': 0.027, # 替换为实际的比例
        'beilv2': 0.027 # 替换为实际的比例
    },
    'ditu/senlingmuchang.png': {
        'x': -95,  # 替换为实际的x坐标
        'y': -85,  # 替换为实际的y坐标
        'beilv': 0.015, # 替换为实际的比例
        'beilv2': 0.015 # 替换为实际的比例
    },
    'ditu/jindianzhijia1.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': -50,  # 替换为实际的y坐标
        'beilv': 0.022, # 替换为实际的比例
        'beilv2': 0.022 # 替换为实际的比例
    },
    'ditu/jindianzhijia2.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': -50,  # 替换为实际的y坐标
        'beilv': 0.0195, # 替换为实际的比例
        'beilv2': 0.0195 # 替换为实际的比例
    },
    'ditu/jindianzhijia3.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': -50,  # 替换为实际的y坐标
        'beilv': 0.0255 ,# 替换为实际的比例
        'beilv2': 0.0255 # 替换为实际的比例
    },
    'ditu/youlun1.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': 0,  # 替换为实际的y坐标
        'beilv': 0.0255 ,# 替换为实际的比例
        'beilv2': 0.0255 # 替换为实际的比例
    },
    'ditu/youlun2.png': {
        'x': -90,  # 替换为实际的x坐标
        'y': 10,  # 替换为实际的y坐标
        'beilv': 0.03, # 替换为实际的比例
        'beilv2': 0.03 # 替换为实际的比例
    },
    'ditu/youlun3.png': {
        'x': 20,  # 替换为实际的x坐标
        'y': 10,  # 替换为实际的y坐标
        'beilv': 0.0195 ,# 替换为实际的比例
         'beilv2': 0.0195 # 替换为实际的比例
    },
    'ditu/jiudian.png': {
        'x': -100,  # 替换为实际的x坐标
        'y': -20,  # 替换为实际的y坐标
        'beilv': 0.018, # 替换为实际的比例
        'beilv2': 0.027 # 替换为实际的比例
    }
}
# 初始化设置
def read_config(file_path):
    with open(file_path, 'r', encoding='windows-1252') as f:
        config = {}
        for line in f:
            key, value = line.strip().split(':', 1)
            key = key.strip()
            value = value.strip()
            # 处理元组类型的值
            if value.startswith('(') and value.endswith(')'):
                value = tuple(map(int, value[1:-1].split(',')))
            config[key] = value
        return config

# 从txt文件中读取配置
config = read_config('map_info.txt')

# 提取读取到的值
image_path = config.get('image_path', 'ditu/gubao1.png')
js_x=image_info_dict[image_path]['x']
js_y=image_info_dict[image_path]['y']
js_beilv=image_info_dict[image_path]['beilv']
js_beilv2=image_info_dict[image_path]['beilv2']

left_bottom = config.get('left_bottom', (900, 0))
right_top = config.get('right_top', (17000, 8600))

# 打印结果
print(f"Image Path: {image_path}")
print(f"Left Bottom: {left_bottom}")
print(f"Right Top: {right_top}")

# 加载背景图像
img = Image.open(image_path)
img_width, img_height = img.size


# 计算缩放比例
scale_x = img_width / (right_top[0] - left_bottom[0])
scale_y = img_height / (right_top[1] - left_bottom[1])

# 坐标映射函数
def map_to_image_coordinates(point, left_bottom, scale_x, scale_y):
    x, y = point
    mapped_x = (x - left_bottom[0]) * scale_x
    mapped_y = img_height - (y - left_bottom[1]) * scale_y
    return int(mapped_x), int(mapped_y)

# 初始化Flask应用
app = Flask(__name__)
app2 = Flask(__name__)

CORS(app)
CORS(app2)
# 全局变量存储坐标
mao_coords = {'x': 0, 'y': 0}
mao_coords2 = {'x': 0, 'y': 0}
triangle_coords2 = []  # 存储紫色三角形坐标
triangle_coords = []  # 存储紫色三角形坐标
yellow_triangle_coords = []  # 存储紫黄色三角形坐标
yellow_triangle_coords2 = []  # 存储紫黄色三角形坐标
lock = threading.Lock()

# 初始化图像，编码为Base64
img_byte_arr = io.BytesIO()
img.save(img_byte_arr, format='PNG')
img_byte_arr.seek(0)
base_image_b64 = base64.b64encode(img_byte_arr.read()).decode('utf-8')

# 接口：更新坐标
@app.route('/', methods=['POST'])
def process_data():
    global mao_coords, triangle_coords, yellow_triangle_coords
    try:
        data = request.get_json()
        print(data)
        with lock:
            if 'yingshen' in data:
                triangle_coords.append({'x': data['yingshen'].get('x', 0), 'y': data['yingshen'].get('y', 0)})
                return jsonify({"status": "success"}), 200
            elif 'mao' in data:
                mao_coords = {'x': data['mao'].get('x', 0), 'y': data['mao'].get('y', 0)}
                return jsonify({"status": "success"}), 200
            elif 'yellow_triangle' in data:  # 处理黄色三角形坐标
                yellow_triangle_coords.append({'x': data['yellow_triangle'].get('x', 0), 'y': data['yellow_triangle'].get('y', 0)})
                return jsonify({"status": "success"}), 200
            else:
                return jsonify({"status": "error", "message": "Invalid data format"}), 400
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
# 接口：获取坐标数据
@app.route('/get_updates', methods=['GET'])
def get_updates():
    try:
        with lock:
            return jsonify({
                "mao": mao_coords,
                "triangles": triangle_coords,
                "yellow_triangle": yellow_triangle_coords  # 返回黄色三角形坐标
            }), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
@app.route('/get_updates2', methods=['GET'])
def get_updates2():
    try:
        with lock:
            mao_coords2['x'] = int(mao_coords['x']*js_beilv+js_x)
            mao_coords2['y'] = int(-mao_coords['y']*js_beilv2+js_y)
            triangle_coords2 = [{'x': int(item['x']*js_beilv+js_x), 'y': int(-item['y']*js_beilv2+js_y)} for item in triangle_coords]
            yellow_triangle_coords2 = [{'x': int(item['x']*js_beilv+js_x), 'y': int(-item['y']*js_beilv2+js_y)} for item in yellow_triangle_coords]

            return jsonify({
                "mao":mao_coords2,
                "triangles": triangle_coords2,
                "yellow_triangle": yellow_triangle_coords2  # 返回黄色三角形坐标
            }), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
# 路由：返回HTML页面
@app.route('/ditu')
def index():
    return render_template_string(f'''
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Dynamic Map</title>
            <style>
                body {{
                    margin: 0;
                    padding: 0;
                    height: 100vh;
                    overflow: hidden;
                    background-color: #f0f0f0;
                }}
                #container {{
                    position: relative;
                    width: 100vw;
                    height: 100vh;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                }}
                img, canvas {{
                    position: absolute;
                    top: 0;
                    left: 0;
                    width: 100%;
                    height: 100%;
                    object-fit: contain;
                }}
            </style>
        </head>
        <body>
            <div id="container">
                <img id="base_image" src="data:image/png;base64,{base_image_b64}" alt="基础图像">
                <canvas id="overlay"></canvas>
            </div>
            <script>
                const canvas = document.getElementById('overlay');
                const ctx = canvas.getContext('2d');
                const img = document.getElementById('base_image');

                let imgWidth = {img_width};
                let imgHeight = {img_height};
                let scale = 1; // 全局缩放比例

                function resizeCanvas() {{
                    const container = document.getElementById('container');
                    const containerWidth = container.clientWidth;
                    const containerHeight = container.clientHeight;

                    // 计算缩放比例
                    scale = Math.min(containerWidth / imgWidth, containerHeight / imgHeight);
                    canvas.width = imgWidth * scale;
                    canvas.height = imgHeight * scale;
                }}

                function mapToImageCoordinates(x, y) {{
                    const scaleX = canvas.width / ({right_top[0]} - {left_bottom[0]});
                    const scaleY = canvas.height / ({right_top[1]} - {left_bottom[1]});
                    const mappedX = (x - {left_bottom[0]}) * scaleX;
                    const mappedY = canvas.height - (y - {left_bottom[1]}) * scaleY;
                    return [mappedX, mappedY];
                }}

                function updateCanvas() {{
                    fetch('http://101.35.50.189:5000/get_updates')
                        .then(response => response.json())
                        .then(data => {{
                            ctx.clearRect(0, 0, canvas.width, canvas.height);

                            // 绘制红圆
                            if (data.mao) {{
                                const [x, y] = mapToImageCoordinates(data.mao.x, data.mao.y);
                                ctx.beginPath();
                                ctx.arc(x, y, 7 * scale, 0, Math.PI * 2); // 根据缩放比例调整圆的大小
                                ctx.fillStyle = 'red';
                                ctx.fill();
                            }}

                            // 绘制紫色三角形
                            data.triangles.forEach(triangle => {{
                                const [x, y] = mapToImageCoordinates(triangle.x, triangle.y);
                                ctx.fillStyle = 'purple';
                                ctx.beginPath();
                                ctx.moveTo(x, y - 10 * scale); // 根据缩放比例调整三角形大小
                                ctx.lineTo(x - 10 * scale, y + 10 * scale);
                                ctx.lineTo(x + 10 * scale, y + 10 * scale);
                                ctx.closePath();
                                ctx.fill();
                            }});

                            // 绘制黄色三角形
                            data.yellow_triangle.forEach(triangle => {{
                                const [x, y] = mapToImageCoordinates(triangle.x, triangle.y);
                                ctx.fillStyle = 'yellow';
                                ctx.beginPath();
                                ctx.moveTo(x, y - 10 * scale); // 根据缩放比例调整三角形大小
                                ctx.lineTo(x - 10 * scale, y + 10 * scale);
                                ctx.lineTo(x + 10 * scale, y + 10 * scale);
                                ctx.closePath();
                                ctx.fill();
                            }});
                        }})
                        .catch(error => console.error('Error updating canvas:', error));
                }}

                window.addEventListener('resize', () => {{
                    resizeCanvas();
                    updateCanvas(); // 窗口大小变化时重新绘制
                }});
                resizeCanvas();
                setInterval(updateCanvas, 200);
            </script>
        </body>
        </html>
    ''')
# 存储地图文件信息（模拟你的文件信息）
map_files = {
    "gubao1": {"image_path": 'ditu/gubao1.png', "left_bottom": (900, 0), "right_top": (17000, 8600)},
    "gubao2": {"image_path": 'ditu/gubao2.png', "left_bottom": (0, 0), "right_top": (13320, 8300)},
    "gubao3": {"image_path": 'ditu/gubao3.png', "left_bottom": (0, 0), "right_top": (13320, 8300)},
    "tiangong": {"image_path": 'ditu/tiangong.png', "left_bottom": (0, -4000), "right_top": (23500, 4500)},
    "taikong1": {"image_path": 'ditu/taikong1.png', "left_bottom": (0, 0), "right_top": (14400, 8000)},
    "taikong2": {"image_path": 'ditu/taikong2.png', "left_bottom": (0, 0), "right_top": (15400, 8000)},
    "taikong3": {"image_path": 'ditu/taikong3.png', "left_bottom": (0, 0), "right_top": (16000, 6000)},
    "senlingmuchang": {"image_path": 'ditu/senlingmuchang.png', "left_bottom": (0, -5000), "right_top": (30000, 5500)},
    "youlechang": {"image_path": 'ditu/youlechang.png', "left_bottom": (0, -1000), "right_top": (23000, 7000)},
    "xongmaoguan": {"image_path": 'ditu/xongmaoguan.png', "left_bottom": (0, 0), "right_top": (23500, 12000)},
    "jindianzhijia1": {"image_path": 'ditu/jindianzhijia1.png', "left_bottom": (0, -1800), "right_top": (20100, 6600)},
    "jindianzhijia2": {"image_path": 'ditu/jindianzhijia2.png', "left_bottom": (0, -1700), "right_top": (22200, 6300)},
    "jindianzhijia3": {"image_path": 'ditu/jindianzhijia3.png', "left_bottom": (0, -1800), "right_top": (17100, 6600)},
    "youlun1": {"image_path": 'ditu/youlun1.png', "left_bottom": (0, 0), "right_top": (17300, 7150)},
    "youlun2": {"image_path": 'ditu/youlun2.png', "left_bottom": (0, 0), "right_top": (14550, 7700)},
    "youlun3": {"image_path": 'ditu/youlun3.png', "left_bottom": (0, 0), "right_top": (14550, 12550)},
    "jiudian": {"image_path": 'ditu/jiudian.png', "left_bottom": (0, 0), "right_top": (25000, 6000)}
}

# 更新选择的地图信息并保存到txt文件
def save_to_txt(map_name, map_info):
    with open('map_info.txt', 'w') as file:
        file.write(f"image_path:{map_info['image_path']}\n")
        file.write(f"left_bottom:{map_info['left_bottom']}\n")
        file.write(f"right_top:{map_info['right_top']}\n")


# 前端页面 (直接嵌入在Python文件里)
@app2.route('/')
def index2():
    return render_template_string('''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Map Selection</title>
    </head>
    <body>
        <h1>Map Selection</h1>
        <label for="map_select">Choose a map:</label>
        <select id="map_select">
            <option value="gubao1">古堡1</option>
            <option value="gubao2">古堡2</option>
            <option value="gubao3">古堡3</option>
            <option value="tiangong">天宫</option>
            <option value="taikong1">太空1</option>
            <option value="taikong2">太空2</option>
            <option value="taikong3">太空3</option>
            <option value="senlingmuchang">森林牧场</option>
            <option value="youlechang">游乐场</option>
            <option value="xongmaoguan">熊猫馆</option>
            <option value="jindianzhijia1">经典之家1</option>
            <option value="jindianzhijia2">经典之家2</option>
            <option value="jindianzhijia3">经典之家3</option>
            <option value="youlun1">邮轮1</option>
            <option value="youlun2">邮轮2</option>
            <option value="youlun3">邮轮3</option>
            <option value="jiudian">酒店</option>
        </select>
        <button onclick="updateMap()">Select Map</button>

        <script>
            function updateMap() {
                const mapName = document.getElementById('map_select').value;

                fetch('http://101.35.50.189:5000/update_map', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: 'map_name=' + mapName
                })
                .then(response => response.json())
                .then(data => {
                    // No popup, only backend update
                });
            }
        </script>
    </body>
    </html>
    ''')

# 更新地图选择的后端路由
@app2.route('/update_map', methods=['POST'])
def update_map2():
    map_name = request.form.get('map_name')
    if map_name in map_files:
        selected_map = map_files[map_name]
        save_to_txt(map_name, selected_map)
        import signal
        import os
        # 向当前进程发送 SIGINT 信号，模拟 Ctrl + C
        os.kill(os.getpid(), signal.SIGINT)

        return jsonify({"status": "success", "message": f"Map {map_name} selected and saved to txt."}), 200
    else:
        return jsonify({"status": "error", "message": "Invalid map selected."}), 400
def run_app1():
    app.run(host='0.0.0.0', port=5000)
    CORS(app)

def run_app2():
    app2.run(host='0.0.0.0', port=5001)
    CORS(app2)
import threading
from threading import Thread
# 启动Flask应用
if __name__ == '__main__':
    t1 = Thread(target=run_app1)
    t2 = Thread(target=run_app2)
    t1.start()
    t2.start()
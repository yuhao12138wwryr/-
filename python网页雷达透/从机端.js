"ui";

// 发送通知
var title = "138的保活服务(你一定要活)";
var text = "应用正在后台运行";

importClass(android.app.NotificationManager);
importClass(android.app.NotificationChannel);
importClass(android.content.Context);

// 获取通知管理器
var manager = context.getSystemService(Context.NOTIFICATION_SERVICE);

// 创建通知通道（Android 8.0+ 需要）
var channelId = "autoxjs_keep_alive";
if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
    var channel = new NotificationChannel(channelId, "AutoX.js 保活", NotificationManager.IMPORTANCE_LOW);
    manager.createNotificationChannel(channel);
}

// 创建通知
var notification = new android.app.Notification.Builder(context, channelId)
    .setContentTitle(title)
    .setContentText(text)
    .setSmallIcon(android.R.drawable.ic_dialog_info)
    .setOngoing(true)  // 设置常驻通知
    .build();

// 发送通知
manager.notify(1, notification);
toast("保活通知已启动");

// 防止脚本退出
setInterval(() => {}, 1000);



var num1 =0
var num2 =0
var num3 =1
var storage = storages.create("my_storage");

ui.layout(
    <vertical padding="16">
        <text textSize="16sp" textColor="black" text="通过下面三个参数可以调整绘制的位置。屏幕的原点在左上角，下面第一个数是x轴偏移，第二个数是y轴偏移,往下和往右是xy增大的方向,第三个数是缩放倍率" />
        <input id="input1" inputType="text" hint="数字1"text="60" />
        <input id="input2" inputType="text" hint="数字2"text="180" />
        <input id="input3" inputType="text" hint="数字3" text="1"/>
        <button id="save" text="保存并启动" />
    </vertical>
);

// 读取存储的值，并填充输入框
ui.input1.setText(storage.get("num1", "60"));
ui.input2.setText(storage.get("num2", "280"));
ui.input3.setText(storage.get("num3", "1"));


var url = "http://101.35.50.189:5000/get_updates2";
var beilv = 1;
var windowMao = null; // 存储 "mao" 点的 window

// 创建浮动窗口
function createFloatingText(x1, y1, text1) {
    var window = floaty.window(
        <text id="text" textSize="10sp" textColor="red"/>
    );

    ui.run(() => {

        window.text.setText(text1);
        window.setPosition(x1, y1);
    });

    return window; // 返回窗口对象，方便后续更新
}

// 初始化固定的两个点
var window2 = createFloatingText(-110*num3+num1, -260*num3+num2, "🟣");
var window3 = createFloatingText(-110*num3+num1, -260*num3+num2, "🟣");
var window4 = createFloatingText(-110*num3+num1, -260*num3+num2, "🟢");
var window5 = createFloatingText(-110*num3+num1, -260*num3+num2, "🟢");
// **每次请求都创建新线程**
function getUpdates() {
    threads.start(function () {
        try {
            var options = { timeout: 140 }; // 超时时间 5 秒
            var res = http.get(url, options);

            if (res.statusCode == 200) {
                var json = res.body.json();
                if (json.hasOwnProperty("mao")) {
                    var mao = json.mao;
                    var newX = mao.x *num3+num1;
                    var newY = mao.y * num3+num2;

                    ui.run(() => {
                        if (windowMao === null) {
                            windowMao = createFloatingText(newX, newY, "🔴");
                        } else {
                            windowMao.setPosition(newX, newY);
                        }
                    });
                }
            } else {
                toast("http erro")
            }
            if (json.hasOwnProperty("triangles")) {

        var yingshe=json.triangles;
        var hudun=json.yellow_triangle;
        if (yingshe && yingshe.length > 0 && yingshe[0] !== undefined)
        {
        var yingshe_newX = yingshe[0].x *num3+num1;
        var yingshe_newY = yingshe[0].y * num3+num2;
        }
        else
        {
        var yingshe_newX = -110*num3+num1; // 默认值
        var yingshe_newY =-260*num3+num2;
        }
        if (yingshe && yingshe.length > 1 && yingshe[1] !== undefined) {
        // yingshe[1] 存在，可以安全访问
        var yingshe_newX3 = yingshe[1].x * num3 + num1;
        var yingshe_newY3 = yingshe[1].y * num3 + num2;
        } else {

        var yingshe_newX3 = -110*num3+num1; // 默认值
        var yingshe_newY3 =-260*num3+num2;
}
         if (hudun && hudun.length > 0 && hudun[0] !== undefined)
        {
        var hudun_newX = hudun[0].x *num3+num1;
        var hudun_newY = hudun[0].y * num3+num2;
        }
        else
        {
        var hudun_newX = -110*num3+num1; // 默认值
        var hudun_newY =-260*num3+num2;
        }
        if (hudun && hudun.length > 1 && hudun[1] !== undefined) {
        // yingshe[1] 存在，可以安全访问
        var hudun_newX3 = hudun[1].x * num3 + num1;
        var hudun_newY3 = hudun[1].y * num3 + num2;
        } else {

        var hudun_newX3 = -110*num3+num1; // 默认值
        var hudun_newY3 =-260*num3+num2;
}

        ui.run(() => {
            if (window2 === null) {
                window2 = createFloatingText(yingshe_newX, yingshe_newY, "🟣");
            } else {
                window2.setPosition(yingshe_newX, yingshe_newY);
            }
            if (window3 === null) {
                window3 = createFloatingText(yingshe_newX3, yingshe_newY3, "🟣");
            } else {
                window3.setPosition(yingshe_newX3, yingshe_newY3);
            }

                        if (window4 === null) {
                window4 = createFloatingText(hudun_newX, hudun_newY, "🟢");
            } else {
                window4.setPosition(hudun_newX, hudun_newY);
            }
            if (window5 === null) {
                window5 = createFloatingText(hudun_newX3, hudun_newY3, "🟢");
            } else {
                window5.setPosition(hudun_newX3, hudun_newY3);
            }

        });
    }
        } catch (e) {
            log("请求错误: " + e);
            toast("服务器断开")
        }
    });
}
var an=0;
var updateInterval = null; // 记录定时器 ID
// 按钮点击事件，保存输入的数字
ui.save.click(() => {
    an=1;
    storage.put("num1", ui.input1.getText() + "");
    storage.put("num2", ui.input2.getText() + "");
    storage.put("num3", ui.input3.getText() + "");
    num1 = parseFloat(storage.get("num1", "0"));
    num2 = parseFloat(storage.get("num2", "0"));
    num3 = parseFloat(storage.get("num3", "0"));
    toast("保存成功");
    window2.setPosition(-110*num3+num1, -260*num3+num2);
    window3.setPosition(-110*num3+num1, -260*num3+num2);
    if (updateInterval) {
        clearInterval(updateInterval);
        updateInterval = null;
    }
    updateInterval = setInterval(getUpdates, 150);
});
// 递归的定时器函数
function checkAndRestart() {
    // 执行需要周期性运行的任务
    if (updateInterval == null && an==1) {
        log("检测到 setInterval 被终止，尝试重启...");
        updateInterval = setTimeout(getUpdates, 100); // 递归调用 getUpdates
    }

    // 设定每隔 5 秒再次检查一次
    setTimeout(checkAndRestart, 1000);
}

// 启动递归任务
checkAndRestart();
#include "QtWidgetsApplication2.h"
#include "QtWidgetsClass.h"
#include <QtWidgets/QApplication>

#include <QQuickWindow>

int main(int argc, char *argv[])
{
    qputenv("QSG_RENDER_LOOP", "basic");//
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);//这2行解决了缩放卡屏幕的问题
    QApplication app(argc, argv);
    // 在main.cpp中全局设置（确保优先使用GPU）

    QtWidgetsApplication2 window;
    window.show();
    return app.exec();
}

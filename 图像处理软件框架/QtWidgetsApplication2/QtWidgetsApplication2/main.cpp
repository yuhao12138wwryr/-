#include "QtWidgetsApplication2.h"
#include "QtWidgetsClass.h"
#include <QtWidgets/QApplication>

#include <QQuickWindow>

int main(int argc, char *argv[])
{
    qputenv("QSG_RENDER_LOOP", "basic");//
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);//��2�н�������ſ���Ļ������
    QApplication app(argc, argv);
    // ��main.cpp��ȫ�����ã�ȷ������ʹ��GPU��

    QtWidgetsApplication2 window;
    window.show();
    return app.exec();
}

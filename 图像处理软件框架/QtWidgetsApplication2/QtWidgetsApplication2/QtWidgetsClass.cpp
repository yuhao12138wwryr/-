#include "QtWidgetsClass.h"
#include "ui_QtWidgetsClass.h"
#include <QWebEngineView>
#include <QUrl>
#include <QWebEnginePage>  // 用于处理页面错误
#include <QTimer>          // 用于定时重试
#include <QWebEngineSettings> // 用于禁用错误页面
#include <QFile>           // 用于检查本地文件是否存在
#include <QDir>            // 用于处理路径
#include <QDebug>          // 用于调试输出

QtWidgetsClass::QtWidgetsClass(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // 获取提升后的 QWebEngineView
    QWebEngineView* webView = ui.webEngineView;
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 禁用错误页面显示
    webView->page()->settings()->setAttribute(QWebEngineSettings::ErrorPageEnabled, false);

    // 连接错误信号
    connect(webView->page(), &QWebEnginePage::loadFinished, [webView](bool ok) {
        static bool isShowingLocalFile = true;

        if (isShowingLocalFile) {
            // 如果当前显示的是本地文件，尝试加载网络页面
            isShowingLocalFile = false;
            webView->load(QUrl("http://192.168.3.178:5000/"));
        }
        else if (!ok) {
            // 如果网络加载失败，返回显示本地文件
            isShowingLocalFile = true;

            // 使用相对路径
            QString localPath = QDir::current().filePath("index.html");
            QFile file(localPath);

            if (file.exists()) {
                webView->setUrl(QUrl::fromLocalFile(file.fileName()));
            }
            else {
                qDebug() << "Local file not found at:" << localPath;
                webView->setHtml("<html><body><h1>Local file not found</h1></body></html>");
            }

            // 设置重试定时器
            QTimer::singleShot(1000, [webView]() {
                webView->load(QUrl("http://192.168.3.178:5000/"));
                });
        }
        });

    // 初始加载本地HTML文件 - 使用相对路径
    QString localPath = QDir::current().filePath("index.html");
    QFile file(localPath);

    if (file.exists()) {
        webView->setUrl(QUrl::fromLocalFile(file.fileName()));
    }
    else {
        qDebug() << "Local file not found at:" << localPath;
        webView->setHtml("<html><body><h1>Local file not found</h1></body></html>");
    }
}

QtWidgetsClass::~QtWidgetsClass()
{
}
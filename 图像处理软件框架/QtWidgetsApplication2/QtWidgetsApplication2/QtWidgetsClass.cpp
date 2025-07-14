#include "QtWidgetsClass.h"
#include "ui_QtWidgetsClass.h"
#include <QWebEngineView>
#include <QUrl>
#include <QWebEnginePage>  // ���ڴ���ҳ�����
#include <QTimer>          // ���ڶ�ʱ����
#include <QWebEngineSettings> // ���ڽ��ô���ҳ��
#include <QFile>           // ���ڼ�鱾���ļ��Ƿ����
#include <QDir>            // ���ڴ���·��
#include <QDebug>          // ���ڵ������

QtWidgetsClass::QtWidgetsClass(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // ��ȡ������� QWebEngineView
    QWebEngineView* webView = ui.webEngineView;
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // ���ô���ҳ����ʾ
    webView->page()->settings()->setAttribute(QWebEngineSettings::ErrorPageEnabled, false);

    // ���Ӵ����ź�
    connect(webView->page(), &QWebEnginePage::loadFinished, [webView](bool ok) {
        static bool isShowingLocalFile = true;

        if (isShowingLocalFile) {
            // �����ǰ��ʾ���Ǳ����ļ������Լ�������ҳ��
            isShowingLocalFile = false;
            webView->load(QUrl("http://192.168.3.178:5000/"));
        }
        else if (!ok) {
            // ����������ʧ�ܣ�������ʾ�����ļ�
            isShowingLocalFile = true;

            // ʹ�����·��
            QString localPath = QDir::current().filePath("index.html");
            QFile file(localPath);

            if (file.exists()) {
                webView->setUrl(QUrl::fromLocalFile(file.fileName()));
            }
            else {
                qDebug() << "Local file not found at:" << localPath;
                webView->setHtml("<html><body><h1>Local file not found</h1></body></html>");
            }

            // �������Զ�ʱ��
            QTimer::singleShot(1000, [webView]() {
                webView->load(QUrl("http://192.168.3.178:5000/"));
                });
        }
        });

    // ��ʼ���ر���HTML�ļ� - ʹ�����·��
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
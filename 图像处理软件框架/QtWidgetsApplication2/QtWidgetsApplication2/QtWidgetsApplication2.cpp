#include "QtWidgetsApplication2.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QWebEngineView>
#include <map>
#include <utility> // for std::pair
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <sstream>
#include "QuadrupleBinding.h"
#include <QTabBar>  // �����������
#include <QMouseEvent>  // �����������
#include <QDir>
#include <QTimer>
#include <QWebEngineSettings>
ServerThread::ServerThread(QObject* parent, QMenu* menu)
    : QThread(parent), menu(menu)
{
}

void ServerThread::run()
{
    server = new QTcpServer();
    if (!server->listen(QHostAddress::Any, 12345)) {//������������12345
        emit newMessageReceived("Server could not start: " + server->errorString());
        return;
    }

    connect(server, &QTcpServer::newConnection, [this]() {
        QTcpSocket* socket = server->nextPendingConnection();

        connect(socket, &QTcpSocket::readyRead, [this, socket]() {
            QByteArray data = socket->readAll();
            QString message = QString::fromUtf8(data);
            emit newMessageReceived(message);
            });

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        });

    exec();
}

QtWidgetsApplication2::QtWidgetsApplication2(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::QtWidgetsApplication2Class)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 7);

    // ɾ��Ĭ�Ϸ�ҳ
    ui->toolBox->removeItem(0);
    ui->toolBox->removeItem(0);

    // ��ʼ�� tabWidget
    QTabWidget* tabWidget = ui->tabWidget;
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    QWidget* widget = tabWidget->widget(1); // ��ȡ��һ��ѡ�������
    tabWidget->removeTab(1);               // �Ƴ�ѡ������Զ�ɾ��widget��
    widget = tabWidget->widget(0); // ��ȡ��2��ѡ�������
    tabWidget->removeTab(0); 
    QWebEngineView* webView = new QWebEngineView(tabWidget);


    QString htmlPath = QCoreApplication::applicationDirPath() + "/a.html";
    webView->load(QUrl::fromLocalFile(htmlPath));
    int tabIndex = tabWidget->addTab(webView, QString::fromLocal8Bit("�㷨��������"));
    tabWidget->setCurrentIndex(tabIndex);

     // ��¼��һ�εı�ǩҳ�����������л���ǩʱ����֮ǰ��ҳ�������ɾ���������Ż�������������˵����ûִ�С���
    connect(tabWidget, &QTabWidget::currentChanged, [=](int index) mutable {
        // ������һ����ǩҳ������
        if (lastIndex >= 0 && lastIndex < tabWidget->count()) {
            if (QWidget* lastPage = tabWidget->widget(lastIndex)) {
                lastPage->hide();
            }
        }
        // ��ʾ��ǰ��ǩҳ������
        if (index >= 0 && index < tabWidget->count()) {
            if (QWidget* currentPage = tabWidget->widget(index)) {
                currentPage->show();
            }
        }

        lastIndex = index; // ���¼�¼
        });
    // ���ӹرհ�ť�ź�
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [tabWidget, this](int index) {
        QWidget* widget = tabWidget->widget(index);  // ��ȡ��ǩҳ����
        if (auto webView = qobject_cast<QWebEngineView*>(widget)) {
            // 3. ��ȡ��ǰURL
            QUrl currentUrl=webViewMap[webView];
            int port = currentUrl.port();
            sendMessage(currentUrl.host(), 4999, QString::number(port-5000));
        }
        else {
            qWarning() << "�ñ�ǩҳ������ҳ��ͼ";
        }
        // �����ֵ䣬�޸ķ�����������Ŀ����ť�������˰�ť��tabWidget�ͱ�־λ�����tabWidget�ͱ�־λ���ܿ���ҳ�棩
        for (auto& [btn, pair] : this->buttonToWebViewDict) {
            if (pair.first == widget) {  
                btn->setStyleSheet("color: black;");
                pair.second = 0;    // �� second ֵ��Ϊ 0
            }
        }
        tabWidget->removeTab(index);  // �Ƴ���ǩҳ����ʱ widget �����٣�
        });
    tabWidget->tabBar()->installEventFilter(this);  // ����
    // ��ӵ�һ����ҳ
    QWidget* page1 = new QWidget();
    QVBoxLayout* layout1 = new QVBoxLayout(page1);

    ui->toolBox->setStyleSheet(R"(
    QToolBox {
        background: #f0f0f0;
        border: 1px solid #ccc;
    }
    QToolBox::tab {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                  stop:0 #6a6a6a, stop:1 #3a3a3a);
        color: white;
        border-radius: 4px;
        padding: 5px;
        margin: 2px;
    }
    QToolBox::tab:selected {  /* ѡ��ʱ����ʽ */
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                  stop:0 #3a3a3a, stop:1 #6a6a6a);
    }
)");
    int index = ui->toolBox->addItem(page1, QString::fromLocal8Bit("����������"));
    ui->toolBox->setItemEnabled(index, false);  // ���ø���
    // �����������߳�
    serverThread = new ServerThread(this, ui->menu);
    connect(serverThread, &ServerThread::newMessageReceived, this, &QtWidgetsApplication2::updateMenuMessage);
    serverThread->start();
}
// �������¼�������ʵ��
bool QtWidgetsApplication2::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->tabWidget->tabBar() && event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        int tabIndex = ui->tabWidget->tabBar()->tabAt(mouseEvent->pos());
        if (tabIndex >= 0) {
            detachTab(tabIndex);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

// ��������ǩ���뷽��
void QtWidgetsApplication2::detachTab(int index)
{
    QTabWidget* tabWidget = ui->tabWidget;
    QWidget* widget = tabWidget->widget(index);
    QString title = tabWidget->tabText(index);

    // �� tabWidget ���Ƴ�����ɾ�� widget
    tabWidget->removeTab(index);

    // ������������
    QDockWidget* dock = new QDockWidget(title, this);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::NoDockWidgetArea);
    dock->setWidget(widget); // ֱ��ʹ��ԭ widget
    dock->setAttribute(Qt::WA_DeleteOnClose);

    // �������ڹر�ʱ������ӻ� tabWidget
    connect(dock, &QDockWidget::destroyed, this, [this, widget, title]() {
        ui->tabWidget->addTab(widget, title);
        });

    dock->setFloating(true);
    dock->show();
}

void QtWidgetsApplication2::handleButtonClick(QTabWidget* tabWidget, QString s_url, QWidget* page, QPushButton* button) {
    if (button && page && buttonToWebViewDict[button].second != 1) {
        // ֱ�Ӳ�������İ�ť

        button->setStyleSheet("color: red;");
        QWebEngineView* webView = new QWebEngineView(tabWidget);

        binder.addBinding(button, webView, s_url, 1);//������ť��ҳ����URL�����ݽṹ
        webView->load(QUrl(s_url));
        QUrl url2(s_url);
        int port = url2.port();       // 5000 (���δָ���˿ڣ����� -1)
        sendMessage(url2.host(), 4999, QString::number(port - 5000+1972008941));//��֪����������ָ����������4999�ǵ������Ķ˿ڡ�������ʵ����ֱ�Ӷ�url�������ø㣬����������.port������QQ������Ϊ���뿴���Ժ���˭��ά����������ң��Ҹ����㡣
        // ���Ӽ�������ź�
        QObject::connect(webView, &QWebEngineView::loadFinished, [webView, s_url](bool success) {
            if (!success) {
                webView->setHtml("<html><body style='background-color:white;'></body></html>");
                // ����ʧ�ܣ��ӳ�1����Զ�ˢ��
                QTimer::singleShot(1000, [webView, s_url]() {
                    webView->load(QUrl(s_url));
                    });
            }
            });

        int tabIndex = tabWidget->addTab(webView, button->text());
        tabWidget->setCurrentIndex(tabIndex);
        webViewMap[webView] = url2;//������ҳ�Ͷ˿ڵĶ�Ӧ��ϵ����Ϊ��������˾��޷���webView��ö˿ڣ�������ú�����ı����ϲ���
        buttonToWebViewDict[button] = { webView, 1 };//��ť�������˰�ť��tabWidget�ͱ�־λ�������ظ�������ҳ��
    }
}

void QtWidgetsApplication2::sendMessage(const QString& ip, int port, const QString& message)
{
    QTcpSocket* socket = new QTcpSocket();

    // ���ӷ�����
    socket->connectToHost(ip, port);

    // �����������������ʧ�ܵ����
    if (socket->waitForConnected(1000)) {
        // ������Ϣ
        socket->write(message.toUtf8());
        socket->flush();
        qDebug() << "��Ϣ�ѷ���:" << message;
    }

    // ������ɺ�ر�����
    socket->disconnectFromHost();
    socket->deleteLater();
}
void QtWidgetsApplication2::updateMenuMessage(const QString& message)
{
    // ������Ϣ��������Ϣ��ʽΪ "IP:��Ϣ����"
    // ����: "192.168.1.100:����һ��������Ϣ"

    int colonPos = message.indexOf(':');
    if (colonPos == -1) {
        return; // ��Ч��Ϣ��ʽ
    }

    QString ip = message.left(colonPos);

    QString msgContent = message.mid(colonPos + 1);
    if (ipMessageMap.contains(ip) == false) {// IP��һ�γ���
        QStringList parts = msgContent.split(",");
        // ����IP-��Ϣӳ��
        ipMessageMap[ip] = message;
        // ������в˵���
            // ��ӵڶ�����ҳ
        QWidget* page = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(page);
        QTabWidget* tabWidget = ui->tabWidget;
        ui->toolBox->addItem(page, parts[0]);
        for (int i = 1; i < parts.size(); ++i) { // ��i=1��ʼ

            QPushButton* button = new QPushButton(parts[i], page);
            QString ip_url = "http://" + ip+":"+QString::number(4999+i);
            connect(button, &QPushButton::clicked, this, [this, tabWidget, ip_url, page, button]() {
                handleButtonClick(tabWidget, ip_url, page, button);  // ָ��ť����
                });
            layout->addWidget(button);
        }
    }
    ui->menu->clear();

    // Ϊÿ��IP��Ӳ˵���
    for (auto it = ipMessageMap.begin(); it != ipMessageMap.end(); ++it) {
        QString menuText = QString("%1: %2").arg(it.key()).arg(it.value());
        ui->menu->addAction(menuText);
    }
}

void QtWidgetsApplication2::addWebTab(QTabWidget* tabWidget, const QString& title, const QString& url) {
    QWebEngineView* webView = new QWebEngineView(tabWidget);
    webView->load(QUrl(url));
    int tabIndex = tabWidget->addTab(webView, title);
    tabWidget->setCurrentIndex(tabIndex);
}

QtWidgetsApplication2::~QtWidgetsApplication2() {
    serverThread->quit();
    serverThread->wait();
    delete serverThread;
    delete ui;
}
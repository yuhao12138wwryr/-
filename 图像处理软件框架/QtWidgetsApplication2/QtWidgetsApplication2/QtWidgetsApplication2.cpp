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
#include <QTabBar>  // 必须添加这行
#include <QMouseEvent>  // 必须添加这行
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
    if (!server->listen(QHostAddress::Any, 12345)) {//本机服务器是12345
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

    // 删除默认分页
    ui->toolBox->removeItem(0);
    ui->toolBox->removeItem(0);

    // 初始化 tabWidget
    QTabWidget* tabWidget = ui->tabWidget;
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    QWidget* widget = tabWidget->widget(1); // 获取第一个选项卡的内容
    tabWidget->removeTab(1);               // 移除选项卡（会自动删除widget）
    widget = tabWidget->widget(0); // 获取第2个选项卡的内容
    tabWidget->removeTab(0); 
    QWebEngineView* webView = new QWebEngineView(tabWidget);


    QString htmlPath = QCoreApplication::applicationDirPath() + "/a.html";
    webView->load(QUrl::fromLocalFile(htmlPath));
    int tabIndex = tabWidget->addTab(webView, QString::fromLocal8Bit("算法参数导航"));
    tabWidget->setCurrentIndex(tabIndex);

     // 记录上一次的标签页索引，我想切换标签时隐藏之前的页面而不是删除，但是优化不显著，或者说根本没执行。。
    connect(tabWidget, &QTabWidget::currentChanged, [=](int index) mutable {
        // 隐藏上一个标签页的内容
        if (lastIndex >= 0 && lastIndex < tabWidget->count()) {
            if (QWidget* lastPage = tabWidget->widget(lastIndex)) {
                lastPage->hide();
            }
        }
        // 显示当前标签页的内容
        if (index >= 0 && index < tabWidget->count()) {
            if (QWidget* currentPage = tabWidget->widget(index)) {
                currentPage->show();
            }
        }

        lastIndex = index; // 更新记录
        });
    // 连接关闭按钮信号
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [tabWidget, this](int index) {
        QWidget* widget = tabWidget->widget(index);  // 获取标签页内容
        if (auto webView = qobject_cast<QWebEngineView*>(widget)) {
            // 3. 获取当前URL
            QUrl currentUrl=webViewMap[webView];
            int port = currentUrl.port();
            sendMessage(currentUrl.host(), 4999, QString::number(port-5000));
        }
        else {
            qWarning() << "该标签页不是网页视图";
        }
        // 遍历字典，修改符合条件的条目（按钮函数绑定了按钮和tabWidget和标志位，清除tabWidget和标志位才能开新页面）
        for (auto& [btn, pair] : this->buttonToWebViewDict) {
            if (pair.first == widget) {  
                btn->setStyleSheet("color: black;");
                pair.second = 0;    // 将 second 值设为 0
            }
        }
        tabWidget->removeTab(index);  // 移除标签页（此时 widget 已销毁）
        });
    tabWidget->tabBar()->installEventFilter(this);  // 新增
    // 添加第一个分页
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
    QToolBox::tab:selected {  /* 选中时的样式 */
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                  stop:0 #3a3a3a, stop:1 #6a6a6a);
    }
)");
    int index = ui->toolBox->addItem(page1, QString::fromLocal8Bit("启动导航栏"));
    ui->toolBox->setItemEnabled(index, false);  // 禁用该项
    // 启动服务器线程
    serverThread = new ServerThread(this, ui->menu);
    connect(serverThread, &ServerThread::newMessageReceived, this, &QtWidgetsApplication2::updateMenuMessage);
    serverThread->start();
}
// 新增：事件过滤器实现
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

// 新增：标签分离方法
void QtWidgetsApplication2::detachTab(int index)
{
    QTabWidget* tabWidget = ui->tabWidget;
    QWidget* widget = tabWidget->widget(index);
    QString title = tabWidget->tabText(index);

    // 从 tabWidget 中移除但不删除 widget
    tabWidget->removeTab(index);

    // 创建浮动窗口
    QDockWidget* dock = new QDockWidget(title, this);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::NoDockWidgetArea);
    dock->setWidget(widget); // 直接使用原 widget
    dock->setAttribute(Qt::WA_DeleteOnClose);

    // 浮动窗口关闭时重新添加回 tabWidget
    connect(dock, &QDockWidget::destroyed, this, [this, widget, title]() {
        ui->tabWidget->addTab(widget, title);
        });

    dock->setFloating(true);
    dock->show();
}

void QtWidgetsApplication2::handleButtonClick(QTabWidget* tabWidget, QString s_url, QWidget* page, QPushButton* button) {
    if (button && page && buttonToWebViewDict[button].second != 1) {
        // 直接操作传入的按钮

        button->setStyleSheet("color: red;");
        QWebEngineView* webView = new QWebEngineView(tabWidget);

        binder.addBinding(button, webView, s_url, 1);//创建按钮与页面与URL的数据结构
        webView->load(QUrl(s_url));
        QUrl url2(s_url);
        int port = url2.port();       // 5000 (如果未指定端口，返回 -1)
        sendMessage(url2.host(), 4999, QString::number(port - 5000+1972008941));//告知调度器启动指定服务器，4999是调度器的端口。这里其实可以直接读url，我懒得搞，交给后人了.port加上我QQ号是因为我想看看以后是谁来维护这个，加我，我告诉你。
        // 连接加载完成信号
        QObject::connect(webView, &QWebEngineView::loadFinished, [webView, s_url](bool success) {
            if (!success) {
                webView->setHtml("<html><body style='background-color:white;'></body></html>");
                // 加载失败，延迟1秒后自动刷新
                QTimer::singleShot(1000, [webView, s_url]() {
                    webView->load(QUrl(s_url));
                    });
            }
            });

        int tabIndex = tabWidget->addTab(webView, button->text());
        tabWidget->setCurrentIndex(tabIndex);
        webViewMap[webView] = url2;//储存网页和端口的对应关系，因为如果网卡了就无法从webView获得端口，将来最好和下面的变量合并了
        buttonToWebViewDict[button] = { webView, 1 };//按钮函数绑定了按钮和tabWidget和标志位，避免重复创建网页）
    }
}

void QtWidgetsApplication2::sendMessage(const QString& ip, int port, const QString& message)
{
    QTcpSocket* socket = new QTcpSocket();

    // 连接服务器
    socket->connectToHost(ip, port);

    // 简单起见，不处理连接失败的情况
    if (socket->waitForConnected(1000)) {
        // 发送消息
        socket->write(message.toUtf8());
        socket->flush();
        qDebug() << "消息已发送:" << message;
    }

    // 发送完成后关闭连接
    socket->disconnectFromHost();
    socket->deleteLater();
}
void QtWidgetsApplication2::updateMenuMessage(const QString& message)
{
    // 解析消息，假设消息格式为 "IP:消息内容"
    // 例如: "192.168.1.100:这是一条测试消息"

    int colonPos = message.indexOf(':');
    if (colonPos == -1) {
        return; // 无效消息格式
    }

    QString ip = message.left(colonPos);

    QString msgContent = message.mid(colonPos + 1);
    if (ipMessageMap.contains(ip) == false) {// IP第一次出现
        QStringList parts = msgContent.split(",");
        // 更新IP-消息映射
        ipMessageMap[ip] = message;
        // 清除现有菜单项
            // 添加第二个分页
        QWidget* page = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(page);
        QTabWidget* tabWidget = ui->tabWidget;
        ui->toolBox->addItem(page, parts[0]);
        for (int i = 1; i < parts.size(); ++i) { // 从i=1开始

            QPushButton* button = new QPushButton(parts[i], page);
            QString ip_url = "http://" + ip+":"+QString::number(4999+i);
            connect(button, &QPushButton::clicked, this, [this, tabWidget, ip_url, page, button]() {
                handleButtonClick(tabWidget, ip_url, page, button);  // 指向按钮函数
                });
            layout->addWidget(button);
        }
    }
    ui->menu->clear();

    // 为每个IP添加菜单项
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
#pragma once
#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMenu>
#include <QDockWidget>  // ����

#include "ui_QtWidgetsApplication2.h"
#include "QtWidgetsApplication2.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QWebEngineView>
#include <map>
#include <utility> // for std::pair
#include "QuadrupleBinding.h"

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QObject* parent = nullptr, QMenu* menu = nullptr);
    void run() override;

signals:
    void newMessageReceived(const QString& message);

private:
    QTcpServer* server;
    QMenu* menu;
};

class QtWidgetsApplication2 : public QMainWindow {
    Q_OBJECT
public:
    void addWebTab(QTabWidget* tabWidget, const QString& title, const QString& url);
    QtWidgetsApplication2(QWidget* parent = nullptr);
    ~QtWidgetsApplication2();
    QuadrupleBinding binder;

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;  // ����

private slots:
    void handleButtonClick(QTabWidget* tabWidget, QString, QWidget* page, QPushButton* button);
    void updateMenuMessage(const QString& message);

private:
    void sendMessage(const QString& ip, int port, const QString& message);
    void detachTab(int index);  // ��������ǩ���뷽��
    Ui::QtWidgetsApplication2Class* ui;
    std::map<QPushButton*, std::pair<QWebEngineView*, int>> buttonToWebViewDict;
    ServerThread* serverThread;
    QMap<QString, QString> ipMessageMap; // �洢IP�Ͷ�Ӧ��Ϣ
    QMap<QWebEngineView*, QUrl> webViewMap;  // ��ҳ��IP�˿�
    int lastIndex = -1;
};
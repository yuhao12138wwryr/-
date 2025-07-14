/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication2.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION2_H
#define UI_QTWIDGETSAPPLICATION2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication2Class
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *page_3;
    QWidget *page_4;
    QTabWidget *tabWidget;
    QWidget *tab_7;
    QLabel *label;
    QWidget *widget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;
    QMenu *menu_7;
    QMenu *menu_8;
    QMenu *menu_9;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplication2Class)
    {
        if (QtWidgetsApplication2Class->objectName().isEmpty())
            QtWidgetsApplication2Class->setObjectName("QtWidgetsApplication2Class");
        QtWidgetsApplication2Class->resize(600, 499);
        action = new QAction(QtWidgetsApplication2Class);
        action->setObjectName("action");
        action_2 = new QAction(QtWidgetsApplication2Class);
        action_2->setObjectName("action_2");
        action_3 = new QAction(QtWidgetsApplication2Class);
        action_3->setObjectName("action_3");
        action_4 = new QAction(QtWidgetsApplication2Class);
        action_4->setObjectName("action_4");
        action_5 = new QAction(QtWidgetsApplication2Class);
        action_5->setObjectName("action_5");
        action_6 = new QAction(QtWidgetsApplication2Class);
        action_6->setObjectName("action_6");
        action_7 = new QAction(QtWidgetsApplication2Class);
        action_7->setObjectName("action_7");
        centralWidget = new QWidget(QtWidgetsApplication2Class);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName("toolBox");
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 236, 356));
        toolBox->addItem(page_3, QString::fromUtf8("Page 1"));
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        page_4->setGeometry(QRect(0, 0, 236, 356));
        toolBox->addItem(page_4, QString::fromUtf8("Page 2"));
        splitter->addWidget(toolBox);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        label = new QLabel(tab_7);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 261, 91));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        tabWidget->addTab(tab_7, QString());
        widget = new QWidget();
        widget->setObjectName("widget");
        tabWidget->addTab(widget, QString());
        splitter->addWidget(tabWidget);

        horizontalLayout->addWidget(splitter);

        QtWidgetsApplication2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtWidgetsApplication2Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 33));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName("menu_3");
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName("menu_4");
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName("menu_5");
        menu_6 = new QMenu(menuBar);
        menu_6->setObjectName("menu_6");
        menu_7 = new QMenu(menuBar);
        menu_7->setObjectName("menu_7");
        menu_8 = new QMenu(menuBar);
        menu_8->setObjectName("menu_8");
        menu_9 = new QMenu(menuBar);
        menu_9->setObjectName("menu_9");
        QtWidgetsApplication2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplication2Class);
        mainToolBar->setObjectName("mainToolBar");
        QtWidgetsApplication2Class->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtWidgetsApplication2Class);
        statusBar->setObjectName("statusBar");
        QtWidgetsApplication2Class->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menu_6->menuAction());
        menuBar->addAction(menu_7->menuAction());
        menuBar->addAction(menu_8->menuAction());
        menuBar->addAction(menu_9->menuAction());
        menu_2->addAction(action_7);
        menu_3->addAction(action);
        menu_4->addAction(action_2);
        menu_5->addAction(action_3);
        menu_6->addAction(action_4);
        menu_7->addAction(action_5);
        menu_9->addAction(action_6);

        retranslateUi(QtWidgetsApplication2Class);

        toolBox->setCurrentIndex(1);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QtWidgetsApplication2Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplication2Class)
    {
        QtWidgetsApplication2Class->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "QtWidgetsApplication2", nullptr));
        action->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        action_2->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        action_3->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        action_4->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        action_5->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        action_6->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        action_7->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QCoreApplication::translate("QtWidgetsApplication2Class", "Page 1", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QCoreApplication::translate("QtWidgetsApplication2Class", "Page 2", nullptr));
        label->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\257\267\345\234\250\345\267\246\344\276\247\351\200\211\346\213\251\344\270\200\344\270\252\345\226\234\346\254\242\347\232\204\347\256\227\346\263\225\343\200\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("QtWidgetsApplication2Class", "\346\254\242\350\277\216", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget), QString());
        menu->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\277\236\346\216\245\346\203\205\345\206\265", nullptr));
        menu_2->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\345\257\274\350\210\252\351\241\265", nullptr));
        menu_3->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\347\274\226\350\276\221", nullptr));
        menu_4->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\347\252\227\344\275\223", nullptr));
        menu_5->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\247\206\345\233\276", nullptr));
        menu_6->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\350\256\276\347\275\256", nullptr));
        menu_7->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\345\270\256\345\212\251", nullptr));
        menu_8->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\346\226\207\344\273\266", nullptr));
        menu_9->setTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "\346\220\234\347\264\242\357\274\232    ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication2Class: public Ui_QtWidgetsApplication2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION2_H

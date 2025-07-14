/********************************************************************************
** Form generated from reading UI file 'QtWidgetsClass.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSCLASS_H
#define UI_QTWIDGETSCLASS_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsClassClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWebEngineView *webEngineView;

    void setupUi(QWidget *QtWidgetsClassClass)
    {
        if (QtWidgetsClassClass->objectName().isEmpty())
            QtWidgetsClassClass->setObjectName("QtWidgetsClassClass");
        QtWidgetsClassClass->resize(643, 400);
        horizontalLayout = new QHBoxLayout(QtWidgetsClassClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        webEngineView = new QWebEngineView(QtWidgetsClassClass);
        webEngineView->setObjectName("webEngineView");
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        horizontalLayout->addWidget(webEngineView);


        retranslateUi(QtWidgetsClassClass);

        QMetaObject::connectSlotsByName(QtWidgetsClassClass);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsClassClass)
    {
        QtWidgetsClassClass->setWindowTitle(QCoreApplication::translate("QtWidgetsClassClass", "QtWidgetsClass", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsClassClass: public Ui_QtWidgetsClassClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSCLASS_H

#pragma once
#ifndef QUADRUPLEBINDING_H
#define QUADRUPLEBINDING_H

#include <QHash>
#include <QMap>
#include <QPushButton>
#include <QWebEngineView>
#include <optional>

class QuadrupleBinding {
public:
    // �󶨹�ϵ���ݽṹ
    struct BindingData {
        QWebEngineView* webView;
        QString url;
        int index;

        BindingData(QWebEngineView* v = nullptr,
            const QString& u = QString(),
            int i = 0)
            : webView(v), url(u), index(i) {
        }
    };

    // �����Ԫ���
    void addBinding(QPushButton* button,
        QWebEngineView* webView,
        const QString& url,
        int index);

    // ͨ�ü����ӿ�
    std::optional<BindingData> getBinding(QPushButton* button) const;
    std::optional<BindingData> getBinding(QWebEngineView* webView) const;
    std::optional<BindingData> getBinding(const QString& url) const;
    std::optional<BindingData> getBinding(int index) const;

    // ���°󶨹�ϵ
    bool updateBinding(QPushButton* button, const BindingData& newData);
    bool updateBinding(QWebEngineView* webView, const BindingData& newData);
    bool updateBinding(const QString& url, const BindingData& newData);
    bool updateBinding(int index, const BindingData& newData);

    // �Ƴ���
    bool removeBinding(QPushButton* button);
    bool removeBinding(QWebEngineView* webView);
    bool removeBinding(const QString& url);
    bool removeBinding(int index);

    // ��������
    void clearAll();
    int count() const;

private:
    // ��ȡ�����İ�ťָ�루�ڲ�ʹ�ã�
    QPushButton* getButton(QPushButton* button) const;
    QPushButton* getButton(QWebEngineView* webView) const;
    QPushButton* getButton(const QString& url) const;
    QPushButton* getButton(int index) const;

    // ���洢������
    QHash<QPushButton*, BindingData> m_buttonMap;
    QHash<QWebEngineView*, QPushButton*> m_webViewMap;
    QMap<QString, QPushButton*> m_urlMap;
    QHash<int, QPushButton*> m_indexMap;
};

#endif // QUADRUPLEBINDING_H
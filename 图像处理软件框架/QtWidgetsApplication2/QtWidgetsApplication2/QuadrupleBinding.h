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
    // 绑定关系数据结构
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

    // 添加四元组绑定
    void addBinding(QPushButton* button,
        QWebEngineView* webView,
        const QString& url,
        int index);

    // 通用检索接口
    std::optional<BindingData> getBinding(QPushButton* button) const;
    std::optional<BindingData> getBinding(QWebEngineView* webView) const;
    std::optional<BindingData> getBinding(const QString& url) const;
    std::optional<BindingData> getBinding(int index) const;

    // 更新绑定关系
    bool updateBinding(QPushButton* button, const BindingData& newData);
    bool updateBinding(QWebEngineView* webView, const BindingData& newData);
    bool updateBinding(const QString& url, const BindingData& newData);
    bool updateBinding(int index, const BindingData& newData);

    // 移除绑定
    bool removeBinding(QPushButton* button);
    bool removeBinding(QWebEngineView* webView);
    bool removeBinding(const QString& url);
    bool removeBinding(int index);

    // 批量操作
    void clearAll();
    int count() const;

private:
    // 获取关联的按钮指针（内部使用）
    QPushButton* getButton(QPushButton* button) const;
    QPushButton* getButton(QWebEngineView* webView) const;
    QPushButton* getButton(const QString& url) const;
    QPushButton* getButton(int index) const;

    // 主存储和索引
    QHash<QPushButton*, BindingData> m_buttonMap;
    QHash<QWebEngineView*, QPushButton*> m_webViewMap;
    QMap<QString, QPushButton*> m_urlMap;
    QHash<int, QPushButton*> m_indexMap;
};

#endif // QUADRUPLEBINDING_H
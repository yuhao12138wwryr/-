#include "QuadrupleBinding.h"

void QuadrupleBinding::addBinding(QPushButton* button,
    QWebEngineView* webView,
    const QString& url,
    int index) {
    if (!button || !webView) return;

    // ���Ƴ��Ѵ��ڵĹ�������ֹ�ظ���
    removeBinding(button);
    removeBinding(webView);
    removeBinding(url);
    removeBinding(index);

    // ���������
    m_buttonMap[button] = { webView, url, index };

    // ������������
    m_webViewMap[webView] = button;
    m_urlMap[url] = button;
    m_indexMap[index] = button;
}

// ͨ�ü���ʵ��
std::optional<QuadrupleBinding::BindingData>
QuadrupleBinding::getBinding(QPushButton* button) const {
    auto it = m_buttonMap.find(button);
    return it != m_buttonMap.end() ? std::optional(it.value()) : std::nullopt;
}

std::optional<QuadrupleBinding::BindingData>
QuadrupleBinding::getBinding(QWebEngineView* webView) const {
    return getBinding(getButton(webView));
}

std::optional<QuadrupleBinding::BindingData>
QuadrupleBinding::getBinding(const QString& url) const {
    return getBinding(getButton(url));
}

std::optional<QuadrupleBinding::BindingData>
QuadrupleBinding::getBinding(int index) const {
    return getBinding(getButton(index));
}

// ���²���ʵ��
bool QuadrupleBinding::updateBinding(QPushButton* button, const BindingData& newData) {
    if (!m_buttonMap.contains(button)) return false;

    // �Ƴ�������
    const auto& oldData = m_buttonMap[button];
    m_webViewMap.remove(oldData.webView);
    m_urlMap.remove(oldData.url);
    m_indexMap.remove(oldData.index);

    // ��������
    m_buttonMap[button] = newData;
    m_webViewMap[newData.webView] = button;
    m_urlMap[newData.url] = button;
    m_indexMap[newData.index] = button;

    return true;
}

bool QuadrupleBinding::updateBinding(QWebEngineView* webView, const BindingData& newData) {
    return updateBinding(getButton(webView), newData);
}

bool QuadrupleBinding::updateBinding(const QString& url, const BindingData& newData) {
    return updateBinding(getButton(url), newData);
}

bool QuadrupleBinding::updateBinding(int index, const BindingData& newData) {
    return updateBinding(getButton(index), newData);
}

// �Ƴ�����ʵ��
bool QuadrupleBinding::removeBinding(QPushButton* button) {
    if (!m_buttonMap.contains(button)) return false;

    const auto& data = m_buttonMap[button];
    m_webViewMap.remove(data.webView);
    m_urlMap.remove(data.url);
    m_indexMap.remove(data.index);
    m_buttonMap.remove(button);

    return true;
}

bool QuadrupleBinding::removeBinding(QWebEngineView* webView) {
    return removeBinding(getButton(webView));
}

bool QuadrupleBinding::removeBinding(const QString& url) {
    return removeBinding(getButton(url));
}

bool QuadrupleBinding::removeBinding(int index) {
    return removeBinding(getButton(index));
}

// �ڲ���������
QPushButton* QuadrupleBinding::getButton(QPushButton* button) const {
    return m_buttonMap.contains(button) ? button : nullptr;
}

QPushButton* QuadrupleBinding::getButton(QWebEngineView* webView) const {
    auto it = m_webViewMap.find(webView);
    return it != m_webViewMap.end() ? it.value() : nullptr;
}

QPushButton* QuadrupleBinding::getButton(const QString& url) const {
    auto it = m_urlMap.find(url);
    return it != m_urlMap.end() ? it.value() : nullptr;
}

QPushButton* QuadrupleBinding::getButton(int index) const {
    auto it = m_indexMap.find(index);
    return it != m_indexMap.end() ? it.value() : nullptr;
}

// ��������
void QuadrupleBinding::clearAll() {
    m_buttonMap.clear();
    m_webViewMap.clear();
    m_urlMap.clear();
    m_indexMap.clear();
}

int QuadrupleBinding::count() const {
    return m_buttonMap.size();
}
#ifndef VIEWFORMCUST_H
#define VIEWFORMCUST_H

#include <QWidget>
#include <memory>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QColor>

class ViewFormCust : public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit ViewFormCust(QQuickItem *parent = nullptr);
    ~ViewFormCust();
    static ViewFormCust *m_instance;
    static ViewFormCust *getInstance();
    static QObject* getInstance(QQmlEngine *engine, QJSEngine *scriptEngine){Q_UNUSED(engine);Q_UNUSED(scriptEngine);return getInstance();}

private:
    void paintEvent(QPaintEvent*);
    virtual void paint(QPainter *painter) override;
    virtual void wheelEvent(QWheelEvent*) override;
    virtual void mouseDoubleClickEvent(QMouseEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;

    bool _mouseDragging = false;
};

#endif // VIEWFORM_H

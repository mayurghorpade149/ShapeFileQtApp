#ifndef VIEWFORM_H
#define VIEWFORM_H

#include <QWidget>
#include <memory>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQuickPaintedItem>

class ViewForm : public QWidget
{
    Q_OBJECT   

public:
    explicit ViewForm(QWidget* parent = nullptr);
    ~ViewForm();
    static ViewForm *m_instance;
    static ViewForm *getInstance();
    static QObject* getInstance(QQmlEngine *engine, QJSEngine *scriptEngine){Q_UNUSED(engine);Q_UNUSED(scriptEngine);return getInstance();}

private:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void wheelEvent(QWheelEvent*) override;
    virtual void mouseDoubleClickEvent(QMouseEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;

    bool _mouseDragging = false;
};

#endif // VIEWFORM_H

#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
#include "map.h"
#include <QQmlProperty>
#include <QQuickItem>


class MapWindow : public QWidget, public cl::Map::MapObserver
{
    Q_OBJECT


public:    
    explicit MapWindow(QWidget* parent = nullptr);
    ~MapWindow();

    static MapWindow *m_instance;
    static MapWindow *getInstance();
    static QObject* getInstance(QQmlEngine *engine, QJSEngine *scriptEngine){Q_UNUSED(engine);Q_UNUSED(scriptEngine);return getInstance();}


public:
    virtual void paintEvent(QPaintEvent*) override;

    virtual void updateDisplay() override;

    void setMap(std::shared_ptr<cl::Map::Map> const& map);

private:    

    std::shared_ptr<cl::Map::Map> _map;
};

#endif // MAPWINDOW_H

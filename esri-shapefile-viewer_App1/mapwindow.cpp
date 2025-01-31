#include "mapwindow.h"
#include <QPainter>

MapWindow* MapWindow::m_instance;

MapWindow* MapWindow::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new MapWindow(nullptr);
    }
    return m_instance;
}

MapWindow::MapWindow(QWidget *parent) :
    QWidget(parent)
{        
    setMinimumHeight(512);
    setMinimumWidth(512);
    setMaximumHeight(512);
    setMaximumWidth(512);
}

MapWindow::~MapWindow() {}

void MapWindow::setMap(std::shared_ptr<cl::Map::Map> const& map)
{
    _map = map;

    _map->setObserver(*this);
    _map->setPaintingRect(rect());
    _map->zoomToAll();
}

void MapWindow::paintEvent(QPaintEvent*)
{
    if (_map == nullptr)
        return;

    _map->setPaintingRect(rect());

    QPainter painter(this);
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    _map->draw(painter);

    painter.end();
}

void MapWindow::updateDisplay()
{
    update();
}

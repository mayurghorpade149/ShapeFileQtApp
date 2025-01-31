#include "viewformcustome.h"
#include <QPainter>
#include <QWheelEvent>
#include "shapemanager.h"
ViewFormCust* ViewFormCust::m_instance;

ViewFormCust* ViewFormCust::getInstance()
{
    if (ViewFormCust::m_instance == nullptr)
    {
        ViewFormCust::m_instance = new ViewFormCust(nullptr);
    }
    return ViewFormCust::m_instance;
}
ViewFormCust::ViewFormCust(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    ViewFormCust::m_instance = this;
//    setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
}

ViewFormCust::~ViewFormCust() {}

void ViewFormCust::paintEvent(QPaintEvent*)
{
//    cl::DataManagement::ShapeView::instance().setPaintingRect(boundingRect().toRect());

//    QPainter painter(this);
//    painter.begin(this);
//    painter.setRenderHint(QPainter::Antialiasing);

//    cl::DataManagement::ShapeView::instance().draw(painter);

//    painter.end();
}

void ViewFormCust::paint(QPainter *painter)
{
    cl::DataManagement::ShapeView::instance().setPaintingRect(boundingRect().toRect());

    painter->setRenderHint(QPainter::Antialiasing);

    cl::DataManagement::ShapeView::instance().draw(*painter);
}

void ViewFormCust::wheelEvent(QWheelEvent* event)
{
    cl::Pair<int> mousePos(event->pos());

    // Zoom in once everytime the wheel turns 90 degrees.
    float scaleFactor = 1 + (float(event->delta()) / 8 / 90);

    cl::DataManagement::ShapeView::instance().zoomAtCursor(mousePos, scaleFactor);
}

void ViewFormCust::mouseDoubleClickEvent(QMouseEvent*)
{
    cl::DataManagement::ShapeView::instance().zoomToAll();
}

void ViewFormCust::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "Mouse press event";
    _mouseDragging = true;
    setCursor(QCursor(Qt::CursorShape::ClosedHandCursor));
    cl::DataManagement::ShapeView::instance().translationStart(event->pos());
}

void ViewFormCust::mouseReleaseEvent(QMouseEvent*)
{
    qDebug() << "Mouse release event";
    _mouseDragging = false;
    setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
}

void ViewFormCust::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "Mouse move event";
    if (_mouseDragging)
    {
        qDebug() << "Mouse drag event";
        cl::DataManagement::ShapeView::instance().translationProcessing(event->pos());
    }
}

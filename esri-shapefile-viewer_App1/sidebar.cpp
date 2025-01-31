#include "sidebar.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include "shapemanager.h"
#include "shapedata.h"

Sidebar* Sidebar::m_instance;

Sidebar* Sidebar::getInstance()
{
    if (Sidebar::m_instance == nullptr)
    {
        Sidebar::m_instance = new Sidebar(nullptr);
    }
    return Sidebar::m_instance;
}

Sidebar::Sidebar(QWidget* parent)
    : QDockWidget(parent)
{
    setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

    // Connect the item double-click signal.
//    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(doubleClickItem(QListWidgetItem*)));
}

Sidebar::~Sidebar() {}

QStringList Sidebar::listSelection()
{
    return layerList;
}

QString Sidebar::listFirst()
{
    return layerList.first();
}

QString Sidebar::listLast()
{
    return layerList.last();
}

void Sidebar::updateList()
{
    layerList.clear();

    auto rawNameList = cl::DataManagement::ShapeView::instance().rawNameList();

    int i = 0;
    for (auto item : rawNameList)
    {
        QString name = QString::fromStdString(*item);
        layerList.insert(i++, name);
    }
}

// Zoom to specified layer when double clicking it.
void Sidebar::doubleClickItem(QListWidgetItem* clickedItem)
{
    using namespace cl::DataManagement;

    QString layerName = clickedItem->text();
    auto layerItr = ShapeView::instance().findByName(layerName.toStdString());
    if (ShapeView::instance().layerNotFound(layerItr))
        return;

    ShapeView::instance().zoomToLayer(layerItr);
}

#include "mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QLabel>
#include <QListWidget>
#include "mainwindowglobalcontext.h"

MainWindow* MainWindow::m_instance;

MainWindow* MainWindow::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new MainWindow(nullptr);
    }
    return m_instance;
}


MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{

//    setWindowTitle("Shape Viewer");

    qsrand(QTime::currentTime().second());

    // Initialize the view widget of shapes.
    QObject *rootObj = nullptr;

    rootObj = MainWindowGlobalContext::getInstance()->getRootObject();
    QQuickWindow *wndw = qobject_cast<QQuickWindow*>(rootObj);
    QObject *primCamera = rootObj->findChild<QObject*>("viewForm");
    if (primCamera)
    {
        _viewFormCust = qobject_cast<ViewFormCust *>(primCamera);
    }
//    _viewForm.reset(new ViewForm(this));
//    setCentralWidget(_viewForm.get());


    // Initialize the status label.
//    _msgLabel.reset(new QLabel());
//    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
//    statusBar()->addWidget(_msgLabel.get());

    // Bind the singleton dataset with this form as its observer.
    cl::DataManagement::ShapeView::instance().setObserver(*this);

    // Connect the open file signal.
//    connect(ui->actionOpen_Dataset, SIGNAL(triggered(bool)), this, SLOT(openDataset()));
//    connect(ui->actionClose_All, SIGNAL(triggered(bool)), this, SLOT(closeAll()));
//    connect(ui->actionRemove_Layer, SIGNAL(triggered(bool)), this, SLOT(removeLayer()));
//    connect(ui->actionLayer_Up, SIGNAL(triggered(bool)), this, SLOT(layerUp()));
//    connect(ui->actionLayer_Down, SIGNAL(triggered(bool)), this, SLOT(layerDown()));
//    connect(ui->actionFull_Elements, SIGNAL(triggered(bool)), this, SLOT(createMapFullElements()));
//    connect(ui->actionNo_Grid_Line, SIGNAL(triggered(bool)), this, SLOT(createMapNoGridLine()));
    // If the slot function name is wrong,
    // without any error prompts the connection will not work.

    // Show the main window.
//    show();
}

MainWindow::~MainWindow() {}

void MainWindow::updateDisplay()
{
    if(_viewFormCust == nullptr)
    {
        QObject *rootObj = nullptr;

        rootObj = MainWindowGlobalContext::getInstance()->getRootObject();
//        QQuickWindow *wndw = qobject_cast<QQuickWindow*>(rootObj);
        QObject *primCamera = rootObj->findChild<QObject*>("viewForm");
        if (primCamera)
        {
            _viewFormCust = qobject_cast<ViewFormCust *>(primCamera);
        }
    }
    _viewFormCust->update();
//    update();
}

void MainWindow::setLabel(QString const& msg)
{
    if (_msgLabel != nullptr)
        _msgLabel->setText(msg);
}

void MainWindow::openDataset(QStringList fileNames)
{
    using namespace cl::DataManagement;

    bool notInitialized = ShapeView::instance().isEmpty();

//    QStringList fileNames = {"C:/Users/Owner/Downloads/shapefile-viewer-qt-master/shapefile-viewer-qt-master/data/TM_WORLD_BORDERS-0.3.shp"};//dialog.selectedFiles();
    for (auto path : fileNames)
        ShapeView::instance().addLayer(path.toStdString());

    if (notInitialized)
        ShapeView::instance().zoomToAll();
    emit updateLayerList();
}

void MainWindow::openDataset(QString fileNameStr)
{
    using namespace cl::DataManagement;

    bool notInitialized = ShapeView::instance().isEmpty();


    fileNameStr.remove("file://");

    QStringList fileNames = fileNameStr.split(",");


    for (auto path : fileNames)
    {
        ShapeView::instance().addLayer(path.toStdString());
        QFileInfo fileInfo(path);
        QString filename(fileInfo.fileName());
        layerList.append(filename.remove(".shp"));
    }

    if (notInitialized)
        ShapeView::instance().zoomToAll();

    emit updateLayerList();
}

void MainWindow::closeAll()
{
    cl::DataManagement::ShapeView::instance().clearAllLayers();
}

void MainWindow::removeLayer(int LayerIndex)
{
    using namespace cl::DataManagement;

    QStringList selection = listSelection();
    if (selection.empty() || selection.count()<LayerIndex)
        return;

    QString selectedItem = selection.at(LayerIndex);//selection.front();
    auto layerItr = ShapeView::instance().findByName(selectedItem.toStdString());
    if (ShapeView::instance().layerNotFound(layerItr))
        return;

    ShapeView::instance().removeLayer(layerItr);
    layerList.removeAt(LayerIndex);
    emit updateLayerList();
}

void MainWindow::layerUp(int LayerIndex)
{
    using namespace cl::DataManagement;

    QStringList selection = listSelection();
    if (selection.empty())
        return;
    QString selectedItem = selection.at(LayerIndex);//selection.front();
    if (selectedItem == listFirst() || selection.count()<LayerIndex)
        return;

    auto layerItr = ShapeView::instance().findByName(selectedItem.toStdString());
    if (ShapeView::instance().layerNotFound(layerItr))
        return;

    ShapeView::instance().rearrangeLayer(layerItr, ++(++layerItr));
    emit updateLayerList();
}

void MainWindow::layerDown(int LayerIndex)
{
    using namespace cl::DataManagement;

    QStringList selection = listSelection();
    if (selection.empty() || selection.count()<LayerIndex)
        return;
    QString selectedItem = selection.at(LayerIndex);//selection.front();
    if (selectedItem == listLast())
        return;

    auto layerItr = ShapeView::instance().findByName(selectedItem.toStdString());
    if (ShapeView::instance().layerNotFound(layerItr))
        return;

    ShapeView::instance().rearrangeLayer(layerItr, --layerItr);
    emit updateLayerList();
}

void MainWindow::createMap(cl::Map::MapStyle mapStyle)
{
    using namespace cl::Map;
    using namespace cl::DataManagement;

    std::unique_ptr<MapDirector> mapDirector;

    switch (mapStyle)
    {
    case MapStyle::FullElements:
        mapDirector.reset(new MapDirector(new MapBuilder::FullElements()));
        break;
    case MapStyle::NoGridLine:
        mapDirector.reset(new MapDirector(new MapBuilder::NoGridLine()));
        break;
    default:
        return;
    }

    std::shared_ptr<Map> map = mapDirector->constructMap(ShapeView::instance().shapeDoc());

    _mapWindow->setMap(map);
}

void MainWindow::createMapFullElements()
{
    createMap(cl::Map::MapStyle::FullElements);
}

void MainWindow::createMapNoGridLine()
{
    createMap(cl::Map::MapStyle::NoGridLine);
}

QStringList MainWindow::listSelection()
{    
    return layerList;
}

QString MainWindow::listFirst()
{
    return layerList.first();
}

QString MainWindow::listLast()
{
    return layerList.last();
}

void MainWindow::updateList()
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
void MainWindow::doubleClickItem(int index)
{
    using namespace cl::DataManagement;

    QString layerName = layerList.at(index);
    auto layerItr = ShapeView::instance().findByName(layerName.toStdString());
    if (ShapeView::instance().layerNotFound(layerItr))
        return;

    ShapeView::instance().zoomToLayer(layerItr);
}

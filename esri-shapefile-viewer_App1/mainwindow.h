#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include "viewform.h"
#include "viewformcustome.h"
#include "mapwindow.h"
#include "shapemanager.h"
#include "map.h"

class QLabel;

class MainWindow : public QWidget,public cl::DataManagement::ShapeViewObserver
{
    Q_OBJECT    
    Q_PROPERTY(QStringList layerList READ listSelection NOTIFY updateLayerList)
public:

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    static MainWindow *m_instance;
    static MainWindow *getInstance();
    static QObject* getInstance(QQmlEngine *engine, QJSEngine *scriptEngine){Q_UNUSED(engine);Q_UNUSED(scriptEngine);return getInstance();}

    virtual void updateDisplay() override;
    virtual void setLabel(QString const& msg) override;

    QStringList layerList;

private:    

//    ViewForm* _viewForm;
    ViewFormCust* _viewFormCust = nullptr;
    std::unique_ptr<QLabel> _msgLabel;
    std::unique_ptr<MapWindow> _mapWindow;

    void createMap(cl::Map::MapStyle mapStyle);

public slots:
    Q_INVOKABLE void openDataset(QStringList filelist);
    Q_INVOKABLE void openDataset(QString file);
    Q_INVOKABLE void closeAll();
    Q_INVOKABLE void removeLayer(int LayerIndex);
    Q_INVOKABLE void layerUp(int LayerIndex);
    Q_INVOKABLE void layerDown(int LayerIndex);

    Q_INVOKABLE void createMapFullElements();
    Q_INVOKABLE void createMapNoGridLine();        
    Q_INVOKABLE QStringList listSelection();

    void updateList();

    QString listFirst();
    QString listLast();

    void doubleClickItem(int index);

signals:
    void updateLayerList();
};

#endif // MAINWINDOW_H

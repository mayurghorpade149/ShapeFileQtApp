#include "mainwindow.h"
#include <QObject>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include "support.h"
#include "mainwindowglobalcontext.h"

int main(int argc, char* argv[])
{
    MainWindowGlobalContext *m_MainWindowGlobalContext;
    m_MainWindowGlobalContext = MainWindowGlobalContext::getInstance();

    QApplication app(argc, argv);
    app.setOrganizationName("pdrl");

//    qmlRegisterType<MainWindow>("ShapeFileLib", 1, 0, "MainWindow");
    qmlRegisterSingletonType<MainWindow>("ShapeFileLib",1, 0, "MainWindow", &MainWindow::getInstance);
    qmlRegisterType<MapWindow>("ShapeFileLib", 1, 0, "MapWindow");
//    qmlRegisterSingletonType<MapWindow>("ShapeFileLib",1, 0, "MapWindow", &MapWindow::getInstance);
    qmlRegisterType<ViewForm>("ShapeFileLib", 1, 0, "ViewForm");
    qmlRegisterType<ViewFormCust>("ShapeFileLib", 1, 0, "ViewFormCust");
//    qmlRegisterSingletonType<ViewForm>("ShapeFileLib",1, 0, "ViewForm", &ViewForm::getInstance);


    app.processEvents(QEventLoop::AllEvents);
    m_MainWindowGlobalContext->appInit(&app);

    QQmlApplicationEngine engine;
    m_MainWindowGlobalContext->engineStart(&engine);

//    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:/mainui.qml")));

    QObject *rootObj = nullptr;

    rootObj = engine.rootObjects().at(engine.rootObjects().count()-1);
    qDebug() << " Class Name =" << rootObj->metaObject()->className();
    QQuickWindow *w = qobject_cast<QQuickWindow*>(rootObj);
//    w->setFlags(Qt::Window | Qt::FramelessWindowHint );

    return app.exec();
}

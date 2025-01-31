#include "mainwindowglobalcontext.h"
#include <QMessageBox>

MainWindowGlobalContext* MainWindowGlobalContext::m_MainWindowGlobalContext;

MainWindowGlobalContext::MainWindowGlobalContext(QObject *parent) :
    QObject(parent)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
}

void MainWindowGlobalContext::mainWindowRegisterQML()
{

}
void MainWindowGlobalContext::uiUpdateLoop()
{
    app->processEvents();
}
int MainWindowGlobalContext::appInit(QApplication *appPtr)
{
    app = appPtr;
    return 1;
}
int MainWindowGlobalContext::appExec()
{
    return app->exec();
}

int MainWindowGlobalContext::loadEngine(QUrl url)
{
    qDebug()<< "----- load qml";
    //  app->quit();
    qDebug() << engine->rootObjects().at(0)->objectName() <<endl;
    rootObj = engine->rootObjects().at(0);
    qDebug() << " Class Name =" << rootObj->metaObject()->className();
    QQuickWindow *w = qobject_cast<QQuickWindow*>(rootObj);
    w->close();
    engine->load(url);
    //    app->exec();
    return 0;
}


int MainWindowGlobalContext::engineStart(QQmlApplicationEngine *m_engine)
{
    engine = m_engine;
    return 1;
}

QQmlApplicationEngine * MainWindowGlobalContext::getEngine()
{
    return engine ;
}

MainWindowGlobalContext* MainWindowGlobalContext::getInstance()
{
    if(!m_MainWindowGlobalContext)
    {
        m_MainWindowGlobalContext = new MainWindowGlobalContext();
    }

    return m_MainWindowGlobalContext;
}
QObject* MainWindowGlobalContext::getRootObject()
{
    if(!engine->rootObjects().isEmpty())
        return engine->rootObjects().at(0);
    return nullptr;
}

void MainWindowGlobalContext::setRootObject(QObject* m_rootObject)
{
    rootObject = m_rootObject;
}

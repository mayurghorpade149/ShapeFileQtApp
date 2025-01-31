#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T10:57:12
#
#-------------------------------------------------

QT += quick
QT += widgets sql positioning location
QT += qml quick
QT += gui
QT += core
QT += network
QT += xml
QT += svg
QT += texttospeech
QT += multimedia
QT += core-private
QT += multimedia
QT += opengl
QT += concurrent
QT += quickwidgets
QT += sql
QT += multimediawidgets
QT += websockets
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = esri-shapefile-viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
    ../shapelib/dbfopen.cpp \
    ../shapelib/shpopen.cpp \
    ../shapelib/shptree.cpp \
    main.cpp \
    mainwindowglobalcontext.cpp \
    viewform.cpp \
    shapemanager.cpp \
    shapedata.cpp \
    map.cpp \
    mainwindow.cpp \
    mapwindow.cpp \
    viewformcustome.cpp

HEADERS  += \
    ../shapelib/shapefil.h \
    mainwindowglobalcontext.h \
    viewform.h \
    shapedata.h \
    shapemanager.h \
    nsdef.h \
    support.h \
    map.h \
    mainwindow.h \
    mapwindow.h \
    viewformcustome.h

#FORMS    += mainwindow.ui \
#    viewform.ui \
#    sidebar.ui \
#    mapwindow.ui

RESOURCES += qml.qrc \

DISTFILES += \
    mainui.qml

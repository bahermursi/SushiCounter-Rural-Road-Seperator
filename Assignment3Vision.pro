#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T18:56:10
#
#-------------------------------------------------

QT       += core gui

QMAKE_MAC_SDK = macosx10.12
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment3Vision
TEMPLATE = app

CONFIG += c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    detectimage.cpp \
    segmentimage.cpp

HEADERS  += mainwindow.h \
    detectimage.h \
    segmentimage.h

FORMS    += mainwindow.ui

LIBS += -L/usr/local/Cellar/opencv3/3.1.0_4/share/OpenCV/3rdparty/lib/

QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv

RESOURCES += \
    resources.qrc

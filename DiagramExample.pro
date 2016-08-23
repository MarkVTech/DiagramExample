#-------------------------------------------------
#
# Project created by QtCreator 2016-08-15T16:11:34
#
#-------------------------------------------------

include(libavoid/libavoid.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicsViewPlaying
TEMPLATE = app
DEFINES += _AFXDLL

SOURCES += main.cpp\
        mainwindow.cpp \
    drawingscene.cpp \
    shims.cpp \
    rectangleshape.cpp \
    shapebase.cpp \
    edge.cpp

HEADERS  += mainwindow.h \
    drawingscene.h \
    shims.h \
    rectangleshape.h \
    shapebase.h \
    edge.h

FORMS    += mainwindow.ui

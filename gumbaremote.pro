#-------------------------------------------------
#
# Project created by QtCreator 2012-05-19T20:14:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gumbaremote
TEMPLATE = app

include(qextserialport/src/qextserialport.pri)
include(wiimote/wiimote.pri)

LIBS += -lqjson

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

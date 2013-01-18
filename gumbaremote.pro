#-------------------------------------------------
#
# Project created by QtCreator 2012-05-19T20:14:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gumbaremote
TEMPLATE = app

include(/home/timon/development/qextserialport/src/qextserialport.pri)
include(wiimote.pri)

#LIBS += -L/home/timon/development/qextserialport/lib -lqextserialport
#INCLUDEPATH += /home/timon/development/qextserialport/src/*

LIBS += -lqjson

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

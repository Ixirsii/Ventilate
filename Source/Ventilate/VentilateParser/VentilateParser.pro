#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T13:20:23
#
#-------------------------------------------------

QT       -= gui

TARGET = VentilateParser
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ventilateparser.cpp

HEADERS += ventilateparser.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

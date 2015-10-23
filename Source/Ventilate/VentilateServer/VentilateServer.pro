QT += core network
QT -= gui

TARGET = VentilateServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += connectionhandler.h server.h

SOURCES += main.cpp connectionhandler.cpp server.cpp


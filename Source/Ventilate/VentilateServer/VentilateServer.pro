QT += core
QT -= gui
QT += network

TARGET = VentilateServer
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    connectionhandler.cpp \
    server.cpp

HEADERS += \
    connectionhandler.h \
    server.h


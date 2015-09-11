QT += core
QT -= gui
QT += network

TARGET = BitChatServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    connectionhandler.cpp

HEADERS += \
    server.h \
    connectionhandler.h


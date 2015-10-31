QT += core
QT += network
QT -= gui

TARGET = Socket_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    socket_test.cpp

HEADERS += \
    socket_test.h

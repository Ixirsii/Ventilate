#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T13:11:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VentilateClient
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    chatroomlistener.cpp \
    mainwindow.cpp

HEADERS  += \
    chatroomlistener.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui

RESOURCES +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/release/ -llibVentilate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/debug/ -llibVentilate
else:unix: LIBS += -L$$OUT_PWD/../libVentilate/ -llibVentilate

INCLUDEPATH += $$PWD/../libVentilate
DEPENDPATH += $$PWD/../libVentilate


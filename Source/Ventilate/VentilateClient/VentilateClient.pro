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
        mainwindow.cpp \
    socket.cpp \
    account.h \
    chatroom.cpp \
    message.cpp \
    client.cpp \
    chatroomlistener.cpp

HEADERS  += mainwindow.h \
    socket.h \
    account.h \
    chatroom.h \
    message.h \
    client.h \
    chatroomlistener.h

FORMS    += mainwindow.ui

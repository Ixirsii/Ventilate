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
    chatroomlistener.cpp \
    ventilate_about.cpp \
    ventilate_changepassword.cpp \
    ventilate_createchat.cpp \
    ventilate_help.cpp \
    ventilate_joinchat.cpp \
    ventilate_leavechat.cpp \
    ventilate_login.cpp \
    ventilate_newuser.cpp \
    ventilate_reportchat.cpp

HEADERS  += mainwindow.h \
    account.h \
    chatroom.h \
    chatroomlistener.h \
    client.h \
    message.h \
    socket.h \
    ventilate_about.h \
    ventilate_changepassword.h \
    ventilate_createchat.h \
    ventilate_help.h \
    ventilate_joinchat.h \
    ventilate_leavechat.h \
    ventilate_login.h \
    ventilate_newuser.h \
    ventilate_reportchat.h

FORMS    += mainwindow.ui \
    ventilate_about.ui \
    ventilate_changepassword.ui \
    ventilate_createchat.ui \
    ventilate_help.ui \
    ventilate_joinchat.ui \
    ventilate_leavechat.ui \
    ventilate_login.ui \
    ventilate_newuser.ui \
    ventilate_reportchat.ui


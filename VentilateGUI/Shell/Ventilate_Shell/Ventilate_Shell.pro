#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T01:25:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ventilate_Shell
TEMPLATE = app


SOURCES += main.cpp\
        ventilate.cpp \
    ventilate_createchat.cpp \
    chatroom.cpp \
    ventilate_login.cpp \
    ventilate_newuser.cpp

HEADERS  += ventilate.h \
    ventilate_createchat.h \
    chatroom.h \
    ventilate_login.h \
    ventilate_newuser.h

FORMS    += ventilate.ui \
    ventilate_createchat.ui \
    ventilate_login.ui \
    ventilate_newuser.ui

RESOURCES += \
    ventilate.qrc

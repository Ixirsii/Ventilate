#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T17:01:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ventialte-Shell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ventilate_login.cpp \
    ventilate_newuser.cpp \
    ventilate_createchat.cpp \
    ventilate_changepassword.cpp \
    ventilate_joinchat.cpp \
    ventilate_leavechat.cpp \
    ventilate_reportchat.cpp \
    ventilate_help.cpp \
    ventilate_about.cpp

HEADERS  += mainwindow.h \
    ventilate_login.h \
    ventilate_newuser.h \
    ventilate_createchat.h \
    ventilate_changepassword.h \
    ventilate_joinchat.h \
    ventilate_leavechat.h \
    ventilate_reportchat.h \
    ventilate_help.h \
    ventilate_about.h

FORMS    += mainwindow.ui \
    ventilate_login.ui \
    ventilate_newuser.ui \
    ventilate_createchat.ui \
    ventilate_changepassword.ui \
    ventilate_joinchat.ui \
    ventilate_leavechat.ui \
    ventilate_reportchat.ui \
    ventilate_help.ui \
    ventilate_about.ui

RESOURCES += \
    ventilate-shell_resources.qrc

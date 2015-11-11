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
    chatroomlistener.cpp \
    client.cpp \
    socket.cpp \
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
    chatroomlistener.h \
    client.h \
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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/release/ -llibVentilate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/debug/ -llibVentilate
else:unix: LIBS += -L$$OUT_PWD/../libVentilate/ -llibVentilate

INCLUDEPATH += $$PWD/../libVentilate
DEPENDPATH += $$PWD/../libVentilate

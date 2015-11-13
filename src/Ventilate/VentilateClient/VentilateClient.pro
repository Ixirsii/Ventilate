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
    ventilate.cpp \
    ventilate_createchat.cpp \
    ventilate_login.cpp \
    ventilate_newuser.cpp

HEADERS  += mainwindow.h \
    chatroomlistener.h \
    client.h \
    socket.h \
    ventilate.h \
    ventilate_createchat.h \
    ventilate_login.h \
    ventilate_newuser.h

FORMS    += mainwindow.ui \
    ventilate.ui \
    ventilate_createchat.ui \
    ventilate_login.ui \
    ventilate_newuser.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/release/ -llibVentilate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/debug/ -llibVentilate
else:unix: LIBS += -L$$OUT_PWD/../libVentilate/ -llibVentilate

INCLUDEPATH += $$PWD/../libVentilate
DEPENDPATH += $$PWD/../libVentilate

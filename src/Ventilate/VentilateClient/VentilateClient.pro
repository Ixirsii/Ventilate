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
    client.cpp \
    ventilate.cpp \
    ventilate_login.cpp \
    ventilate_newuser.cpp \
    abstractdialog.cpp \
    createchatui.cpp \
    joinchatui.cpp

HEADERS  += \
    chatroomlistener.h \
    client.h \
    ventilate.h \
    ventilate_login.h \
    ventilate_newuser.h \
    abstractdialog.h \
    createchatui.h \
    joinchatui.h

FORMS    += \
    ventilate.ui \
    ventilate_createchat.ui \
    ventilate_login.ui \
    ventilate_newuser.ui \
    joinchatui.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/release/ -llibVentilate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/debug/ -llibVentilate
else:unix: LIBS += -L$$OUT_PWD/../libVentilate/ -llibVentilate

INCLUDEPATH += $$PWD/../libVentilate
DEPENDPATH += $$PWD/../libVentilate

RESOURCES += \
    ventilate.qrc

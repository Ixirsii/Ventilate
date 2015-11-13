#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T00:05:29
#
#-------------------------------------------------

QT       += network sql

QT       -= gui

CONFIG += c++11
TARGET = libVentilate
TEMPLATE = lib

DEFINES += LIBVENTILATE_LIBRARY

SOURCES += \
    connectionhandler.cpp \
    account.cpp \
    chatroom.cpp \
    message.cpp \
    database/accountdatabase.cpp \
    database/messagedatabase.cpp \
    database/chatroomdatabase.cpp \
    database/database.cpp \
    database/userdatabase.cpp \
    database/minidbinterface.cpp \
    database/moddatabase.cpp \
    server/server.cpp \
    server/commandparser.cpp \
    server/roomparser.cpp \
    server/accountparser.cpp \
    server/passwordparser.cpp \
    server/peerparser.cpp

HEADERS +=\
        libventilate_global.h \
    connectionhandler.h \
    commands.h \
    account.h \
    chatroom.h \
    message.h \
    database/databaseinterface.h \
    database/accountdatabase.h \
    database/messagedatabase.h \
    database/chatroomdatabase.h \
    database/database.h \
    database/userdatabase.h \
    database/minidbinterface.h \
    database/moddatabase.h \
    server/server.h \
    server/commandparser.h \
    server/roomparser.h \
    server/accountparser.h \
    server/passwordparser.h \
    server/peerparser.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

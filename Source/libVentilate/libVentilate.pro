#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T00:05:29
#
#-------------------------------------------------

QT       += network sql

QT       -= gui

TARGET = libVentilate
TEMPLATE = lib

DEFINES += LIBVENTILATE_LIBRARY

SOURCES += libventilate.cpp \
    server.cpp \
    connectionhandler.cpp

HEADERS += libventilate.h\
        libventilate_global.h \
    server.h \
    connectionhandler.h \
    commands.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

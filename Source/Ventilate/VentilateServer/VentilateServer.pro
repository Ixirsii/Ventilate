QT += core network
QT -= gui

TARGET = VentilateServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS +=

SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/release/ -llibVentilate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libVentilate/debug/ -llibVentilate
else:unix: LIBS += -L$$OUT_PWD/../libVentilate/ -llibVentilate

INCLUDEPATH += $$PWD/../libVentilate
DEPENDPATH += $$PWD/../libVentilate

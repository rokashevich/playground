QT       += core
QT       += network
QT       -= gui

TARGET = webServer3
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    myhttpserver.h

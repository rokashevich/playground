QT       += core
QT       += network
QT       -= gui

TARGET = httpd
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    httpd.h

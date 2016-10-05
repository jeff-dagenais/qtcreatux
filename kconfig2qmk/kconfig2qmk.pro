QT       += core
QT       -= gui

TARGET = kconfig2qmk
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

target.path = /usr/local/bin
INSTALLS += target

SOURCES += main.cpp

QT += core
QT -= gui

CONFIG += c++11

TARGET = parsing
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    city.cpp \
    route.cpp

HEADERS += \
    city.h \
    route.h

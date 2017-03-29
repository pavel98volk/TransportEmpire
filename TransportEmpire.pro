QT += core
QT -= gui

CONFIG += c++11

TARGET = TransportEmpire
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    city.cpp \
    path.cpp \
    route.cpp \
    route_statistics.cpp \
    race.cpp \
    race_statistics.cpp \
    bus_type_info.cpp \
    bus.cpp \
    scheduled_race.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    city.h \
    path.h \
    route.h \
    route_statistics.h \
    race.h \
    race_statistics.h \
    money.h \
    bus_type_info.h \
    bus.h \
    scheduled_race.h

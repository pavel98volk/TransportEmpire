QT += core websockets testlib
QT -= gui

CONFIG += c++11
CONFIG += warn_off

TARGET = TransportEmpire
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Model/bus.cpp \
    Model/bus_type_info.cpp \
    Model/city.cpp \
    Model/path.cpp \
    Model/race.cpp \
    Model/race_statistics.cpp \
    Model/route.cpp \
    Model/route_statistics.cpp \
    Model/scheduled_race.cpp \
    Server/webserver.cpp \
    main.cpp 

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
    Model/bus.h                 \
    Model/bus_type_info.h       \
    Model/city.h                \
    Model/money.h               \
    Model/path.h                \
    Model/race.h                \
    Model/race_statistics.h     \
    Model/route.h               \
    Model/route_statistics.h    \
    Model/scheduled_race.h      \
    Server/webserver.h \
    Test/test_suite.h


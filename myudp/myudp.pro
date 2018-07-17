TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS +=-lWs2_32

SOURCES += \
        main.cpp \
    udp.cpp

HEADERS += \
    udp.h \
    udp.h

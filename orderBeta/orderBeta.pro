#-------------------------------------------------
#
# Project created by QtCreator 2021-09-16T08:54:17
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = orderBeta
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    showui.cpp \
    showthread.cpp \
    linkthread.cpp \
    outlog.cpp \
    udpthread.cpp \
    head.cpp \
    tools.cpp \
    data.cpp \
    addtrackdialog.cpp \
    format06.cpp \
    link.cpp \
    udpconnect.cpp \
    SimulatorTradeProtos.pb.cc \
    timer.cpp

HEADERS += \
        mainwindow.h \
    showui.h \
    showthread.h \
    linkthread.h \
    outlog.h \
    udpthread.h \
    head.h \
    tools.h \
    data.h \
    addtrackdialog.h \
    format06.h \
    link.h \
    udpconnect.h \
    SimulatorTradeProtos.pb.h \
    timer.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += "tmp/lib/include"
INCLUDEPATH += "root/lib/protobuf-3.11.4/include"

LIBS += -L "/tmp/libpcap/lib" -lpcap
LIBS += /root/lib/protobuf-3.11.4/lib/libprotobuf.a
LIBS += /root/lib/protobuf-3.11.4/lib/libprotobuf-lite.a
LIBS += /root/lib/protobuf-3.11.4/lib/libprotoc.a

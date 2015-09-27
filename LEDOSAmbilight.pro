#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T00:05:30
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LiveScreenCaptureTest
TEMPLATE = app


SOURCES += main.cpp \
    screenanalyzer.cpp \
    ledostalker.cpp \
    settingswindow.cpp

HEADERS  += \
    screenanalyzer.h \
    ledostalker.h \
    settingswindow.h

FORMS    +=

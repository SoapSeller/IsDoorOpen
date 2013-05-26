#-------------------------------------------------
#
# Project created by QtCreator 2013-05-26T20:56:15
#
#-------------------------------------------------

QT       += core gui
QT += network

QMAKE_CXXFLAGS += -std=c++11



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Door
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

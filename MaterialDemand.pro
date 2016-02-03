#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T23:56:38
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MaterialDemand
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    comboboxdelegate.cpp

HEADERS  += mainwindow.h \
    comboboxdelegate.h

FORMS    += mainwindow.ui

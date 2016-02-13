#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T11:54:06
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Amanda_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cloth.cpp \
    connectdialog.cpp

HEADERS  += mainwindow.h \
    cloth.h \
    connectdialog.h

FORMS    += mainwindow.ui

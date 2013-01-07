#-------------------------------------------------
#
# Project created by QtCreator 2012-12-17T22:36:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = faceReplacer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    framelistwidget.cpp

HEADERS  += mainwindow.h \
    framelistwidget.h

FORMS    += mainwindow.ui

LIBS    += -lmagic

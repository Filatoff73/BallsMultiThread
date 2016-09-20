#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T19:00:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Balls
TEMPLATE = app


SOURCES += main.cpp\
        ballswindow.cpp \
    view.cpp \
    scene.cpp \
    ball.cpp \
    calculatethread.cpp

HEADERS  += ballswindow.h \
    view.h \
    scene.h \
    ball.h \
    consts.h \
    calculatethread.h

FORMS    += ballswindow.ui

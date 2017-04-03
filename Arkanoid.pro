#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T19:03:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arkanoid
TEMPLATE = app


SOURCES += main.cpp \
    arkanoid.cpp \
    bricks.cpp \
    platform.cpp \
    checkpoint.cpp

HEADERS  += \
    arkanoid.h \
    bricks.h \
    platform.h \
    checkpoint.h

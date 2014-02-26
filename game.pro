#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T01:00:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grid.cpp \
    snakepart.cpp \
    snake.cpp

HEADERS  += mainwindow.h \
    grid.h \
    snakepart.h \
    snake.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    main.qrc

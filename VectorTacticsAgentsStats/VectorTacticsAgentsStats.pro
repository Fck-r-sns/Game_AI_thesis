#-------------------------------------------------
#
# Project created by QtCreator 2017-05-28T14:31:15
#
#-------------------------------------------------

QT += core gui sql
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VectorTacticsAgentsStats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp

HEADERS  += mainwindow.h \
    parser.h

FORMS    += mainwindow.ui

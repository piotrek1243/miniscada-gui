#-------------------------------------------------
#
# Project created by QtCreator 2014-06-12T18:34:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = miniscada-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serie.cpp \
    linestyle.cpp \
    legend.cpp \
    label.cpp \
    icon.cpp \
    geometry.cpp \
    chart.cpp \
    axis.cpp

HEADERS  += mainwindow.h \
    serie.h \
    orientation.h \
    linestyle.h \
    legend.h \
    label.h \
    icon.h \
    geometry.h \
    chart.h \
    axis.h

FORMS    += mainwindow.ui

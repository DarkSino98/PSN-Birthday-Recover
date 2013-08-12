#-------------------------------------------------
#
# Project created by QtCreator 2013-08-02T22:12:41
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSN_Birthday_Recover
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutwindow.cpp \
    networkconnexion.cpp

HEADERS  += mainwindow.h \
    aboutwindow.h \
    networkconnexion.h

FORMS    += mainwindow.ui \
    aboutwindow.ui

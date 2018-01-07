#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T10:38:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projekt_wegierski
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        grafwindow.cpp \
    grafgenerprzeplyw.cpp \
    grafkonwprzeplyw.cpp \
    grafmaksprzeplyw.cpp \
    grafrysujprzeplyw.cpp \
    w_algorytm.cpp \
    ggenerator.cpp

HEADERS += \
        grafwindow.h \
    grafgenerprzeplyw.h \
    grafkonwprzeplyw.h \
    grafmaksprzeplyw.h \
    grafrysujprzeplyw.h \
    w_algorytm.h \
    ggenerator.h

FORMS += \
        grafwindow.ui \
    ggenerator.ui

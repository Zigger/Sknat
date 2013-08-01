#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T11:11:46
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks
TEMPLATE = app


SOURCES += main.cpp\
        tgraphics.cpp \
    tworldmap.cpp \
    tobjects.cpp \
    buffer.cpp \
    tbasemechanicks.cpp \
    tinputcatcher.cpp \
    TGraphDescriptions.cpp

HEADERS  += tgraphics.h \
    tworldmap.h \
    tobjects.h \
    buffer.h \
    tbasemechanicks.h \
    tinputcatcher.h \
    TGraphDescriptions.h

FORMS    += tgraphics.ui

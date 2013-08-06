TEMPLATE = app
CONFIG += console
CONFIG += opengl
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    sdlinterface.cpp \
    tobjects.cpp \
    mainmap.cpp \
    mainmechanicks.cpp \
    inputcatcher.cpp \
    graphmodels.cpp

INCLUDEPATH += C:\Qt\SDL-1.2.15\include\SDL

LIBS += -lSDL
LIBS += -lSDLmain
#LIBS += -lmingw32

HEADERS += \
    sdlinterface.h \
    tobjects.h \
    mainmap.h \
    mainmechanicks.h \
    inputcatcher.h \
    graphmodels.h


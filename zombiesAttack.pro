#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T10:33:21
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = zombiesAttack
TEMPLATE = app

QMAKE_CXXFLAGS = -Wall


SOURCES += main.cpp\
        view.cpp \
    model.cpp \
    controller.cpp \
    graphicsagent.cpp \
    agent.cpp \
    strategy.cpp \
    humanstrategy.cpp \
    zombiestrategy.cpp \
    hunterstrategy.cpp \
    graphicsshot.cpp \
    hunterzombiestrategy.cpp

HEADERS  += view.h \
    model.h \
    controller.h \
    graphicsagent.h \
    agent.h \
    strategy.h \
    humanstrategy.h \
    zombiestrategy.h \
    hunterstrategy.h \
    graphicsshot.h \
    hunterzombiestrategy.h

FORMS    += view.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    ideas.txt

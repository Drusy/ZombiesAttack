#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T10:33:21
#
#-------------------------------------------------

QT       += core gui testlib declarative widgets

TARGET = zombiesAttack
TEMPLATE = app

QMAKE_CXXFLAGS = -D_USE_MATH_DEFINES

SOURCES += main.cpp\
        view.cpp \
    model/model.cpp \
    controller.cpp \
    graphicsagent.cpp \
    model/agent.cpp \
    strategy/strategy.cpp \
    strategy/humanstrategy.cpp \
    strategy/zombiestrategy.cpp \
    strategy/hunterstrategy.cpp \
    graphicsshot.cpp \
    strategy/hunterzombiestrategy.cpp \
    strategy/humanbuilderstrategy.cpp \
    strategy/block.cpp \
    tests/agenttest.cpp \
    tests/modeltest.cpp \
    model/poolagent.cpp

HEADERS  += view.h \
    model/model.h \
    controller.h \
    graphicsagent.h \
    model/agent.h \
    strategy/strategy.h \
    strategy/humanstrategy.h \
    strategy/zombiestrategy.h \
    strategy/hunterstrategy.h \
    graphicsshot.h \
    strategy/hunterzombiestrategy.h \
    strategy/humanbuilderstrategy.h \
    strategy/block.h \
    tests/autotest.h \
    tests/agenttest.h \
    tests/modeltest.h \
    model/poolagent.h

FORMS    += view.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    ideas.txt

### eqmake4 was here ###
CONFIG -= debug_and_release debug
CONFIG += release

QMAKE_LFLAGS += -fopenmp

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    levelmap.cpp \
    gamecontroller.cpp \
    draw.cpp \
    keys.cpp \
    state.cpp \
    block.cpp \
    player.cpp \
    pellet.cpp

HEADERS += \
    levelmap.h \
    gamecontroller.h \
    draw.h \
    state.h \
    player.h \
    pellet.h


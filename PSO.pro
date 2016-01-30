TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tools.cpp \
    energy.cpp \
    pso.cpp

HEADERS += tools.h \
    energy.hpp \
    pso.hpp
LIBS+=-L/usr/local/lib -lopencv_core -lopencv_highgui
INCLUDEPATH+=/usr/local/include

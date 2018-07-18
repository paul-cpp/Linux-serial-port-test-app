TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Weffc++ -pedantic -march=native

SOURCES += \
    src/client.cpp \
    src/main.cpp \
    src/serialport.cpp \
    src/server.cpp

LIBS += -lpthread

HEADERS += \
    include/client.h \
    include/serialport.h \
    include/server.h

INCLUDEPATH += ./include/



DISTFILES += \
    in.txt

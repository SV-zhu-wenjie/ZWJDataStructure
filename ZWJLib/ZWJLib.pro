TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Object.cpp

HEADERS += \
    Smartpointer.h \
    Exception.h \
    Object.h \
    List.h \
    Seqlist.h \
    StaticList.h \
    Dynamiclist.h \
    array.h \
    StaticArray.h \
    DynamicArray.h \
    LinkList.h

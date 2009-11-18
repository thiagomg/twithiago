# -------------------------------------------------
# Project created by QtCreator 2009-10-23T12:12:40
# -------------------------------------------------
QT += network \
    xml
CONFIG += oauth \
    crypto
TARGET = Twithiago
TEMPLATE = app
SOURCES += main.cpp \
    wndtimeline.cpp \
    twitter.cpp \
    friendlisthandler.cpp \
    Timeline.cpp
HEADERS += wndtimeline.h \
    twitter.h \
    friendlisthandler.h \
    Timeline.h
FORMS += wndtimeline.ui

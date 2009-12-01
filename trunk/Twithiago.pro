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
    Timeline.cpp \
    Credentials.cpp \
    Config.cpp \
    frmconfig.cpp \
    QTwitPicture.cpp
HEADERS += wndtimeline.h \
    twitter.h \
    friendlisthandler.h \
    Timeline.h \
    Credentials.h \
    Config.h \
    frmconfig.h \
    QTwitPicture.h \
    TextUpdate.h
FORMS += wndtimeline.ui \
    frmconfig.ui

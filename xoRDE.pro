QT += gui websockets svg widgets core
TARGET = XORDE
TEMPLATE = app

include("../xoTools/Compilation.pri")
include("../xoCore/xoCore.pri")

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    xoPrimitiveConsole.cpp

RESOURCES += xo.qrc

win32: RC_ICONS += xo.ico

HEADERS += \
    xoPrimitiveConsole.h

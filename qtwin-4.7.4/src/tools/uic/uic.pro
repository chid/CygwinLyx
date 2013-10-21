TEMPLATE = app
TARGET = uic

DESTDIR = ../../../bin
DEFINES += QT_UIC
INCLUDEPATH += .
DEPENDPATH += .
win32:VPATH += $$QT_SOURCE_TREE/src/tools

!contains(QT_CONFIG, qt3support):DEFINES += QT_NO_QT3_SUPPORT

include(uic.pri)
include(cpp/cpp.pri)

HEADERS += uic.h

SOURCES += main.cpp \
           uic.cpp

include(../bootstrap/bootstrap.pri)

target.path=$$[QT_INSTALL_BINS]
INSTALLS += target
include(../../qt_targets.pri)

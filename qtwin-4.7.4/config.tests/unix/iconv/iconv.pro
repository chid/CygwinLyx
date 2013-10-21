SOURCES = iconv.cpp
CONFIG -= qt dylib app_bundle
mac|win32-g++*|cygwin-g++*:LIBS += -liconv

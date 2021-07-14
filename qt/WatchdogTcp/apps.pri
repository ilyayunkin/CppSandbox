
ROOT_DIR=../
CONFIG += c++17
INCLUDEPATH+=../

DESTDIR= ../bin

QMAKE_CXXFLAGS+= -pedantic-errors
QMAKE_CXXFLAGS+= -Wformat=2
QMAKE_CXXFLAGS+= -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond
QMAKE_CXXFLAGS+= -Wcast-qual -Wcast-align -Wfloat-equal

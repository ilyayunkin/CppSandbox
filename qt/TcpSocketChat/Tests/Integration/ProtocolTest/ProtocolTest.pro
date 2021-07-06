QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_protocoltest.cpp \
    ../../../ChatClient/ClientQuery.cpp \
    ../../../ChatServer/ServerParser.cpp

HEADERS += \
    ../../../ChatClient/ClientQuery.h \
    ../../../ChatServer/AbstractClientCommand.h \
    ../../../ChatServer/AbstractClientCommandVisitor.h \
    ../../../ChatServer/ServerParser.h \
    ../../../ChatServer/AbstractClientCommand.h \
    ../../../ChatServer/ClientCommandName.h

INCLUDEPATH+=../../../

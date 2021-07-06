QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_protocoltest.cpp \
    ../../../ChatClient/ClientParser.cpp \
    ../../../ChatClient/ClientQuery.cpp \
    ../../../ChatServer/ServerParser.cpp \
    ../../../ChatServer/ServerQuery.cpp \
    ../../../Utilities/JsonUtilities.cpp

HEADERS += \
    ../../../ChatClient/AbstractServerCommand.h \
    ../../../ChatClient/AbstractServerCommandVisitor.h \
    ../../../ChatClient/ClientParser.h \
    ../../../ChatClient/ClientQuery.h \
    ../../../ChatServer/AbstractClientCommand.h \
    ../../../ChatServer/AbstractClientCommandVisitor.h \
    ../../../ChatServer/ClientCommandText.h \
    ../../../ChatServer/ServerParser.h \
    ../../../ChatServer/AbstractClientCommand.h \
    ../../../ChatServer/ClientCommandName.h \
    ../../../ChatServer/ServerQuery.h \
    ../../../Utilities/JsonUtilities.h

INCLUDEPATH+=../../../

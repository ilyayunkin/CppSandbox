#ifndef SERVERPARSER_H
#define SERVERPARSER_H

#include "AbstractClientCommand.h"

class QByteArray;

class ServerParser
{
public:
    ServerParser();
    ClientCommandPtr parse(QByteArray data);
};

#endif // SERVERPARSER_H

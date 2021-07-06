#ifndef CLIENTPARSER_H
#define CLIENTPARSER_H

#include "AbstractServerCommand.h"

class QByteArray;
class ClientParser
{
public:
    ServerCommandPtrList parse(const QByteArray data);
private:
    ServerCommandPtr parseOneObject(const QByteArray data);
};

#endif // CLIENTPARSER_H

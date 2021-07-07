#ifndef CLIENTPARSER_H
#define CLIENTPARSER_H

#include "AbstractServerCommand.h"
#include "Utilities/JsonUtilities.h"

class QByteArray;
class ClientParser
{
public:
    ServerCommandPtrList parse(const QByteArray data);
private:
    ServerCommandPtr parseOneObject(const QByteArray data);
    JsonUtilities::JsonDefragmentator jsonDefragmentator_;
};

#endif // CLIENTPARSER_H

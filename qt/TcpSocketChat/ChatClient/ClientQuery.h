#ifndef CLIENTQUERY_H
#define CLIENTQUERY_H

class QByteArray;
class QString;

class ClientQuery
{
public:
    static QByteArray sendName(QString name);
    static QByteArray sendText(QString text);
};

#endif // CLIENTQUERY_H

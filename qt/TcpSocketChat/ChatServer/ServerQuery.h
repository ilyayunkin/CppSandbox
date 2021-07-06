#ifndef SERVERQUERY_H
#define SERVERQUERY_H

class QByteArray;
class QString;
class QStringList;

struct ServerQuery
{
    static QByteArray sendUserList(const QStringList userList);
    static QByteArray sendChat(const QString chat);
};

#endif // SERVERQUERY_H

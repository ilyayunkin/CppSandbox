#include "ServerQuery.h"

#include <QByteArray>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QByteArray ServerQuery::sendUserList(const QStringList userList)
{
    QJsonArray jsonArray;
    std::copy(userList.cbegin(), userList.cend(), std::back_inserter(jsonArray));

    QJsonDocument doc{
        QJsonObject{
            {"command", "user_list"},
            {"user_list", jsonArray}
        }
    };
    return doc.toJson();
}

QByteArray ServerQuery::sendChat(const QString chat)
{
    QJsonDocument doc{
        QJsonObject{
            {"command", "chat"},
            {"chat", chat}
        }
    };
    return doc.toJson();
}

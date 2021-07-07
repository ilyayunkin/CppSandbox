#include "ClientQuery.h"

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

QByteArray ClientQuery::sendName(QString name)
{
    QJsonDocument doc{
        QJsonObject{
            {"command", "name"},
            {"name", name}
        }
    };
    return doc.toJson();
}

QByteArray ClientQuery::sendText(QString text)
{
    QJsonDocument doc{
        QJsonObject{
            {"command", "message"},
            {"text", text}
        }
    };
    return doc.toJson();
}

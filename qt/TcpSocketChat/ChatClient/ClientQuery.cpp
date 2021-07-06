#include "ClientQuery.h"
#include <QByteArray>
#include <QString>

QByteArray ClientQuery::sendName(QString name)
{
    return QString(
R"JS({"command":"name",
"name":"%1"})JS"
                )
            .arg(name).toUtf8();
}

QByteArray ClientQuery::sendText(QString text)
{
    return QString(
R"JS({"command":"message",
"text":"%1"})JS"
                     )
                 .arg(text).toUtf8();
}

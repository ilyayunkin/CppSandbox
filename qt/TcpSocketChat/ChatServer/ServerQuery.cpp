#include "ServerQuery.h"

#include <QByteArray>
#include <QStringList>

QByteArray ServerQuery::sendUserList(const QStringList userList)
{
    auto serialize = [&]{
        QString jsonArray;
        auto i = 0;
        for(const auto user : userList){
            if(i){
                jsonArray+= ",";
            }
            jsonArray+= "\"" + user + "\"";
            ++i;
        }
        return jsonArray;
    };
    return QString(
R"JS({"command":"user_list",
"user_list":[%1]})JS"
                )
            .arg(serialize()).toUtf8();
}

QByteArray ServerQuery::sendChat(const QString chat)
{
    return QString(
R"JS({"command":"chat",
"chat":"%1"})JS"
                )
            .arg(chat).toUtf8();

}

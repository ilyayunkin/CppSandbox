#include "ClientParser.h"

#include "ServerCommandUserList.h"
#include "ServerCommandChat.h"
#include "Utilities/JsonUtilities.h"

#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ServerCommandPtrList ClientParser::parse(const QByteArray data)
{
    ServerCommandPtrList ret;
    const auto frames = JsonUtilities::split(data);

    for(const auto frame : frames){
        ret.push_back(parseOneObject(frame));
    }

    return ret;
}

ServerCommandPtr ClientParser::parseOneObject(const QByteArray data)
{
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isObject()){
        qDebug() << "Not an object:" << data;
        return ServerCommandPtr();
    }

    const auto obj = doc.object();
    if(!obj.contains("command")){
        qDebug() << "No command:" << data;
        return ServerCommandPtr();
    }

    const auto command = obj.value("command").toString();
    if(command == "user_list"){
        if(!obj.contains("user_list")){
            qDebug() << "No user_list:" << data;
            return ServerCommandPtr();
        }

        const auto jsonValue = obj.value("user_list");
        if(!jsonValue.isArray()){
            qDebug() << "Not array:" << data;
            return ServerCommandPtr();
        }

        const auto jsonArray = jsonValue.toArray();
        QStringList list;
        for(auto const item : jsonArray){
            list << item.toString();
        }
        return std::make_unique<ServerCommandUserList>(list);
    }else if(command == "chat"){
        if(!obj.contains("chat")){
            qDebug() << "No chat:" << data;
            return ServerCommandPtr();
        }
        const auto chat = obj.value("chat").toString();

        return std::make_unique<ServerCommandChat>(chat);
     }

    return ServerCommandPtr();
}

#include "ServerParser.h"

#include "ClientCommandName.h"
#include "ClientCommandText.h"

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ServerParser::ServerParser()
{

}

ClientCommandPtr ServerParser::parse(QByteArray data)
{
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isObject()){
        qDebug() << "Not an object:" << data;
        return ClientCommandPtr();
    }

    const auto obj = doc.object();
    if(!obj.contains("command")){
        qDebug() << "No command:" << data;
        return ClientCommandPtr();
    }

    const auto command = obj.value("command").toString();
    if(command == "message"){
        if(!obj.contains("text")){
            qDebug() << "No text:" << data;
            return ClientCommandPtr();
        }
        const auto text = obj.value("text").toString();
        return std::make_unique<ClientCommandText>(text);
    }else if(command == "name"){
        if(!obj.contains("name")){
            qDebug() << "No name:" << data;
            return ClientCommandPtr();
        }
        const auto name = obj.value("name").toString();

        return std::make_unique<ClientCommandName>(name);
     }
    return ClientCommandPtr();
}

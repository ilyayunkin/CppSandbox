#include "Server.h"
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

Server::Server(QObject *parent)
    : QObject(parent)
{
    if(!server.listen(QHostAddress::Any, 7050)){
        QMessageBox::critical(
                    nullptr, "Unable to open connection",
                    "Unable to open connection");
    }else{
        connect(&server, &QTcpServer::newConnection,
                this, &Server::clientConnected);
    }
}

void Server::clientConnected()
{
    QTcpSocket *const clientSocket =
            server.nextPendingConnection();
    if(clientSocket != nullptr)
    {
        QObject::connect(clientSocket, &QTcpSocket::disconnected,
                         this, &Server::clientDisconnected);
        connect(clientSocket, &QTcpSocket::readyRead,
                this, &Server::dataReceived);
        sockets_.push_back(clientSocket);

        qDebug() << "Client connected";
    }
}

void Server::clientDisconnected()
{
    qDebug() << "Client disconnected";
    QTcpSocket *const clientSocket =
            dynamic_cast<QTcpSocket *>(sender());

    auto clientName = names_[clientSocket];
    chat_+= "\r\n" + clientName + " left the chat";
    updateChat();

    sockets_.removeAll(clientSocket);
    clientSocket->deleteLater();
}

void Server::dataReceived()
{
    qDebug() << "Data received";
    QTcpSocket *const clientSocket =
            dynamic_cast<QTcpSocket *>(sender());

    assert(QString(sender()->metaObject()->className()) ==
           QString("QTcpSocket"));
    assert(clientSocket != nullptr);

    auto data = clientSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isObject()){
        qDebug() << "Not an object:" << data;
        return;
    }

    auto obj = doc.object();
    if(!obj.contains("command")){
        qDebug() << "No command:" << data;
        return;
    }

    auto command = obj.value("command").toString();
    if(command == "message"){
        if(!obj.contains("text")){
            qDebug() << "No text:" << data;
            return;
        }
        auto text = obj.value("text").toString();

        auto clientName = names_[clientSocket];
        chat_+= "\r\n" + clientName + ":" + text;
        emit updateChat();
    }else if(command == "name"){
        if(!obj.contains("name")){
            qDebug() << "No name:" << data;
            return;
        }
        auto name = obj.value("name").toString();

        names_[clientSocket] = name;
        chat_+= "\r\n" + name + " joined the chat!";
        updateChat();
    }
}

void Server::updateChat()
{
    chatChanged(chat_);

    for(auto socket : sockets_)
        socket->write(chat_.toUtf8());
}

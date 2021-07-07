#include "Server.h"

#include "ClientCommandName.h"
#include "ClientCommandText.h"
#include "ServerQuery.h"

#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include <assert.h>

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
        names_[clientSocket] = QString();

        qDebug() << "Client connected";
    }
}

void Server::clientDisconnected()
{
    qDebug() << "Client disconnected";
    QTcpSocket *const clientSocket =
            dynamic_cast<QTcpSocket *>(sender());

    const auto clientName = names_[clientSocket];
    chat_+= "\r\n" + clientName + " left the chat";
    updateChat();

    names_.erase(clientSocket);
    clientSocket->deleteLater();

    updateUserList();
}

void Server::dataReceived()
{
    qDebug() << "Data received";
    tmpSocket_ = dynamic_cast<QTcpSocket *>(sender());

    assert(QString(sender()->metaObject()->className()) ==
           QString("QTcpSocket"));
    assert(tmpSocket_ != nullptr);

    const auto commandPtr = parser_.parse(tmpSocket_->readAll());
    commandPtr->accept(*this);
}

void Server::updateChat()
{
    emit chatChanged(chat_);

    for(const auto socket : names_){
        const auto clientSocket = socket.first;
        clientSocket->write(ServerQuery::sendChat(chat_));
    }
}

void Server::updateUserList()
{
    QStringList userList;
    for(const auto socket : names_){
        const auto name = socket.second;
        userList.append(name);
    }
    for(const auto socket : names_){
        const auto clientSocket = socket.first;
        clientSocket->write(ServerQuery::sendUserList(userList));
    }
}

void Server::visit(const ClientCommandName &command)
{
    assert(tmpSocket_);

    names_[tmpSocket_] = command.name;
    chat_+= "\r\n" + command.name + " joined the chat!";

    updateChat();
    updateUserList();
}

void Server::visit(const ClientCommandText &command)
{
    assert(tmpSocket_);

    const auto clientName = names_[tmpSocket_];
    chat_+= "\r\n" + clientName + ":" + command.text;
    emit updateChat();
}

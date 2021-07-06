#include "Server.h"

#include "ClientCommandName.h"
#include "ClientCommandText.h"

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
    tmpSocket_ = dynamic_cast<QTcpSocket *>(sender());

    assert(QString(sender()->metaObject()->className()) ==
           QString("QTcpSocket"));
    assert(tmpSocket_ != nullptr);

    auto commandPtr = parser_.parse(tmpSocket_->readAll());
    commandPtr->accept(*this);
}

void Server::updateChat()
{
    chatChanged(chat_);

    for(auto socket : sockets_)
        socket->write(chat_.toUtf8());
}

void Server::visit(ClientCommandName &command)
{
    assert(tmpSocket_);

    names_[tmpSocket_] = command.name;
    chat_+= "\r\n" + command.name + " joined the chat!";
    updateChat();
}

void Server::visit(ClientCommandText &command)
{
    assert(tmpSocket_);

    auto clientName = names_[tmpSocket_];
    chat_+= "\r\n" + clientName + ":" + command.text;
    emit updateChat();
}

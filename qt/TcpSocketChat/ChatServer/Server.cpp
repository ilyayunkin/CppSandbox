#include "Server.h"
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>

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

    QDataStream dataStream(clientSocket);

    chat_+= "\r\n" + clientSocket->readAll();
    chatChanged(chat_);

    for(auto socket : sockets_)
        socket->write(chat_.toUtf8());
}

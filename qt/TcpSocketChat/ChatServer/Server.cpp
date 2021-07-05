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
        QObject::connect(clientSocket, SIGNAL(disconnected()),
                         clientSocket, SLOT(deleteLater()));
        connect(clientSocket, &QTcpSocket::readyRead,
                this, &Server::dataReceived);

        qDebug() << "Client connected";
    }
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
}

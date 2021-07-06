#include "Client.h"

#include "ClientQuery.h"

#include <QMetaEnum>
#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>

Client::Client(QObject *parent)
    : QObject(parent)
{
    connect(&socket, SIGNAL(connected()),
            SIGNAL(connected()));
    connect(&socket, SIGNAL(disconnected()),
            SIGNAL(disconnected()));
    connect(&socket, &QTcpSocket::disconnected,
            this, &Client::onDisconnected);

    connect(&socket, &QTcpSocket::connected,
            this, &Client::onConnected);
    connect(&socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, &Client::onError);
    connect(&socket, &QTcpSocket::readyRead,
            this, &Client::onDataReceived);

    socket.connectToHost("localhost", 7050);
}

void Client::sendMessage(QString message)
{
    socket.write(ClientQuery::sendText(message));
}

void Client::onConnected()
{
    qDebug() << "Connected";
    auto name = QInputDialog::getText(nullptr, tr("Input your name"), tr("name"));
    socket.write(ClientQuery::sendName(name));
}

void Client::onError(QAbstractSocket::SocketError socketError)
{
    const QMetaEnum metaEnum =
            QMetaEnum::fromType<
            QAbstractSocket::SocketError>();
    /// Строковое представление значения перечислимого типа.
    /// Может вернуть 0, если значение не соответствует
    /// ни одному из значений, определенных в перечислении.
    const char *value = metaEnum.valueToKey(socketError);

    /// Возвращаемое значение.
    const QString errorText = (value != nullptr) ? value : "Unknown error";

    emit error(errorText);

    if(socketError == QAbstractSocket::RemoteHostClosedError){
        QMessageBox::critical(nullptr, tr("Server disconnected"), tr("Chat will be closed"));
        QApplication::quit();
    }
}

void Client::onDataReceived()
{
    qDebug() << "Data received";
    emit chatChanged(socket.readAll());
}

void Client::onDisconnected()
{
}

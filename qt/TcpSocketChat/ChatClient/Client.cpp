#include "Client.h"
#include <QMetaEnum>

Client::Client(QObject *parent)
    : QObject(parent)
{
    connect(&socket, SIGNAL(connected()),
            SIGNAL(connected()));
    connect(&socket, SIGNAL(disconnected()),
            SIGNAL(disconnected()));

    connect(&socket, &QTcpSocket::connected,
            this, &Client::onConnected);
    connect(&socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, &Client::onError);

    socket.connectToHost("localhost", 7050);
}

void Client::sendMessage(QString message)
{
    socket.write(message.toUtf8());
}

void Client::onConnected()
{
//    QTimer *const timer = new QTimer(this);
//    connect(timer, &QTimer::timeout,
//            this, &Client::timeout);
//    const int oneSecond = 1000;
//    timer->start(oneSecond);
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
}

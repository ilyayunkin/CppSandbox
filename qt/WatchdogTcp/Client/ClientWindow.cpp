#include "ClientWindow.h"
#include "ui_ClientWindow.h"

#include <QMetaEnum>

ClientWindow::ClientWindow(const QString hostName, const int port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    connect(&socket_, &QTcpSocket::connected,
            this, &ClientWindow::connected);
    connect(&socket_, &QTcpSocket::disconnected,
            this, &ClientWindow::disconnected);
    connect(&socket_, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, &ClientWindow::onError);
    connect(&socket_, &QTcpSocket::readyRead,
            this, &ClientWindow::dataReceived);

    socket_.connectToHost(hostName, port);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::onError(QAbstractSocket::SocketError socketError)
{
    const QMetaEnum metaEnum =
            QMetaEnum::fromType<
            QAbstractSocket::SocketError>();
    /// Строковое представление значения перечислимого типа.
    /// Может вернуть 0, если значение не соответствует
    /// ни одному из значений, определенных в перечислении.
    const char *value = metaEnum.valueToKey(socketError);
    qDebug() << value;

    /// Возвращаемое значение.
//    const auto ret = (socketError == QAbstractSocket::SocketError::RemoteHostClosedError)
//            ? ConnectionError::RemoteHostClosedError
//            : ConnectionError::Unknown;

//    emit error(ret);
}


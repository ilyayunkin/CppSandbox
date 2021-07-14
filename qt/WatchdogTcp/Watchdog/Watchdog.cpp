#include "Watchdog.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QProcess>

#include <cassert>

Watchdog::Watchdog(const QString filename, const int port, QObject *parent)
    : QObject(parent)
    , filename_(filename)
    , port(port)
{
    if(!server_.listen(QHostAddress::Any, port)){
        QMessageBox::critical(
                    nullptr, "Unable to open connection",
                    "Unable to open connection");
    }else{
        connect(&server_, &QTcpServer::newConnection,
                this, &Watchdog::onClientConnected_);
    }

    restartClient_();
}

Watchdog::~Watchdog()
{
    qDebug() << __PRETTY_FUNCTION__;
    if(clientSocket_)
        clientSocket_->disconnect();
}

QByteArray Watchdog::readAll()
{
    if(clientSocket_){
        return clientSocket_->readAll();
    }

    return QByteArray();
}

void Watchdog::write(const QByteArray data)
{
    if(clientSocket_){
        clientSocket_->write(data);
    }
}

void Watchdog::onClientConnected_()
{
    clientSocket_ = server_.nextPendingConnection();

    if(clientSocket_ != nullptr)
    {
        connect(clientSocket_, &QTcpSocket::disconnected,
                this, &Watchdog::onClientDisconnected_);
        connect(clientSocket_, &QTcpSocket::readyRead,
                this, &Watchdog::onDataReceived_);

        connect(clientSocket_, &QTcpSocket::disconnected,
                this, &Watchdog::disconnected);
        connect(clientSocket_, &QTcpSocket::readyRead,
                this, &Watchdog::readyRead);
        //        names_[clientSocket] = QString();

        qDebug() << "Client connected";
        emit connected();
    }
}

void Watchdog::onClientDisconnected_()
{
    QTcpSocket *const clientSocket =
            dynamic_cast<QTcpSocket *>(sender());

    assert(clientSocket == clientSocket_);

    restartClient_();

    //    const auto clientName = names_[clientSocket];
    //    chat_+= "\r\n" + clientName + " left the chat";
    //    updateChat();

    //    names_.erase(clientSocket);
    clientSocket->deleteLater();

    //    updateUserList();
}

void Watchdog::onDataReceived_()
{
    qDebug() << "Data received";
    QTcpSocket *const clientSocket =
            dynamic_cast<QTcpSocket *>(sender());

    assert(clientSocket == clientSocket_);
    //    tmpSocket_ = dynamic_cast<QTcpSocket *>(sender());

    //    assert(QString(sender()->metaObject()->className()) ==
    //           QString("QTcpSocket"));
    //    assert(tmpSocket_ != nullptr);

    //    const auto commandPtr = parser_.parse(tmpSocket_->readAll());
    //    commandPtr->accept(*this);
}

void Watchdog::restartClient_()
{
    bool started = QProcess::startDetached(filename_);
    if(started){
        qDebug() << "Client Started";
    }else{
        qDebug() << "Start failed";
    }
}


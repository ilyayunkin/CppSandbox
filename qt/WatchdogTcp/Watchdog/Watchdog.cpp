#include "Watchdog.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QProcess>

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
                this, &Watchdog::clientConnected);
    }

    restartClient_();
}

Watchdog::~Watchdog()
{
    qDebug() << __PRETTY_FUNCTION__;
    disconnect(connection_);
}

void Watchdog::clientConnected()
{
    QTcpSocket *const clientSocket =
            server_.nextPendingConnection();
    if(clientSocket != nullptr)
    {
        connection_ = connect(clientSocket, &QTcpSocket::disconnected,
                         this, &Watchdog::clientDisconnected);
        connect(clientSocket, &QTcpSocket::readyRead,
                this, &Watchdog::dataReceived);
//        names_[clientSocket] = QString();

        qDebug() << "Client connected";
    }
}

void Watchdog::clientDisconnected()
{
    qDebug() << "Client disconnected";
    QTcpSocket *const clientSocket =
            dynamic_cast<QTcpSocket *>(sender());

    restartClient_();

//    const auto clientName = names_[clientSocket];
//    chat_+= "\r\n" + clientName + " left the chat";
//    updateChat();

//    names_.erase(clientSocket);
    clientSocket->deleteLater();

//    updateUserList();
}

void Watchdog::dataReceived()
{
    qDebug() << "Data received";
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


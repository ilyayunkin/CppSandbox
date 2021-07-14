#include "WatchdogWindow.h"
#include "ui_WatchdogWindow.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QProcess>

WatchdogWindow::WatchdogWindow(int port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WatchdogWindow)
{
    ui->setupUi(this);
    if(!server_.listen(QHostAddress::Any, port)){
        QMessageBox::critical(
                    nullptr, "Unable to open connection",
                    "Unable to open connection");
    }else{
        connect(&server_, &QTcpServer::newConnection,
                this, &WatchdogWindow::clientConnected);
    }

    restartClient_();
}

WatchdogWindow::~WatchdogWindow()
{
    delete ui;
}

void WatchdogWindow::clientConnected()
{
    QTcpSocket *const clientSocket =
            server_.nextPendingConnection();
    if(clientSocket != nullptr)
    {
        QObject::connect(clientSocket, &QTcpSocket::disconnected,
                         this, &WatchdogWindow::clientDisconnected);
        connect(clientSocket, &QTcpSocket::readyRead,
                this, &WatchdogWindow::dataReceived);
//        names_[clientSocket] = QString();

        qDebug() << "Client connected";
    }
}

void WatchdogWindow::clientDisconnected()
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

void WatchdogWindow::dataReceived()
{
    qDebug() << "Data received";
//    tmpSocket_ = dynamic_cast<QTcpSocket *>(sender());

//    assert(QString(sender()->metaObject()->className()) ==
//           QString("QTcpSocket"));
//    assert(tmpSocket_ != nullptr);

//    const auto commandPtr = parser_.parse(tmpSocket_->readAll());
    //    commandPtr->accept(*this);
}

void WatchdogWindow::restartClient_()
{
    bool started = QProcess::startDetached("Client.exe");
    if(started){
        qDebug() << "Client Started";
    }else{
        qDebug() << "Start failed";
    }
}


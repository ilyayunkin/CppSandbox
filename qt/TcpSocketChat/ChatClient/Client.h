#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "AbstractServerCommandVisitor.h"
#include "ClientParser.h"

#include <QTcpSocket>

class Client : public QObject, public AbstractServerCommandVisitor
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    // AbstractServerCommandVisitor interface
public:
    void visit(ServerCommandUserList &command);
    void visit(ServerCommandChat &command);

public slots:
    void sendMessage(QString message);
signals:
    void connected();
    void error(QString);
    void chatChanged(QString);
    void userListChanged(QStringList);

private:
    QTcpSocket socket;
    ClientParser parser;
    void onConnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onDataReceived();
    void onDisconnected();
};

#endif // CLIENT_H

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "AbstractClientCommandVisitor.h"
#include "ServerParser.h"

#include <QTcpServer>
#include <QList>
#include <unordered_map>

class Server : public QObject, public AbstractClientCommandVisitor
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void chatChanged(QString chat);
private:
    QTcpServer server;
    QString chat_;
    QList<QTcpSocket*> sockets_;
    std::unordered_map<QTcpSocket*, QString> names_;
    ServerParser parser_;
    QTcpSocket*tmpSocket_ = nullptr;

    void clientConnected();
    void clientDisconnected();
    void dataReceived();
    void updateChat();

    // AbstractClientCommandVisitor interface
public:
    void visit(ClientCommandName &command);
    void visit(ClientCommandText &command);
};

#endif // SERVER_H

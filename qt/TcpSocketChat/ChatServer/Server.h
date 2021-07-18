#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "AbstractClientCommandVisitor.h"
#include "ServerParser.h"

#include <QTcpServer>
#include <QList>
#include <unordered_map>

class Server final : public QObject, public AbstractClientCommandVisitor
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void chatChanged(QString chat);
private:
    QTcpServer server;
    QString chat_;
    std::unordered_map<QTcpSocket*, QString> names_;
    ServerParser parser_;
    QTcpSocket*tmpSocket_ = nullptr;

    void clientConnected();
    void clientDisconnected(QTcpSocket *const clientSocket);
    void dataReceived(QTcpSocket *const clientSocket);
    void updateChat();
    void updateUserList();

    // AbstractClientCommandVisitor interface
public:
    void visit(const ClientCommandName &command) override;
    void visit(const ClientCommandText &command) override;
};

#endif // SERVER_H

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include <unordered_map>
class Server : public QObject
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

    void clientConnected();
    void clientDisconnected();
    void dataReceived();
    void updateChat();
};

#endif // SERVER_H

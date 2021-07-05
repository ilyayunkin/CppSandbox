#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

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
    void clientConnected();
    void dataReceived();
};

#endif // SERVER_H

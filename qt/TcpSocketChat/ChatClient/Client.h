#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void sendMessage(QString message);
signals:
    void connected();
    void error(QString);
    void chatChanged(QString);

private:
    QTcpSocket socket;
    void onConnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onDataReceived(void);
};

#endif // CLIENT_H

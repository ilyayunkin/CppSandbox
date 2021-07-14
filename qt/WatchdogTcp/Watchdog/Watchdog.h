#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QTcpServer>

class QTcpSocket;
class Watchdog : public QObject
{
    Q_OBJECT
public:
    Watchdog(const QString filename, const int port, QObject *parent = nullptr);
    ~Watchdog();

    QByteArray readAll();
    void write(const QByteArray data);

private:
    const QString filename_;
    const int port;
    QTcpServer server_;
    QTcpSocket *clientSocket_ = nullptr;

signals:
    void connected();
    void disconnected();
    void readyRead();

private slots:
    void onClientConnected_();
    void onClientDisconnected_();
    void onDataReceived_();
    void restartClient_();
};

#endif // WATCHDOG_H

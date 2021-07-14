#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QTcpServer>

class Watchdog : public QObject
{
public:
    Watchdog(const QString filename, const int port, QObject *parent = nullptr);

private:
    const QString filename_;
    const int port;
    QTcpServer server_;
    void clientConnected();
    void clientDisconnected();
    void dataReceived();
    void restartClient_();
};

#endif // WATCHDOG_H

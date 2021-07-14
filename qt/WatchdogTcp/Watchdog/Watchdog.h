#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QTcpServer>

class Watchdog : public QObject
{
public:
    Watchdog(const QString filename, const int port, QObject *parent = nullptr);
    ~Watchdog();

private:
    const QString filename_;
    const int port;
    QTcpServer server_;
    QMetaObject::Connection connection_;

private slots:
    void clientConnected();
    void clientDisconnected();
    void dataReceived();
    void restartClient_();
};

#endif // WATCHDOG_H

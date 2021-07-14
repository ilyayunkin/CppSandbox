#ifndef WATCHDOGWINDOW_H
#define WATCHDOGWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class WatchdogWindow; }
QT_END_NAMESPACE

class WatchdogWindow : public QMainWindow
{
    Q_OBJECT

public:
    WatchdogWindow(int port = 7050, QWidget *parent = nullptr);
    ~WatchdogWindow();

private:
    Ui::WatchdogWindow *ui;
    QTcpServer server_;
    void clientConnected();
    void clientDisconnected();
    void dataReceived();
    void restartClient_();
};
#endif // WATCHDOGWINDOW_H

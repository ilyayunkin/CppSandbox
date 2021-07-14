#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(const QString hostName = "localhost", const int port = 7050, QWidget *parent = nullptr);
    ~ClientWindow();
signals:
    void connected();
    void disconnected();
    void dataReceived();

private:
    Ui::ClientWindow *ui;
    QTcpSocket socket_;
    void onError(QAbstractSocket::SocketError socketError);
};
#endif // CLIENTWINDOW_H

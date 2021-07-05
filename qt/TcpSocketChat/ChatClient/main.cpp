#include "mainwindow.h"

#include <QApplication>
#include "Client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Client client;
    QObject::connect(&w, &MainWindow::newMessage,
                     &client, &Client::sendMessage);

    return a.exec();
}
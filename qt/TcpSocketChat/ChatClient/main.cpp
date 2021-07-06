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
    QObject::connect(&client, &Client::chatChanged,
                     &w, &MainWindow::setChat);
    QObject::connect(&client, &Client::userListChanged,
                     &w, &MainWindow::setUserList);

    return a.exec();
}

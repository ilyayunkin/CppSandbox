#include "mainwindow.h"

#include <QApplication>
#include "Server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Server s;
    QObject::connect(&s, &Server::chatChanged, &w, &MainWindow::setChat);

    return a.exec();
}

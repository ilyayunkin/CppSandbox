#include "mainwindow.h"

#include <QApplication>
#include "Counter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Counter counter;
    QObject::connect(&counter, &Counter::newValue, &w, &MainWindow::setValue);
    counter.start();

    auto ret = a.exec();

    counter.stop();
    counter.wait();

    return ret;
}

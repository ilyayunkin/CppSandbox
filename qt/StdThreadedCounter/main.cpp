#include "mainwindow.h"

#include <QApplication>
#include <thread>
#include "Counter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Counter counter;
    QObject::connect(&counter, &Counter::newValue, &w, &MainWindow::setValue);
    std::thread thread([&](){counter.run();});

    auto ret = a.exec();

    counter.stop();
    thread.join();

    return ret;
}

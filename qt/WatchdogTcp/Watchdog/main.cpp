#include "WatchdogWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WatchdogWindow w;
    w.show();
    return a.exec();
}

#include "WatchdogWindow.h"
#include "ui_WatchdogWindow.h"

WatchdogWindow::WatchdogWindow(int port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WatchdogWindow)
    , watchdog_("Client.exe", port)
{
    ui->setupUi(this);
    connect(&watchdog_, &Watchdog::readyRead, this,
            [this]{ui->textBrowser->setText(watchdog_.readAll());});
}

WatchdogWindow::~WatchdogWindow()
{
    delete ui;
}

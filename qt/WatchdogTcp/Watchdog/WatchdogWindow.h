#ifndef WATCHDOGWINDOW_H
#define WATCHDOGWINDOW_H

#include <QMainWindow>
#include <Watchdog.h>

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
    Watchdog watchdog_;
};
#endif // WATCHDOGWINDOW_H

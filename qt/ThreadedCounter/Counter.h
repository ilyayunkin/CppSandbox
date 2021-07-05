#ifndef COUNTER_H
#define COUNTER_H

#include <QThread>

class Counter : public QThread
{
    Q_OBJECT
public:
    Counter();

public slots:
    void stop();
signals:
    void newValue(int i);

    // QThread interface
protected:
    void run();
private:
    int i = 0;
    bool stop_ = false;
};

#endif // COUNTER_H

#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
public:
    Counter();

public slots:
    void run();
    void stop();
signals:
    void newValue(int i);
private:
    int i = 0;
    bool stop_ = false;
};

#endif // COUNTER_H

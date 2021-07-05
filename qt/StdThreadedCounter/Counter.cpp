#include "Counter.h"
#include <QThread>
Counter::Counter()
{

}

void Counter::run()
{
    while(!stop_){
        i++;
        emit newValue(i);
        QThread::msleep(500);
    }
}

void Counter::stop()
{
    stop_ = true;
}

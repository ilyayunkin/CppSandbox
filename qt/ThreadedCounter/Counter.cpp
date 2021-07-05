#include "Counter.h"

Counter::Counter()
{

}

void Counter::run()
{
    while(!stop_){
        i++;
        emit newValue(i);
        msleep(500);
    }
}

void Counter::stop()
{
    stop_ = true;
}

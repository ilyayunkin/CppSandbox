#include "data.h"
#include <QTimer>
#include <QDebug>
Data::Data(QObject *parent)
    : QObject(parent)
{
    QTimer *t = new QTimer(this);
    t->start(1000);
    connect(t, &QTimer::timeout, this, &Data::timeout_);
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << number();
}

void Data::timeout_()
{
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << number();
    ++number_;
    emit numberChanged();
}

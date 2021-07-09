#ifndef DATA_H
#define DATA_H

#include <QObject>

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)

public:
    explicit Data(QObject *parent = nullptr);
    int number(){return number_;}
    void setNumber(int value){number_ = value;}

signals:
    void numberChanged();

private:
    int number_ = 0;
    void timeout_();
};

#endif // DATA_H

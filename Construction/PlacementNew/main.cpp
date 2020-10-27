#include <QCoreApplication>
#include <QDebug>

class A
{
public:
    int i;
    A(int i) : i(i)
    {
        qDebug() <<__PRETTY_FUNCTION__ << __LINE__ << i;
    }
    ~A()
    {
        qDebug() <<__PRETTY_FUNCTION__ << __LINE__;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char b[sizeof (A)];
    auto aPtr = new(b) A(5);

    qDebug() << aPtr->i;
    aPtr->~A();

    return a.exec();
}

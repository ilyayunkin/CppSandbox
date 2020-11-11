#include <QCoreApplication>
#include <QDebug>
#include <tuple>

struct A
{
    static int i;
    A(){
        ++i;
        qDebug() << __PRETTY_FUNCTION__;
    }
    A(const A &other){
        ++i;
        qDebug() << __PRETTY_FUNCTION__;
    }
    A(const A &&other){
        ++i;
        qDebug() << __PRETTY_FUNCTION__;
    }
    void operator=(const A &other){
        ++i;
        qDebug() << __PRETTY_FUNCTION__;
    }
    void operator=(const A &&other){
        ++i;
        qDebug() << __PRETTY_FUNCTION__;
    }
};
int A::i = 0;

typedef std::tuple<QString, A> stringA;

stringA f()
{
    qDebug() << __PRETTY_FUNCTION__;
    A a;
    return std::make_tuple(QString::number(A::i), a);
}
stringA g()
{
    qDebug() << __PRETTY_FUNCTION__;
    return std::make_tuple(QString::number(A::i), A());
}
A h()
{
    qDebug() << __PRETTY_FUNCTION__;
    return A();
}
A e()
{
    qDebug() << __PRETTY_FUNCTION__;
    A a;
    return a;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        // A very redundant case - receiver objects are to be constructed by default,
        // then mpve-assigned from the return value
        QString istr;
        A a1;
        std::tie(istr, a1) = f();
        qDebug() << A::i << "special function calls"
                 << "\nreturn value:" << istr << "\n";
    }
    A::i = 0;
    {// One construction - copy ellision works.
        A a1 = h();
        qDebug() << A::i << "special function calls" << "\n";
    }
    A::i = 0;
    {// One construction - copy ellision works.
        A a1 = e();
        qDebug() << A::i << "special function calls" << "\n";
    }
    A::i = 0;
    {//C++17
     // Not such a bad case - 2 r in the function
     // First - the object itself, second - it's copy into the tuple.
     // Receiver is just a group of references
        auto [istr, a1] = f();
        qDebug() << A::i << "special function calls"
                << "\nreturn value:" << istr << "\n";
    }
    A::i = 0;
    {//Similar, but the second Constructor is Move Constructor that can be cheaper.
        auto [istr, a1] = g();
        qDebug() << A::i << "special function calls"
                    << "\nreturn value:" << istr << "\n";
    }
    return a.exec();
}

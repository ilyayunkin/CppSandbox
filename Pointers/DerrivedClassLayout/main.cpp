#include <QCoreApplication>
#include <QDebug>

class BaseSimple1
{
public:
    int i;
};
class BaseSimple2
{
public:
    char c;
};
class DerrivedSimple : public BaseSimple1, public BaseSimple2
{
};


class BaseVirtual1
{
public:
    int i;
    virtual ~BaseVirtual1() = default;
};

class DerrivedVirtual : public BaseSimple1, public BaseSimple2
{
public:
    int d;
    virtual void f() {}
};

class DerrivedMultipleVirtual : public BaseSimple1, public BaseSimple2, public BaseVirtual1
{
public:
    int f;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    {
        auto *ds = new DerrivedSimple;
        auto *bs1 = static_cast<BaseSimple1 *>(ds);
        auto *bs2 = static_cast<BaseSimple2 *>(ds);
        // Derrived class pointer points the first base class entity
        qDebug() << ds
                 << bs1
                 << bs2;
        // When we compare those pointers, the comparison operator returns true
        // because it adds offset while pointers' cast
        qDebug() << (ds == bs1)
                 << (ds == bs2);

        // But if we cast those pointers to (void *),
        // we will be able to compare raw pointers' values
        qDebug() << (static_cast<void *>(ds) == static_cast<void *>(bs1))
                 << (static_cast<void *>(ds) == static_cast<void *>(bs2));
    }
    {
        auto *ds = new DerrivedVirtual;
        auto *bs1 = static_cast<BaseSimple1 *>(ds);
        auto *bs2 = static_cast<BaseSimple2 *>(ds);
        // If a class that derrives a non-virtual class, is virtual
        // it contains a virtual table first,
        // than instances of base classes.
        qDebug() << ds
                 << bs1
                 << bs2;
        // When we compare those pointers, the comparison operator returns true
        // because it adds offset while pointers' cast
        qDebug() << (ds == bs1)
                 << (ds == bs2);

        // But if we cast those pointers to (void *),
        // we will be able to compare raw pointers' values
        qDebug() << (static_cast<void *>(ds) == static_cast<void *>(bs1))
                 << (static_cast<void *>(ds) == static_cast<void *>(bs2));
    }
    {
        auto *ds = new DerrivedMultipleVirtual;
        auto *bs1 = static_cast<BaseSimple1 *>(ds);
        auto *bs2 = static_cast<BaseSimple2 *>(ds);
        auto *bv1 = static_cast<BaseVirtual1 *>(ds);
        // Derrived class pointer points the first VIRTUAL base class entity
        qDebug() << ds
                 << bs1
                 << bs2
                 << bv1;
        // When we compare those pointers, the comparison operator returns true
        // because it adds offset while pointers' cast
        qDebug() << (ds == bs1)
                 << (ds == bs2)
                 << (ds == bv1);

        // But if we cast those pointers to (void *),
        // we will be able to compare raw pointers' values
        qDebug() << (static_cast<void *>(ds) == static_cast<void *>(bs1))
                 << (static_cast<void *>(ds) == static_cast<void *>(bs2))
                 << (static_cast<void *>(ds) == static_cast<void *>(bv1));
    }

    return a.exec();
}

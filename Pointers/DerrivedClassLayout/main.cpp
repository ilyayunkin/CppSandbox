#include <QCoreApplication>
#include <QDebug>

#include <type_traits>

class BaseSimple1
{
public:
    int i;
};
static_assert (std::is_standard_layout<BaseSimple1>::value, "Must be Standard layout");

class BaseSimple2
{
public:
    char c;
};
static_assert (std::is_standard_layout<BaseSimple2>::value, "Must be Standard layout");

class DerrivedSimple1 : public BaseSimple1
{// NO additional non-static data
};
static_assert (std::is_standard_layout<DerrivedSimple1>::value, "Must be Standard layout");

class DerrivedSimple2 : public BaseSimple1
{// additional non-static data
public:
    char c;
};
static_assert (!std::is_standard_layout<DerrivedSimple2>::value, "Must be NOT standard layout");

class DerrivedSimple : public BaseSimple1, public BaseSimple2
{
};
static_assert (!std::is_standard_layout<DerrivedSimple>::value, "Must be NOT standard layout");

class BaseVirtual1
{
public:
    int i;
    virtual ~BaseVirtual1() = default;
};
static_assert (!std::is_standard_layout<BaseVirtual1>::value, "Must be NOT standard layout");

class DerrivedVirtual : public BaseSimple1, public BaseSimple2
{
public:
    int d;
    virtual void f() {}
};
static_assert (!std::is_standard_layout<DerrivedVirtual>::value, "Must be NOT standard layout");

class DerrivedMultipleVirtual : public BaseSimple1, public BaseSimple2, public BaseVirtual1
{
public:
    int f;
};
static_assert (!std::is_standard_layout<DerrivedMultipleVirtual>::value, "Must be NOT standard layout");

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

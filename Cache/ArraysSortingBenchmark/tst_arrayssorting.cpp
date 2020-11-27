#include <QtTest>
#include <array>
#include <random>
#include <vector>
#include <algorithm>
// add necessary includes here
using namespace std;
class ArraysSorting : public QObject
{
    Q_OBJECT

public:
    ArraysSorting();
    ~ArraysSorting();

private slots:
    void benchmark8();
    void benchmark32();
    void benchmark64();
    void benchmark65();
    void benchmark127();
    void benchmark128();
};

ArraysSorting::ArraysSorting()
{

}

ArraysSorting::~ArraysSorting()
{

}
template<int len>
void bench()
{
    constexpr auto count = 8192;
    typedef std::array<char, len> arr;
    vector<arr> v;
    v.reserve(count);
    for(int i = 0; i < count; ++i){
        arr a;
        memcpy(a.data(), QString::number(rand() % count).toLatin1().data(), len);
        v.push_back(a);
    }
    QBENCHMARK{
        sort(v.begin(), v.end());
    }
}
void ArraysSorting::benchmark8()
{
    bench<8>();
}
void ArraysSorting::benchmark32()
{
    bench<32>();
}
void ArraysSorting::benchmark64()
{
    bench<64>();
}
void ArraysSorting::benchmark65()
{
    bench<65>();
}
void ArraysSorting::benchmark127()
{
    bench<127>();
}
void ArraysSorting::benchmark128()
{
    bench<128>();
}


QTEST_APPLESS_MAIN(ArraysSorting)

#include "tst_arrayssorting.moc"

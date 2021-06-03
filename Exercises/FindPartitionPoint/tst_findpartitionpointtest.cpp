#include <QtTest>
#include <algorithm>
#include <stdexcept>
// Диапазон всегда начинается с 0, заканчивается 1.
// Элементы монотонно возрастают
// Найти первое вхождение 1.

class FindPartitionPointTest : public QObject
{
    Q_OBJECT

public:
    FindPartitionPointTest();
    ~FindPartitionPointTest();

private slots:
    void test_case1_data();
    void test_case1();

};

FindPartitionPointTest::FindPartitionPointTest()
{

}

FindPartitionPointTest::~FindPartitionPointTest()
{

}

void FindPartitionPointTest::test_case1_data()
{
    QTest::addColumn<QVector<int>>("in");

    QTest::newRow("1") << QVector<int>{0,1};
    QTest::newRow("2") << QVector<int>{0,1,1,1};
    QTest::newRow("3") << QVector<int>{0,1,1,1,1};
    QTest::newRow("4") << QVector<int>{0,0,0, 1};
    QTest::newRow("5") << QVector<int>{0,0,0,0, 1};
    QTest::newRow("6") << QVector<int>{0,0,0,0, 1,1,1};
    QTest::newRow("7") << QVector<int>{0,0,0,0, 1,1,1,1};
    QTest::newRow("8") << QVector<int>{0,0,0, 1,1,1};
    QTest::newRow("9") << QVector<int>{0,0,0, 1,1,1,1};
}
#define ASS(a) if(!(a)){throw std::runtime_error(#a);}

int findPartitionPoint(const QVector<int> &in)
{
    const int targetValue = 1;
    auto size = in.size();
    auto lastIndex = size - 1;
    ASS(size >= 2);
    ASS(in.at(0) == 0);
    ASS(in.at(lastIndex) == targetValue);

    if(size == 2)
        return 1;

    auto begin = in.begin();
    auto end = in.end();
    auto it = begin + (end - begin) / 2;

    while(!((*it == targetValue) && (*(it - 1) != targetValue))){
        ASS(it > begin);
        ASS(it < end);
        if(*it != targetValue){
            begin = it + 1;
            it = begin + (end - begin) / 2;
        }else{
            end = it;
            it = begin + (end - begin) / 2;
        }
    }

    return std::distance(in.begin(), it);
}

void FindPartitionPointTest::test_case1()
{
    QFETCH(QVector<int>, in);

    try {
        int i = findPartitionPoint(in);
        int i1 = std::distance(in.begin(), std::lower_bound(in.begin(), in.end(), 1));
        QCOMPARE(i, i1);
    } catch (std::exception &e) {
        qDebug() << e.what();
        QVERIFY(0);
    }catch(...){
        QVERIFY(0);
    }
}

QTEST_APPLESS_MAIN(FindPartitionPointTest)

#include "tst_findpartitionpointtest.moc"

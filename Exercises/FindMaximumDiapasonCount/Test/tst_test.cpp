#include <QtTest>
#include <QSet>
// add necessary includes here

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void test_range_data();
    void test_range();
    void test_unite_data();
    void test_unite();
    void test_process_data();
    void test_process();

};

Test::Test() = default;
Test::~Test() = default;

struct Range{
    int begin;
    int end;
};
bool operator== (const Range &lhs, const Range &rhs){
    return lhs.begin == rhs.begin && lhs.end == rhs.end;
}
bool operator< (const Range &lhs, const Range &rhs){
    return lhs.begin < rhs.begin;
}

Q_DECLARE_METATYPE(Range);

QVector<Range> range(const QString in)
{
    QVector<Range> out;
    QSet<QChar> charset;
    for(auto c : in){
        charset.insert(c);
    }
    for(auto c : charset){
        out.push_back({in.indexOf(c), in.lastIndexOf(c)});
    }
    std::sort(out.begin(), out.end());
    return out;
}

QVector<Range> unite(const QVector<Range> in)
{
    QVector<Range> out = in;

    if(in.empty())
        return out;

    auto it = out.begin();
    while(it!= out.end() && it + 1 != out.end()){
        auto it2 = it + 1;
        if((it->begin < it2->begin) && (it2->begin < it->end)){
            it->end = std::max(it->end, it2->end);
            out.erase(it2);
        }else{
            ++it;
        }
    }

    return out;
}

QVector<int> process(const QString in)
{
    QVector<int> out;
    auto u = unite(range(in));
    std::transform(u.begin(), u.end(), std::back_inserter(out), [](Range r){return r.end - r.begin + 1;});

    return out;
}

void Test::test_range_data()
{
    QTest::addColumn<QString>("in");
    QTest::addColumn<QVector<Range>>("out");

    QTest::newRow("1") << QString("aaabbbab")
                       << QVector<Range>{{0, 6}, {3,7}};
    QTest::newRow("2") << QString("acbad")
                       << QVector<Range>{{0, 3}, {1, 1}, {2, 2}, {4, 4}};
}

void Test::test_range()
{
    QFETCH(QString, in);
    QFETCH(QVector<Range>, out);
    QCOMPARE(out, range(in));
}

void Test::test_unite_data()
{
    QTest::addColumn<QVector<Range>>("in");
    QTest::addColumn<QVector<Range>>("out");

    QTest::newRow("1") << QVector<Range>{{0, 6}, {3, 7}}
                       << QVector<Range>{{0, 7}};
    QTest::newRow("2") << QVector<Range>{{0, 3}, {1, 1}, {2, 2}, {4, 4}}
                       << QVector<Range>{{0, 3}, {4, 4}};
}

void Test::test_unite()
{
    QFETCH(QVector<Range>, in);
    QFETCH(QVector<Range>, out);
    QCOMPARE(out, unite(in));
}

void Test::test_process_data()
{
    QTest::addColumn<QString>("in");
    QTest::addColumn<QVector<int>>("out");

    QTest::newRow("1") << QString("aaabbbab")
                       << QVector<int>{8};
    QTest::newRow("2") << QString("acbad")
                       << QVector<int>{4,1};
    QTest::newRow("3") << QString("ababcbacadefegdehijhklij")
                       << QVector<int>{9,7, 8};
}

void Test::test_process()
{
    QFETCH(QString, in);
    QFETCH(QVector<int>, out);
    QCOMPARE(out, process(in));
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"

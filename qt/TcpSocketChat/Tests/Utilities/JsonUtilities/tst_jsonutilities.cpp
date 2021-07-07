#include <QtTest>

#include "Utilities/JsonUtilities.h"

namespace  {
auto getJsonList()
{
    return QByteArrayList()
            << R"({
               "firstName": "Иван",
               "lastName": "Иванов",
               "address": {
                   "streetAddress": "Московское ш., 101, кв.101",
                   "city": "Ленинград",
                   "postalCode": 101101
               },
               "phoneNumbers": [
                   "812 123-1234",
                   "916 123-4567"
               ]
            })"
            << R"({
               "firstName": "John",
               "lastName": "Smith",
               "isAlive": true,
               "age": 27,
               "address": {
                 "streetAddress": "21 2nd Street",
                 "city": "New York",
                 "state": "NY",
                 "postalCode": "10021-3100"
               },
               "phoneNumbers": [
                 {
                   "type": "home",
                   "number": "212 555-1234"
                 },
                 {
                   "type": "office",
                   "number": "646 555-4567"
                 }
               ],
               "children": [],
               "spouse": null
             })";
}
}
class JsonUtilitiesTest : public QObject
{
    Q_OBJECT

public:
    JsonUtilitiesTest();
    ~JsonUtilitiesTest();

private slots:
    void splitting();

};

JsonUtilitiesTest::JsonUtilitiesTest()
{

}

JsonUtilitiesTest::~JsonUtilitiesTest()
{

}

void JsonUtilitiesTest::splitting()
{
    const auto list = getJsonList();
    const auto frame = list.join();
    const auto fragments = QByteArrayList()
            << list.mid(0, 5)
            << list.mid(5);

    QByteArrayList outList;

    JsonUtilities::JsonDefragmentator jsonDefragmentator;
    for(const auto &fragment : fragments){
        outList+= jsonDefragmentator.process(fragment);
    }

    QCOMPARE(outList, list);
}

QTEST_APPLESS_MAIN(JsonUtilitiesTest)

#include "tst_jsonutilities.moc"

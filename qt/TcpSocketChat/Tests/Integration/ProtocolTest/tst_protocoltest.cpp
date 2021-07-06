#include <QtTest>
#include "ChatClient/ClientQuery.h"
#include "ChatServer/ServerParser.h"
#include "ChatServer/AbstractClientCommand.h"
#include "ChatServer/AbstractClientCommandVisitor.h"
#include "ChatServer/ClientCommandName.h"
#include "ChatServer/ClientCommandText.h"

struct FakeServer final : public AbstractClientCommandVisitor
{
    QString name;
    QString text;
    void visit(ClientCommandName &c){
        name = c.name;
    }
    void visit(ClientCommandText &c){
        text = c.text;
    }
};

class ProtocolTest : public QObject
{
    Q_OBJECT
public:
    ProtocolTest();
    ~ProtocolTest();

private slots:
    void setsName();
    void setsText();
};

ProtocolTest::ProtocolTest()
{

}

ProtocolTest::~ProtocolTest()
{

}

void ProtocolTest::setsName()
{
    const QString name("My name");
    QByteArray frame = ClientQuery::sendName(name);
    QVERIFY(!frame.isEmpty());

    ServerParser parser;
    ClientCommandPtr commandPtr = parser.parse(frame);
    QVERIFY(commandPtr);
    FakeServer fakeServer;
    commandPtr->accept(fakeServer);

    QCOMPARE(name, fakeServer.name);
}

void ProtocolTest::setsText()
{
    const QString text("Some text");
    QByteArray frame = ClientQuery::sendText(text);
    QVERIFY(!frame.isEmpty());

    ServerParser parser;
    ClientCommandPtr commandPtr = parser.parse(frame);
    QVERIFY(commandPtr);
    FakeServer fakeServer;
    commandPtr->accept(fakeServer);

    QCOMPARE(text, fakeServer.text);
}

QTEST_APPLESS_MAIN(ProtocolTest)

#include "tst_protocoltest.moc"

#include <QtTest>
#include "ChatClient/ClientQuery.h"
#include "ChatClient/ClientParser.h"
#include "ChatClient/AbstractServerCommandVisitor.h"
#include "ChatClient/ServerCommandUserList.h"
#include "ChatClient/ServerCommandChat.h"

#include "ChatServer/ServerParser.h"
#include "ChatServer/AbstractClientCommand.h"
#include "ChatServer/AbstractClientCommandVisitor.h"
#include "ChatServer/ClientCommandName.h"
#include "ChatServer/ClientCommandText.h"
#include "ChatServer/ServerQuery.h"

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

struct FakeClient final : public AbstractServerCommandVisitor
{
    QStringList userList;
    QString chat;
    void visit(ServerCommandUserList &command){
        userList = command.userList;
    }
    void visit(ServerCommandChat &command){
        chat = command.chat;
    }
};

class ProtocolTest : public QObject
{
    Q_OBJECT
public:
    ProtocolTest();
    ~ProtocolTest();

private slots:
    void clientSetsName();
    void clientSetsText();
    void serverSetsUserList();
    void serverSetsChat();
    void serverSetsChatAndUserList();
};

ProtocolTest::ProtocolTest()
{
}

ProtocolTest::~ProtocolTest()
{
}

void ProtocolTest::clientSetsName()
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

void ProtocolTest::clientSetsText()
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

void ProtocolTest::serverSetsUserList()
{
    const QStringList userList = QStringList()
            << "User1"
            << "User2"
               ;
    const QByteArray frame = ServerQuery::sendUserList(userList);
    QVERIFY(!frame.isEmpty());

    ClientParser clientParser;
    FakeClient fakeClient;

    for(const auto &commandPtr : clientParser.parse(frame)){
        QVERIFY(commandPtr);
        commandPtr->accept(fakeClient);
    }

    QCOMPARE(fakeClient.userList, userList);
}

void ProtocolTest::serverSetsChat()
{
    const QString chat = "some text";
    const QByteArray frame = ServerQuery::sendChat(chat);
    QVERIFY(!frame.isEmpty());

    ClientParser clientParser;
    FakeClient fakeClient;

    for(const auto &commandPtr : clientParser.parse(frame)){
        QVERIFY(commandPtr);
        commandPtr->accept(fakeClient);
    }

    QCOMPARE(fakeClient.chat, chat);
}

void ProtocolTest::serverSetsChatAndUserList()
{
    const QString chat = "some text";
    const QStringList userList = QStringList()
            << "User1"
            << "User2"
               ;
    const QByteArray frame = ServerQuery::sendChat(chat)
            + ServerQuery::sendUserList(userList);
    QVERIFY(!frame.isEmpty());

    FakeClient fakeClient;
    ClientParser clientParser;

    for(const auto &commandPtr : clientParser.parse(frame)){
        QVERIFY(commandPtr);
        commandPtr->accept(fakeClient);
    }

    QCOMPARE(fakeClient.chat, chat);
    QCOMPARE(fakeClient.userList, userList);
}

QTEST_APPLESS_MAIN(ProtocolTest)

#include "tst_protocoltest.moc"

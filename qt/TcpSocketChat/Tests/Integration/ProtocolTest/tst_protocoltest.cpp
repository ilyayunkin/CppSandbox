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
    void visit(const ClientCommandName &c){
        name = c.name;
    }
    void visit(const ClientCommandText &c){
        text = c.text;
    }
};

struct FakeClient final : public AbstractServerCommandVisitor
{
    QStringList userList;
    QString chat;
    void visit(const ServerCommandUserList &command){
        userList = command.userList;
    }
    void visit(const ServerCommandChat &command){
        chat = command.chat;
    }
};

struct ServerSendingScenario
{
    FakeClient fakeClient;
    ServerSendingScenario(QByteArray frame)
    {
        QVERIFY(!frame.isEmpty());
        ClientParser clientParser;
        for(const auto &commandPtr : clientParser.parse(frame)){
            if(commandPtr)
                commandPtr->accept(fakeClient);
        }
    }
};

struct ClientSendingScenario
{
    FakeServer fakeServer;
    ClientSendingScenario(QByteArray frame)
    {
        QVERIFY(!frame.isEmpty());
        ServerParser parser;
        const ClientCommandPtr commandPtr = parser.parse(frame);
        QVERIFY(commandPtr);
        commandPtr->accept(fakeServer);
    }
};

class ProtocolTest : public QObject
{
    Q_OBJECT
public:
    ProtocolTest();
    ~ProtocolTest();

private slots:
    void clientSetsName_data();
    void clientSetsName();
    void clientSetsText_data();
    void clientSetsText();
    void serverSetsUserList_data();
    void serverSetsUserList();
    void serverSetsChat_data();
    void serverSetsChat();
    void serverSetsChatAndUserList();
    void fragmentallyDeliveredFrames_AreParsed_ByClient();
};

ProtocolTest::ProtocolTest()
{
}

ProtocolTest::~ProtocolTest()
{
}

void ProtocolTest::clientSetsName_data()
{
    QTest::addColumn<QString>("name");

    QTest::newRow("Text") << "My name";
    QTest::newRow("Quote mark") << "\"";
    QTest::newRow("Text with colons") << "; к; 2; ;Потребитель1;ЖК ккк п.102, дом 88, кв 3;кв.1;Место1;;Modem1;Modem-type2; ; ;";
}

void ProtocolTest::clientSetsName()
{
    QFETCH(QString, name);
    const QByteArray frame = ClientQuery::sendName(name);

    const ClientSendingScenario scenario(frame);

    QCOMPARE(name, scenario.fakeServer.name);
}

void ProtocolTest::clientSetsText_data()
{
    QTest::addColumn<QString>("text");

    QTest::newRow("Text") << "Some text";
    QTest::newRow("Quote mark") << "\"";
    QTest::newRow("Text with colons") << "; к; 2; ;Потребитель1;ЖК ккк п.102, дом 88, кв 3;кв.1;Место1;;Modem1;Modem-type2; ; ;";
}

void ProtocolTest::clientSetsText()
{
    QFETCH(QString, text);
    const QByteArray frame = ClientQuery::sendText(text);

    const ClientSendingScenario scenario(frame);

    QCOMPARE(text, scenario.fakeServer.text);
}

void ProtocolTest::serverSetsUserList_data()
{
    QTest::addColumn<QStringList>("userList");

    QTest::newRow("Text") << (QStringList()
                          << "User1"
                          << "User2")
                             ;
    QTest::newRow("Quote mark") << (QStringList()
                                << "User1"
                                << "\"")
                                   ;
    QTest::newRow("Text with colons") << (QStringList()
                                      << "User1"
                                      << ";;;;;;")
                                         ;
}

void ProtocolTest::serverSetsUserList()
{
    QFETCH(QStringList, userList);
    const QByteArray frame = ServerQuery::sendUserList(userList);

    const ServerSendingScenario scenario(frame);

    QCOMPARE(scenario.fakeClient.userList, userList);
}

void ProtocolTest::serverSetsChat_data()
{
    QTest::addColumn<QString>("chat");

    QTest::newRow("Text") << "Some text";
    QTest::newRow("Quote mark") << "\"";
    QTest::newRow("Text with colons") << "; к; 2; ;Потребитель1;ЖК ккк п.102, дом 88, кв 3;кв.1;Место1;;Modem1;Modem-type2; ; ;";
}

void ProtocolTest::serverSetsChat()
{
    QFETCH(QString, chat);
    const QByteArray frame = ServerQuery::sendChat(chat);

    const ServerSendingScenario scenario(frame);

    QCOMPARE(scenario.fakeClient.chat, chat);
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

    const ServerSendingScenario scenario(frame);

    QCOMPARE(scenario.fakeClient.chat, chat);
    QCOMPARE(scenario.fakeClient.userList, userList);
}

void ProtocolTest::fragmentallyDeliveredFrames_AreParsed_ByClient()
{
    const QString chat = "some text";
    const QStringList userList = QStringList()
            << "User1"
            << "User2"
               ;
    const QByteArray frame = ServerQuery::sendChat(chat)
            + ServerQuery::sendUserList(userList);
    FakeClient fakeClient;
    {
        QVERIFY(!frame.isEmpty());
        ClientParser clientParser;
        auto const frameLen = frame.length();
        const QByteArrayList fragments = QByteArrayList()
                << frame.mid(0, frameLen - 5)
                << frame.mid(frameLen - 5);

        for(const auto fragment : fragments){
            for(const auto &commandPtr : clientParser.parse(fragment)){
                if(commandPtr)
                    commandPtr->accept(fakeClient);
            }
        }
    }

    QCOMPARE(fakeClient.chat, chat);
    QCOMPARE(fakeClient.userList, userList);
}

QTEST_APPLESS_MAIN(ProtocolTest)

#include "tst_protocoltest.moc"

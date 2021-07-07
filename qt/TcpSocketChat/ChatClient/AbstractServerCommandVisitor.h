#ifndef ABSTRACTSERVERCOMMANDVISITOR_H
#define ABSTRACTSERVERCOMMANDVISITOR_H

class ServerCommandUserList;
class ServerCommandChat;
struct AbstractServerCommandVisitor
{
    virtual void visit(const ServerCommandUserList &command) = 0;
    virtual void visit(const ServerCommandChat &command) = 0;
};

#endif // ABSTRACTSERVERCOMMANDVISITOR_H

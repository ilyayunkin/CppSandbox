#ifndef ABSTRACTCLIENTCOMMANDVISITOR_H
#define ABSTRACTCLIENTCOMMANDVISITOR_H

class ClientCommandName;
class ClientCommandText;
struct AbstractClientCommandVisitor
{
    virtual void visit(ClientCommandName &command) = 0;
    virtual void visit(ClientCommandText &command) = 0;
};

#endif // ABSTRACTCLIENTCOMMANDVISITOR_H

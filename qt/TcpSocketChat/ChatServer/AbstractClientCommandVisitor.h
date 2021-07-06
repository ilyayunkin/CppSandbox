#ifndef ABSTRACTCLIENTCOMMANDVISITOR_H
#define ABSTRACTCLIENTCOMMANDVISITOR_H

class ClientCommandName;
class ClientCommandText;
struct AbstractClientCommandVisitor
{
    virtual void visit(ClientCommandName&) = 0;
    virtual void visit(ClientCommandText&) = 0;
};

#endif // ABSTRACTCLIENTCOMMANDVISITOR_H

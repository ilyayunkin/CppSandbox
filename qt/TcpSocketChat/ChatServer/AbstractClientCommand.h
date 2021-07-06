#ifndef ABSTRACTCLIENTCOMMAND_H
#define ABSTRACTCLIENTCOMMAND_H

#include <memory>

class AbstractClientCommandVisitor;
struct AbstractClientCommand
{
    virtual void accept(AbstractClientCommandVisitor &) = 0;
    virtual ~AbstractClientCommand(){}
};

using ClientCommandPtr = std::unique_ptr<AbstractClientCommand> ;

#endif // ABSTRACTCLIENTCOMMAND_H

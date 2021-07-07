#ifndef ABSTRACTSERVERCOMMAND_H
#define ABSTRACTSERVERCOMMAND_H

#include <memory>
#include <deque>

class AbstractServerCommandVisitor;
struct AbstractServerCommand
{
    virtual void accept(AbstractServerCommandVisitor &visitor) const = 0;
    virtual ~AbstractServerCommand(){}
};
using ServerCommandPtr = std::unique_ptr<AbstractServerCommand>;
using ServerCommandPtrList = std::deque<ServerCommandPtr>;

#endif // ABSTRACTSERVERCOMMAND_H

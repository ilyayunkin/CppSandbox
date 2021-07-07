#ifndef SERVERCOMMANDUSERLIST_H
#define SERVERCOMMANDUSERLIST_H

#include "AbstractServerCommand.h"
#include "AbstractServerCommandVisitor.h"
#include <QStringList>

struct ServerCommandUserList final : public AbstractServerCommand
{
    const QStringList userList;
    explicit ServerCommandUserList(const QStringList userList)
        : userList(userList)
    {}

    void accept(AbstractServerCommandVisitor &visitor) const override
    {
        visitor.visit(*this);
    }
};

#endif // SERVERCOMMANDUSERLIST_H

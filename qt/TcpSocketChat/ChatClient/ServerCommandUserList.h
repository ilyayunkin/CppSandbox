#ifndef SERVERCOMMANDUSERLIST_H
#define SERVERCOMMANDUSERLIST_H

#include "AbstractServerCommand.h"
#include "AbstractServerCommandVisitor.h"
#include <QStringList>

struct ServerCommandUserList : public AbstractServerCommand
{
    QStringList userList;
    explicit ServerCommandUserList(const QStringList userList)
        : userList(userList)
    {}

    void accept(AbstractServerCommandVisitor &visitor)
    {
        visitor.visit(*this);
    }
};

#endif // SERVERCOMMANDUSERLIST_H

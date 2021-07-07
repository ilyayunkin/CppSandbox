#ifndef SERVERCOMMANDCHAT_H
#define SERVERCOMMANDCHAT_H

#include "AbstractServerCommand.h"

#include "AbstractServerCommandVisitor.h"

#include <QString>

struct ServerCommandChat final : public AbstractServerCommand
{
    const QString chat;
    explicit ServerCommandChat(QString chat) : chat(chat)
    {}
    void accept(AbstractServerCommandVisitor &visitor) const override{
        visitor.visit(*this);
    }
};

#endif // SERVERCOMMANDCHAT_H

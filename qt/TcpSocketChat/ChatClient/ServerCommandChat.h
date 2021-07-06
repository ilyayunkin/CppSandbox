#ifndef SERVERCOMMANDCHAT_H
#define SERVERCOMMANDCHAT_H

#include "AbstractServerCommand.h"

#include "AbstractServerCommandVisitor.h"

#include <QString>

struct ServerCommandChat : public AbstractServerCommand
{
    QString chat;
    explicit ServerCommandChat(QString chat) : chat(chat)
    {}
    void accept(AbstractServerCommandVisitor &visitor){
        visitor.visit(*this);
    }
};

#endif // SERVERCOMMANDCHAT_H

#ifndef CLIENTCOMMANDNAME_H
#define CLIENTCOMMANDNAME_H

#include "AbstractClientCommand.h"
#include "AbstractClientCommandVisitor.h"

#include <QString>

struct ClientCommandName : public AbstractClientCommand
{
    QString name;
    explicit ClientCommandName(QString name) : name(name){};
    void accept(AbstractClientCommandVisitor &v){
        v.visit(*this);
    }
};

#endif // CLIENTCOMMANDNAME_H

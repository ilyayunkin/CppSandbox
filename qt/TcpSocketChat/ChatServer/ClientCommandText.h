#ifndef CLIENTCOMMANDTEXT_H
#define CLIENTCOMMANDTEXT_H

#include "AbstractClientCommand.h"
#include "AbstractClientCommandVisitor.h"

#include <QString>

struct ClientCommandText : public AbstractClientCommand
{
    QString text;
    explicit ClientCommandText(QString text) : text(text){};
    void accept(AbstractClientCommandVisitor &v){
        v.visit(*this);
    }
};

#endif // CLIENTCOMMANDTEXT_H

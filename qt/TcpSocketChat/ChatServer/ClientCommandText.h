#ifndef CLIENTCOMMANDTEXT_H
#define CLIENTCOMMANDTEXT_H

#include "AbstractClientCommand.h"
#include "AbstractClientCommandVisitor.h"

#include <QString>

struct ClientCommandText final : public AbstractClientCommand
{
    const QString text;
    explicit ClientCommandText(QString text) : text(text){};
    void accept(AbstractClientCommandVisitor &v) const override{
        v.visit(*this);
    }
};

#endif // CLIENTCOMMANDTEXT_H

#ifndef FOREACHMAPSTATEMENT_H_INCLUDED
#define FOREACHMAPSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class ForeachMapStatement : public Statement{
    private:
        std::string key, value;
        Expression* container;
        Statement* body;
    public:
        ForeachMapStatement(std::string key, std::string value, Expression* container, Statement* body) : key(key), value(value), container(container), body(body) {}
        Statements type(){ return Statements::ForeachMapStatement; }
        void execute();
        operator std::string();
        ~ForeachMapStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // FOREACHMAPSTATEMENT_H_INCLUDED

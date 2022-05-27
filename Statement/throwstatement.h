#ifndef THROWSTATEMENT_H_INCLUDED
#define THROWSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Value/value.h"

namespace SlavaScript::lang{
    class ThrowStatement : public Statement{
    private:
        Expression* expression;
        std::shared_ptr<Value> result;
    public:
        ThrowStatement(Expression* expression) : expression(expression) {}
        Statements type(){ return Statements::ThrowStatement; }
        std::shared_ptr<Value> getResult();
        /** @return  throw: ThrowStatement*. */
        void execute();
        operator std::string();
        ~ThrowStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // THROWSTATEMENT_H_INCLUDED

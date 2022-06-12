#ifndef FUNCTIONALEXPRESSION_H_INCLUDED
#define FUNCTIONALEXPRESSION_H_INCLUDED

#include <vector>
#include "expression.h"
#include "../Lib/function.h"

namespace SlavaScript::lang{
    class FunctionalExpression : public Expression{
    private:
        Expression* functionExpr;
        std::vector<Expression*> arguments;
        /** @return  throw: UnknownFunctionException*. */
        std::shared_ptr<Function> consumeFunction(std::shared_ptr<Value> value);
    public:
        FunctionalExpression(Expression* functionExpr) : functionExpr(functionExpr) {}
        Expressions type(){ return Expressions::FunctionalExpression; }
        void addArguments(Expression* argument);
        std::shared_ptr<Value> eval();
        operator std::string();
        ~FunctionalExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // FUNCTIONALEXPRESSION_H_INCLUDED

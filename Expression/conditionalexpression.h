#ifndef CONDITIONALEXPRESSION_H_INCLUDED
#define CONDITIONALEXPRESSION_H_INCLUDED

#include "conditionaloperator.h"
#include "expression.h"
#include <memory>

namespace SlavaScript{ namespace lang{
    class ConditionalExpression : public Expression{
    private:
        Expression* expr1, *expr2;
        ConditionalOperator operation;
    public:
        ConditionalExpression(ConditionalOperator operation, Expression* expr1, Expression* expr2) : operation(operation), expr1(expr1), expr2(expr2) {}
        /** @return  throw: OperationIsNotSupportedException*. */
        static std::shared_ptr<Value> calculate(ConditionalOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right);
        Expressions type(){ return Expressions::ConditionalExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~ConditionalExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // CONDITIONALEXPRESSION_H_INCLUDED

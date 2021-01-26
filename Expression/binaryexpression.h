#ifndef BINARYEXPRESSION_H_INCLUDED
#define BINARYEXPRESSION_H_INCLUDED

#include "binaryoperator.h"
#include "expression.h"

namespace SlavaScript{ namespace lang{
    class BinaryExpression : public Expression{
    private:
        Expression* expr1, *expr2;
        BinaryOperator operation;
    public:
        BinaryExpression(BinaryOperator operation) : operation(operation), expr1(nullptr), expr2(nullptr) {}
        BinaryExpression(BinaryOperator operation, Expression* expr1, Expression* expr2) : operation(operation), expr1(expr1), expr2(expr2) {}
        Expressions type(){ return Expressions::BinaryExpression; }
        /** @return  throw: TypeException*, OperationIsNotSupportedException*. */
        static Value* calculate(BinaryOperator operation, Value* left, Value* right);
        Value* eval();
        Value* eval(Value* value1, Value* value2);
        operator std::string();
        ~BinaryExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // BINARYEXPRESSION_H_INCLUDED

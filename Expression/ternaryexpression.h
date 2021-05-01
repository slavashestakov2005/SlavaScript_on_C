#ifndef TERNARYEXPRESSION_H_INCLUDED
#define TERNARYEXPRESSION_H_INCLUDED

#include "expression.h"

namespace SlavaScript{ namespace lang{
    class TernaryExpression : public Expression{
    private:
        Expression* condition, *trueExpr, *falseExpr;
    public:
        TernaryExpression(Expression* condition, Expression* trueExpr, Expression* falseExpr)
        : condition(condition), trueExpr(trueExpr), falseExpr(falseExpr) {}
        Expressions type(){ return Expressions::TernaryExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~TernaryExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // TERNARYEXPRESSION_H_INCLUDED

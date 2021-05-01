#ifndef OBJECTCREATIONEXPRESSION_H_INCLUDED
#define OBJECTCREATIONEXPRESSION_H_INCLUDED

#include <vector>
#include "expression.h"

namespace SlavaScript{ namespace lang{
    class ObjectCreationExpression : public Expression{
    private:
        std::string name;
        std::vector<Expression*> constructorArguments;
    public:
        ObjectCreationExpression(std::string name, std::vector<Expression*> constructorArguments) : name(name), constructorArguments(constructorArguments) {}
        Expressions type(){ return Expressions::ObjectCreationExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~ObjectCreationExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // OBJECTCREATIONEXPRESSION_H_INCLUDED

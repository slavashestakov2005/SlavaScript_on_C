#ifndef CONTAINERACCESSEXPRESSION_H_INCLUDED
#define CONTAINERACCESSEXPRESSION_H_INCLUDED

#include <vector>
#include "containeracceselement.h"
#include "expression.h"
#include "../Value/arrayvalue.h"
#include "../Value/mapvalue.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript::lang{
    class ContainerAccessExpression : public Expression{
    private:

    public:
        Expression* root = nullptr;
        ContainerAccessElement* access = nullptr;
        std::shared_ptr<Value> container = nullptr;
        std::shared_ptr<Value> index = nullptr;
        bool dot;
        ContainerAccessExpression(std::string variable, ContainerAccessElement* access);
        ContainerAccessExpression(Expression* root, ContainerAccessElement* access);
        Expressions type(){ return Expressions::ContainerAccessExpression; }
        std::shared_ptr<Value> eval();
        std::shared_ptr<Value> get();
        std::shared_ptr<Value> set(std::shared_ptr<Value> value);
        operator std::string();
        ~ContainerAccessExpression(){}
        void accept(Visitor* visitor);
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}

#endif // CONTAINERACCESSEXPRESSION_H_INCLUDED

#ifndef MAPEXPRESSION_H_INCLUDED
#define MAPEXPRESSION_H_INCLUDED

#include <map>
#include "expression.h"

namespace SlavaScript::lang{
    class MapExpression : public Expression{
    private:
        std::map<Expression*, Expression*> elements;
    public:
        MapExpression(std::map<Expression*, Expression*> elements) : elements(elements) {}
        Expressions type(){ return Expressions::MapExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~MapExpression(){}
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // MAPEXPRESSION_H_INCLUDED

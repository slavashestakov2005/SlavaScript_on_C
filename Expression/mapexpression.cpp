#include "mapexpression.h"
#include "../Value/mapvalue.h"

using namespace SlavaScript::lang;

MapExpression::MapExpression(std::map<Expression*, Expression*> elements) : elements(elements) {}

std::shared_ptr<Value> MapExpression::eval(){
    int siz = elements.size();
    std::shared_ptr<MapValue> map = SHARE(MapValue, );
    for (auto now : elements){
        map -> set(now.first -> eval(), now.second -> eval());
    }
    return map;
}

Expressions MapExpression::type() const{
    return Expressions::MapExpression;
}

MapExpression::operator std::string(){
    std::string result = "{";
    int siz = elements.size(), i = 0;
    for(auto now : elements){
        result += std::string(*(now.first));
        result += " : ";
        result += std::string(*(now.second));
        if (i < siz - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

MapExpression::~MapExpression(){}

void MapExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

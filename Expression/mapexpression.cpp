#include "mapexpression.h"
#include "../Value/mapvalue.h"

using namespace SlavaScript::lang;

std::shared_ptr<Value> MapExpression::eval(){
    int siz = elements.size();
    std::shared_ptr<MapValue> map = std::make_shared<MapValue>(siz);
    for (auto now : elements){
        map -> set(now.first -> eval(), now.second -> eval());
    }
    return map;
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

void MapExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

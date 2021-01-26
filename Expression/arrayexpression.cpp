#include "arrayexpression.h"
#include "../Value/arrayvalue.h"

using namespace SlavaScript::lang;

Value* ArrayExpression::eval(){
    ArrayValue* arr = new ArrayValue(elements.size());
    for(int i = 0; i < elements.size(); ++i){
        arr -> set(i, elements[i] -> eval());
    }
    return arr;
}

ArrayExpression::operator std::string(){
    std::string result = "[";
    for(int i = 0; i < elements.size(); ++i){
        result += std::string(*(elements[i]));
        if (i < elements.size() - 1) result += ", ";
    }
    result += "]";
    return result;
}

ArrayExpression::~ArrayExpression(){
    for(int i = 0; i < elements.size(); ++i){
        delete elements[i];
        elements[i] = nullptr;
    }
}

void ArrayExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

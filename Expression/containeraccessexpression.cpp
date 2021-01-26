#include "containeraccessexpression.h"
#include "../Lib/variables.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/classvalue.h"
#include "../Exception/typeexception.h"
#include "variableexpression.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ContainerAccessExpression::ContainerAccessExpression(std::string variable, std::vector<ContainerAccessElement> indices){
    (*this) = ContainerAccessExpression(new VariableExpression(variable), indices);
}

ContainerAccessExpression::ContainerAccessExpression(Expression* root, std::vector<ContainerAccessElement> indices) : root(root), indices(indices) {}

Value* ContainerAccessExpression::eval(){
    return get();
}

Value* ContainerAccessExpression::get(){
    Value* container = getContainer();
    Value* lastindex = lastIndex();
    bool lastdot = lastDot();
    switch(container -> type()){
        case Values::ARRAY:
            if (lastdot) return ((ArrayValue*) container) -> accessDot(lastindex);
            else return ((ArrayValue*) container) -> accessBracket(lastindex);
        case Values::MAP:
            if (lastdot && !((MapValue*) container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            return ((MapValue*) container) -> get(lastindex);
        case Values::STRING:
            if (lastdot) return ((StringValue*) container) -> accessDot(lastindex);
            else return ((StringValue*) container) -> accessBracket(lastindex);
        case Values::CLASS:
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            return ((ClassValue*) container) -> access(lastindex);
        default:
            throw new TypeException("Array, map, string or class expected");
    }
}

Value* ContainerAccessExpression::set(Value* value){
    Value* container = getContainer();
    Value* lastindex = lastIndex();
    bool lastdot = lastDot();
    switch(container -> type()){
        case Values::ARRAY : {
            if (lastdot) throw new std::logic_error("Cannot used DOT for array");
            int arrayIndex = (int) lastindex -> asDouble();
            ((ArrayValue*) container) -> set(arrayIndex, value);
            break;
        }
        case Values::MAP : {
            if (lastdot && !((MapValue*) container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            ((MapValue*) container) -> set(lastindex, value);
            break;
        }
        case Values::STRING : {
            if (lastdot) throw new std::logic_error("Cannot used DOT for string");
            int stringIndex = (int) lastindex -> asDouble();
            ((StringValue*) container) -> set(stringIndex, value);
            break;
        }
        case Values::CLASS : {
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            ((ClassValue*) container) -> set(lastindex, value);
            break;
        }
        default: throw new TypeException("Array, map, string or class expected");
    }
    return value;
}

Value* ContainerAccessExpression::getCopyElement(){
    Value* container = getContainer();
    switch(container -> type()){
        case Values::ARRAY : return new ArrayValue(((ArrayValue*) container) -> getCopyElement());
        case Values::MAP : return ((MapValue*) container) -> getCopyElement();
        default: return container;
    }
}

Value* ContainerAccessExpression::getContainer(){
    Value* container = root -> eval();
    int last = indices.size() - 1;
    for(int i = 0; i < last; ++i){
        Value* ind = index(i);
        bool isdot = isDot(i);
        switch(container -> type()){
            case Values::ARRAY : {
                if (isdot) container = ((ArrayValue*) container) -> accessDot(ind);
                else container = ((ArrayValue*) container) -> accessBracket(ind);
                break;
            }
            case Values::MAP : {
                if (isdot && !((MapValue*) container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
                container = ((MapValue*) container) -> get(ind);
                break;
            }
            case Values::STRING : {
                if (isdot) container = ((StringValue*) container) -> accessDot(ind);
                else container = ((StringValue*) container) -> accessBracket(ind);
                break;
            }
            case Values::CLASS : {
                if (!isdot) throw new std::logic_error("Cannot used [] for class");
                container = ((ClassValue*) container) -> get(ind);
                break;
            }
            default: throw new TypeException("Array, map, string or class expected");
        }
    }
    return container;
}

Value* ContainerAccessExpression::lastIndex(){
    return index(indices.size() - 1);
}

bool ContainerAccessExpression::lastDot(){
    return isDot(indices.size() - 1);
}

Value* ContainerAccessExpression::index(int index){
    return indices[index].eval();
}

bool ContainerAccessExpression::isDot(int index){
    return indices[index].isDot();
}

ContainerAccessExpression::operator std::string(){
    std::string result = std::string(*root);
    for(int i = 0; i < indices.size(); ++i){
        result += std::string(indices[i]);
    }
    return result;
}

void ContainerAccessExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

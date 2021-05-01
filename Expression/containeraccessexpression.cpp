#include "containeraccessexpression.h"
#include "../Lib/variables.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/classvalue.h"
#include "../Value/integrationvalue.h"
#include "../Exception/typeexception.h"
#include "variableexpression.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ContainerAccessExpression::ContainerAccessExpression(std::string variable, std::vector<ContainerAccessElement> indices){
    (*this) = ContainerAccessExpression(new VariableExpression(variable), indices);
}

ContainerAccessExpression::ContainerAccessExpression(Expression* root, std::vector<ContainerAccessElement> indices) : root(root), indices(indices) {}

std::shared_ptr<Value> ContainerAccessExpression::eval(){
    return get();
}

std::shared_ptr<Value> ContainerAccessExpression::get(){
    std::shared_ptr<Value> container = getContainer();
    std::shared_ptr<Value> lastindex = lastIndex();
    bool lastdot = lastDot();
    switch(container -> type()){
        case Values::ARRAY:
            if (lastdot) return (std::static_pointer_cast<ArrayValue>(container)) -> accessDot(lastindex);
            else return (std::static_pointer_cast<ArrayValue>(container)) -> accessBracket(lastindex);
        case Values::MAP:
            if (lastdot && !(std::static_pointer_cast<MapValue>(container)) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            return (std::static_pointer_cast<MapValue>(container)) -> get(lastindex);
        case Values::STRING:
            if (lastdot) return (std::static_pointer_cast<StringValue>(container)) -> accessDot(lastindex);
            else return (std::static_pointer_cast<StringValue>(container)) -> accessBracket(lastindex);
        case Values::CLASS:
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            return (std::static_pointer_cast<ClassValue>(container)) -> access(lastindex);
        case Values::INTEGRATION:
            if (!lastdot) throw new std::logic_error("Cannot used [] for integration");
            return (std::static_pointer_cast<IntegrationValue>(container)) -> accessDot(lastindex);
        default:
            throw new TypeException("Array, map, string, class or integration expected");
    }
}

std::shared_ptr<Value> ContainerAccessExpression::set(std::shared_ptr<Value> value){
    std::shared_ptr<Value> container = getContainer();
    std::shared_ptr<Value> lastindex = lastIndex();
    bool lastdot = lastDot();
    switch(container -> type()){
        case Values::ARRAY : {
            if (lastdot) throw new std::logic_error("Cannot used DOT for array");
            int arrayIndex = (int) lastindex -> asDouble();
            (std::static_pointer_cast<ArrayValue>(container))-> set(arrayIndex, value);
            break;
        }
        case Values::MAP : {
            if (lastdot && !(std::static_pointer_cast<MapValue>(container)) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            (std::static_pointer_cast<MapValue>(container)) -> set(lastindex, value);
            break;
        }
        case Values::STRING : {
            if (lastdot) throw new std::logic_error("Cannot used DOT for string");
            int stringIndex = (int) lastindex -> asDouble();
            (std::static_pointer_cast<StringValue>(container)) -> set(stringIndex, value);
            break;
        }
        case Values::CLASS : {
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            (std::static_pointer_cast<ClassValue>(container)) -> set(lastindex, value);
            break;
        }
        default: throw new TypeException("Array, map, string or class expected");
    }
    return value;
}

std::shared_ptr<Value> ContainerAccessExpression::getCopyElement(){
    std::shared_ptr<Value> container = getContainer();
    switch(container -> type()){
        case Values::ARRAY : return std::make_shared<ArrayValue>((std::static_pointer_cast<ArrayValue>(container)) -> getCopyElement());
        case Values::MAP : return (std::static_pointer_cast<MapValue>(container)) -> getCopyElement();
        default: return container;
    }
}

std::shared_ptr<Value> ContainerAccessExpression::getContainer(){
    std::shared_ptr<Value> container = root -> eval();
    int last = indices.size() - 1;
    for(int i = 0; i < last; ++i){
        std::shared_ptr<Value> ind = index(i);
        bool isdot = isDot(i);
        switch(container -> type()){
            case Values::ARRAY : {
                if (isdot) container = (std::static_pointer_cast<ArrayValue>(container)) -> accessDot(ind);
                else container = (std::static_pointer_cast<ArrayValue>(container)) -> accessBracket(ind);
                break;
            }
            case Values::MAP : {
                if (isdot && !(std::static_pointer_cast<MapValue>(container)) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
                container = (std::static_pointer_cast<MapValue>(container)) -> get(ind);
                break;
            }
            case Values::STRING : {
                if (isdot) container = (std::static_pointer_cast<StringValue>(container)) -> accessDot(ind);
                else container = (std::static_pointer_cast<StringValue>(container)) -> accessBracket(ind);
                break;
            }
            case Values::CLASS : {
                if (!isdot) throw new std::logic_error("Cannot used [] for class");
                container = (std::static_pointer_cast<ClassValue>(container)) -> get(ind);
                break;
            }
            default: throw new TypeException("Array, map, string or class expected");
        }
    }
    return container;
}

std::shared_ptr<Value> ContainerAccessExpression::lastIndex(){
    return index(indices.size() - 1);
}

bool ContainerAccessExpression::lastDot(){
    return isDot(indices.size() - 1);
}

std::shared_ptr<Value> ContainerAccessExpression::index(int index){
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

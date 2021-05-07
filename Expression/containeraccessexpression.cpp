#include "containeraccessexpression.h"
#include "../Lib/variables.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/classmodulevalue.h"
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
            if (lastdot) return CAST(ArrayValue, container) -> accessDot(lastindex);
            else return CAST(ArrayValue, container) -> accessBracket(lastindex);
        case Values::MAP:
            if (lastdot) return CAST(MapValue, container) -> accessDot(lastindex);
            else return CAST(MapValue, container) -> accessBracket(lastindex);
        case Values::STRING:
            if (lastdot) return CAST(StringValue, container) -> accessDot(lastindex);
            else return CAST(StringValue, container) -> accessBracket(lastindex);
        case Values::CLASS:
            if (container -> isClassFromModule()){
                if (lastdot) return CAST(ClassModuleValue, container) -> accessDot(lastindex);
                else return CAST(ClassModuleValue, container) -> accessBracket(lastindex);
            }
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            return CAST(ClassValue, container) -> access(lastindex);
        case Values::INTEGRATION:
            if (!lastdot) throw new std::logic_error("Cannot used [] for integration");
            return CAST(IntegrationValue, container) -> accessDot(lastindex);
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
            CAST(ArrayValue, container)-> set(arrayIndex, value);
            break;
        }
        case Values::MAP : {
            if (lastdot && !CAST(MapValue, container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            CAST(MapValue, container) -> set(lastindex, value);
            break;
        }
        case Values::STRING : {
            if (lastdot) throw new std::logic_error("Cannot used DOT for string");
            int stringIndex = (int) lastindex -> asDouble();
            CAST(StringValue, container) -> set(stringIndex, value);
            break;
        }
        case Values::CLASS : {
            if (container -> isClassFromModule()) throw new std::logic_error("Cannot set property to built-in class");
            if (!lastdot) throw new std::logic_error("Cannot used [] for class");
            CAST(ClassValue, container) -> set(lastindex, value);
            break;
        }
        default: throw new TypeException("Array, map, string or class expected");
    }
    return value;
}

std::shared_ptr<Value> ContainerAccessExpression::getCopyElement(){
    std::shared_ptr<Value> container = getContainer();
    switch(container -> type()){
        case Values::ARRAY : return SHARE(ArrayValue, CAST(ArrayValue, container) -> getCopyElement());
        case Values::MAP : return CAST(MapValue, container) -> getCopyElement();
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
                if (isdot) container = CAST(ArrayValue, container) -> accessDot(ind);
                else container = CAST(ArrayValue, container) -> accessBracket(ind);
                break;
            }
            case Values::MAP : {
                if (isdot) container = CAST(ArrayValue, container) -> accessDot(ind);
                else container = CAST(ArrayValue, container) -> accessBracket(ind);
                break;
            }
            case Values::STRING : {
                if (isdot) container = CAST(StringValue, container) -> accessDot(ind);
                else container = CAST(StringValue, container) -> accessBracket(ind);
                break;
            }
            case Values::CLASS : {
                if (container -> isClassFromModule()){
                    if (isdot) return CAST(ClassModuleValue, container) -> accessDot(ind);
                    else return CAST(ClassModuleValue, container) -> accessBracket(ind);
                }
                if (!isdot) throw new std::logic_error("Cannot used [] for class");
                container = CAST(ClassValue, container) -> get(ind);
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

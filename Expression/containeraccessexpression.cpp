#include "containeraccessexpression.h"
#include "../Lib/variables.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/classmodulevalue.h"
#include "../Value/objectvalue.h"
#include "../Value/integrationvalue.h"
#include "../Exception/typeexception.h"
#include "variableexpression.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ContainerAccessExpression::ContainerAccessExpression(std::string variable, ContainerAccessElement* access){
    (*this) = ContainerAccessExpression(new VariableExpression(variable), access);
}

ContainerAccessExpression::ContainerAccessExpression(Expression* root, ContainerAccessElement* access) : root(root), access(access) {}

std::shared_ptr<Value> ContainerAccessExpression::eval(){
    container = root -> eval();
    index = access -> eval();
    dot = access -> isDot();
    return get();
}

std::shared_ptr<Value> ContainerAccessExpression::get(){
    switch(container -> type()){
        case Values::ARRAY:
            if (dot) return CAST(ArrayValue, container) -> accessDot(index);
            else return CAST(ArrayValue, container) -> accessBracket(index);
        case Values::MAP:
            if (dot) return CAST(MapValue, container) -> accessDot(index);
            else return CAST(MapValue, container) -> accessBracket(index);
        case Values::STRING:
            if (dot) return CAST(StringValue, container) -> accessDot(index);
            else return CAST(StringValue, container) -> accessBracket(index);
        case Values::OBJECT:
            if (container -> isClassFromModule()){
                if (dot) return CAST(ClassModuleValue, container) -> accessDot(index);
                else return CAST(ClassModuleValue, container) -> accessBracket(index);
            }
            if (!dot) throw new std::logic_error("Cannot used [] for object");
            return CAST(ObjectValue, container) -> access(index);
        case Values::INTEGRATION:
            if (!dot) throw new std::logic_error("Cannot used [] for integration");
            return CAST(IntegrationValue, container) -> accessDot(index);
        default:
            throw new TypeException("Array, map, string, object or integration expected");
    }
}

std::shared_ptr<Value> ContainerAccessExpression::set(std::shared_ptr<Value> value){
    switch(container -> type()){
        case Values::ARRAY : {
            if (dot) throw new std::logic_error("Cannot used DOT for array");
            int arrayIndex = (int) index -> asDouble();
            CAST(ArrayValue, container)-> set(arrayIndex, value);
            break;
        }
        case Values::MAP : {
            if (dot && !CAST(MapValue, container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            CAST(MapValue, container) -> set(index, value);
            break;
        }
        case Values::STRING : {
            if (dot) throw new std::logic_error("Cannot used DOT for string");
            int stringIndex = (int) index -> asDouble();
            CAST(StringValue, container) -> set(stringIndex, value);
            break;
        }
        case Values::OBJECT : {
            if (container -> isClassFromModule()) throw new std::logic_error("Cannot set property to built-in object");
            if (!dot) throw new std::logic_error("Cannot used [] for object");
            CAST(ObjectValue, container) -> set(index, value);
            break;
        }
        default: throw new TypeException("Array, map, string or object expected");
    }
    return value;
}

ContainerAccessExpression::operator std::string(){
    return std::string(*root) + std::string(*access);
}

void ContainerAccessExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

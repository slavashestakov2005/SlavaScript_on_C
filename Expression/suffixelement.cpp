#include "suffixelement.h"
#include "../Exception/unknownfunctionexception.h"
#include "../Lib/functions.h"
#include "../Lib/moduleobject.h"
#include "../Lib/variables.h"
#include "../Run/callstack.h"
#include "../Value/arrayvalue.h"
#include "../Value/classvalue.h"
#include "../Value/functionvalue.h"
#include "../Value/integrationvalue.h"
#include "../Value/objectvalue.h"
#include "../Value/stringvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::UnknownFunctionException;

std::shared_ptr<Value> BracketSuffixElement::get(std::shared_ptr<Value> lastContainer, std::shared_ptr<Value> container){
    std::shared_ptr<Value> index = expression -> eval();
    switch(container -> type()){
        case Values::ARRAY: return CAST(ArrayValue, container) -> accessBracket(index);
        case Values::MAP: return CAST(MapValue, container) -> accessBracket(index);
        case Values::STRING: return CAST(StringValue, container) -> accessBracket(index);
        case Values::OBJECT:
            if (container -> isClassFromModule()) return CAST(ModuleObject, container) -> accessBracket(index);
            throw new std::logic_error("Cannot used [] for object");
        case Values::INTEGRATION: throw new std::logic_error("Cannot used [] for integration");
        default: throw new TypeException("Array, map, string, object or integration expected");
    }
}

std::shared_ptr<Value> BracketSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
     std::shared_ptr<Value> index = expression -> eval();
     switch(container -> type()){
        case Values::ARRAY : {
            int arrayIndex = (int) index -> asDouble();
            CAST(ArrayValue, container)-> set(arrayIndex, value);
            break;
        }
        case Values::MAP : {
            CAST(MapValue, container) -> set(index, value);
            break;
        }
        case Values::STRING : {
            int stringIndex = (int) index -> asDouble();
            CAST(StringValue, container) -> set(stringIndex, value);
            break;
        }
        case Values::OBJECT : {
            if (container -> isClassFromModule()) throw new std::logic_error("Cannot set property to built-in object");
            throw new std::logic_error("Cannot used [] for object");
        }
        case Values::INTEGRATION: throw new std::logic_error("Cannot used [] for integration");
        default: throw new TypeException("Array, map, string, object or integration expected");
    }
    return value;
}

BracketSuffixElement::operator std::string(){ return "[" + std::string(*expression) + "]"; }
SuffixType BracketSuffixElement::type() const { return SuffixType::BRACKET; }
BracketSuffixElement::~BracketSuffixElement(){ delete expression; }
void BracketSuffixElement::accept(Visitor* visitor){ expression -> accept(visitor); }


std::shared_ptr<Value> DotSuffixElement::get(std::shared_ptr<Value> lastContainer, std::shared_ptr<Value> container){
    std::shared_ptr<Value> index = expression -> eval();
    switch(container -> type()){
        case Values::ARRAY: return CAST(ArrayValue, container) -> accessDot(index);
        case Values::MAP: return CAST(MapValue, container) -> accessDot(index);
        case Values::STRING: return CAST(StringValue, container) -> accessDot(index);
        case Values::OBJECT:
            if (container -> isClassFromModule()) return CAST(ModuleObject, container) -> accessDot(index);
            else return CAST(ObjectValue, container) -> access(index);
        case Values::INTEGRATION: return CAST(IntegrationValue, container) -> accessDot(index);
        default: throw new TypeException("Array, map, string, object or integration expected");
    }
}

std::shared_ptr<Value> DotSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
    std::shared_ptr<Value> index = expression -> eval();
    switch(container -> type()){
        case Values::ARRAY: throw new std::logic_error("Cannot used DOT for array");
        case Values::MAP: {
            if (!CAST(MapValue, container) -> isThisMap()) throw new std::logic_error("Cannot used DOT for map");
            CAST(MapValue, container) -> set(index, value);
            break;
        }
        case Values::STRING: throw new std::logic_error("Cannot used DOT for string");
        case Values::OBJECT : {
            if (container -> isClassFromModule()) throw new std::logic_error("Cannot set property to built-in object");
            CAST(ObjectValue, container) -> set(index, value);
            break;
        }
        case Values::INTEGRATION: throw new std::logic_error("Cannot used DOT for integration");
        default: throw new TypeException("Array, map, string, object or integration expected");
    }
    return value;
}

DotSuffixElement::operator std::string(){ return "." + std::string(*expression); }
SuffixType DotSuffixElement::type() const { return SuffixType::DOT; }
DotSuffixElement::~DotSuffixElement(){ delete expression; }
void DotSuffixElement::accept(Visitor* visitor){ expression -> accept(visitor); }


std::shared_ptr<Value> ParenSuffixElement::get(std::shared_ptr<Value> lastContainer, std::shared_ptr<Value> container){
    std::vector<std::shared_ptr<Value>> values;
    for(int i = 0; i < arguments.size(); ++i) values.push_back(arguments[i] -> eval());
    std::shared_ptr<Value> result;
    if (container -> type() == Values::CLASS) {
        std::shared_ptr<ClassValue> cls = CAST(ClassValue, container);
        result = cls -> construct(values);
    }
    else if (container -> type() != Values::FUNCTION) throw new TypeException("Class or function expected for call");
    else{
        std::shared_ptr<Function> f = CAST(FunctionValue, container) -> getFunction();;
        CallStack::push(std::string(*this), f);
        if (f -> isClassMethod()) result = ClassMethod::execute(f, values, lastContainer);
        else result = f -> execute(values);
        CallStack::pop();
    }
    return result;
}

std::shared_ptr<Value> ParenSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
    throw new TypeException("Cannot set value to function");
}

ParenSuffixElement::operator std::string(){
    std::string result = "(";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(*arguments[i]);
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}

SuffixType ParenSuffixElement::type() const { return SuffixType::PAREN; }
ParenSuffixElement::~ParenSuffixElement(){ for(Expression* arg : arguments) delete arg; }
void ParenSuffixElement::accept(Visitor* visitor){ for(Expression* arg : arguments) arg -> accept(visitor); }

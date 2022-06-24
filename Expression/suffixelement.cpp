#include "suffixelement.h"
#include "../Exception/exceptions.h"
#include "../Lib/utils.h"
#include "../Run/callstack.h"
#include "../Value/classvalue.h"
#include "../Value/nullvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::LogicException;


SuffixElement::~SuffixElement(){}

BracketSuffixElement::BracketSuffixElement(Expression* expression) : expression(expression) {}

std::shared_ptr<Value> BracketSuffixElement::get(std::shared_ptr<Value> container){
    std::shared_ptr<Value> index = expression -> eval();
    return container -> getBracket(index);
}

std::shared_ptr<Value> BracketSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
    std::shared_ptr<Value> index = expression -> eval();
    container -> setBracket(index, value);
    return value;
}

SuffixType BracketSuffixElement::type() const { return SuffixType::BRACKET; }
BracketSuffixElement::operator std::string(){ return "[" + std::string(*expression) + "]"; }
BracketSuffixElement::~BracketSuffixElement(){ delete expression; }
void BracketSuffixElement::accept(Visitor* visitor){ expression -> accept(visitor); }


DotSuffixElement::DotSuffixElement(Expression* expression) : expression(expression) {}

std::shared_ptr<Value> DotSuffixElement::get(std::shared_ptr<Value> container){
    std::shared_ptr<Value> index = expression -> eval();
    return container -> getDot(index);
}

std::shared_ptr<Value> DotSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
    std::shared_ptr<Value> index = expression -> eval();
    container -> setDot(index, value);
    return value;
}

SuffixType DotSuffixElement::type() const { return SuffixType::DOT; }
DotSuffixElement::operator std::string(){ return "." + std::string(*expression); }
DotSuffixElement::~DotSuffixElement(){ delete expression; }
void DotSuffixElement::accept(Visitor* visitor){ expression -> accept(visitor); }


ParenSuffixElement::ParenSuffixElement(std::vector<Expression*> arguments) : arguments(arguments) {}

std::shared_ptr<Value> ParenSuffixElement::get(std::shared_ptr<Value> container){
    std::vector<std::shared_ptr<Value>> values;
    for(int i = 0; i < arguments.size(); ++i) values.push_back(arguments[i] -> eval());
    std::shared_ptr<Value> result = NullValue::NULL_;
    argType(Values::CLASS, Values::FUNCTION, container);
    if (container -> type() == Values::CLASS) {
        std::shared_ptr<ClassValue> cls = CAST(ClassValue, container);
        result = cls -> construct(values);
    }
    else{
        std::shared_ptr<Function> f = CAST(FunctionValue, container) -> getFunction();
        CallStack::push(std::string(*this), f);
        result = f -> execute(values);
        CallStack::pop();
    }
    return result;
}

std::shared_ptr<Value> ParenSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
    throw LogicException("Cannot set value to function result");
}

SuffixType ParenSuffixElement::type() const { return SuffixType::PAREN; }

ParenSuffixElement::operator std::string(){
    std::string result = "(";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(*arguments[i]);
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}

ParenSuffixElement::~ParenSuffixElement(){ for(Expression* arg : arguments) delete arg; }
void ParenSuffixElement::accept(Visitor* visitor){ for(Expression* arg : arguments) arg -> accept(visitor); }

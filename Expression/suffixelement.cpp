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
#include "../Value/nullvalue.h"
#include "../Value/objectvalue.h"
#include "../Value/stringvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::UnknownFunctionException;

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
    if (container -> type() == Values::CLASS) {
        std::shared_ptr<ClassValue> cls = CAST(ClassValue, container);
        result = cls -> construct(values);
    }
    else if (container -> type() != Values::FUNCTION) throw new TypeException("Class or function expected for call");
    else{
        std::shared_ptr<Function> f = CAST(FunctionValue, container) -> getFunction();
        CallStack::push(std::string(*this), f);
        result = f -> execute(values);
        CallStack::pop();
    }
    return result;
}

std::shared_ptr<Value> ParenSuffixElement::set(std::shared_ptr<Value> container, std::shared_ptr<Value> value){
    throw new TypeException("Cannot set value to function");
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

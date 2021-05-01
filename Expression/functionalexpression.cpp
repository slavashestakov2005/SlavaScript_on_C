#include "functionalexpression.h"
#include "../Lib/functions.h"
#include "../Lib/userdefinedfunction.h"
#include "../Lib/variables.h"
#include "../Value/functionvalue.h"
#include "valueexpression.h"
#include "../Exception/variabledoesnotexistsexception.h"
#include "../Exception/unknownfunctionexception.h"
#include "../Run/callstack.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::VariableDoesNotExistsException;
using SlavaScript::exceptions::UnknownFunctionException;

void FunctionalExpression::addArguments(Expression* argument){
    arguments.push_back(argument);
}

std::shared_ptr<Value> FunctionalExpression::eval(){
    std::vector<std::shared_ptr<Value>> values;
    for(int i = 0; i < arguments.size(); ++i) values.push_back(arguments[i] -> eval());
    std::shared_ptr<Function> f = consumeFunction(functionExpr);
    CallStack::push(std::string(*functionExpr), f);
    std::shared_ptr<Value> result = f -> execute(values);
    CallStack::pop();
    return result;
}

std::shared_ptr<Function> FunctionalExpression::consumeFunction(Expression* expr){
    try{
        std::shared_ptr<Value> value = expr -> eval();
        if (value -> type() == Values::FUNCTION) return CAST(FunctionValue, value) -> getFunction();
        return getFunction(value -> asString());
    }catch(VariableDoesNotExistsException* ex){
        return getFunction(ex -> getVariable());
    }
}

std::shared_ptr<Function> FunctionalExpression::getFunction(std::string name){
    if (Functions::find(name, arguments.size())) return Functions::get(name, arguments.size());
    else if (Functions::isExists(name)) return Functions::get(name);
    else if (Variables::isExists(name)){
        if (Variables::get(name) -> type() == Values::FUNCTION) return CAST(FunctionValue, Variables::get(name)) -> getFunction();
    }
    throw new UnknownFunctionException(name);
}

FunctionalExpression::operator std::string(){
    std::string result;
    if (functionExpr -> type() == Expressions::ValueExpression && ((ValueExpression*) functionExpr) -> value -> type() == Values::STRING){
        result += ((ValueExpression*) functionExpr) -> value -> asString() + "(";
    }
    else result += std::string(*functionExpr) + "(";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(*arguments[i]);
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}

FunctionalExpression::~FunctionalExpression(){
    for(unsigned i = 0; i < arguments.size(); ++i){
        delete arguments[i];
        arguments[i] = nullptr;
    }
}

void FunctionalExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

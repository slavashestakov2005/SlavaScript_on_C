#include "functionalexpression.h"
#include "containeraccessexpression.h"
#include "../Lib/classmethod.h"
#include "../Lib/functions.h"
#include "../Lib/userdefinedfunction.h"
#include "../Lib/variables.h"
#include "../Value/functionvalue.h"
#include "../Value/classvalue.h"
#include "../Value/objectvalue.h"
#include "valueexpression.h"
#include "variableexpression.h"
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
    std::shared_ptr<Value> value = functionExpr -> eval(), result;
    if (value -> type() == Values::CLASS) {
        std::shared_ptr<ClassValue> cls = CAST(ClassValue, value);
        result = cls -> construct(values);
    }
    else {
        std::shared_ptr<Function> f = consumeFunction(value);
        CallStack::push(std::string(*functionExpr), f);
        if (f -> isClassMethod() && functionExpr -> type() == Expressions::ContainerAccessExpression &&
            ((ContainerAccessExpression*)functionExpr) -> container -> type() == Values::OBJECT)
                result = (CAST(ClassMethod, f)) -> execute(values, CAST(ObjectValue, ((ContainerAccessExpression*)functionExpr) -> container));
        else result = f -> execute(values);
        CallStack::pop();
    }
    return result;
}

std::shared_ptr<Function> FunctionalExpression::consumeFunction(std::shared_ptr<Value> value){
    std::shared_ptr<Function> f = nullptr;
    if (value -> type() == Values::FUNCTION) f = CAST(FunctionValue, value) -> getFunction();
    if (f) return f;
    std::string name = value -> asString();
    if (Functions::find(name, arguments.size())) f = Functions::get(name, arguments.size());
    if (f) return f;
    if (Variables::isExists(name) && Variables::get(name) -> type() == Values::FUNCTION) f = CAST(FunctionValue, Variables::get(name)) -> getFunction();
    if (f) return f;
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

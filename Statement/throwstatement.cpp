#include "throwstatement.h"

using namespace SlavaScript::lang;

std::shared_ptr<Value> ThrowStatement::getResult(){
    return result;
}

void ThrowStatement::execute(){
    result = expression -> eval();
    throw this;
}

ThrowStatement::operator std::string(){
    return "throw " + std::string(*expression);
}

ThrowStatement::~ThrowStatement(){
    delete expression;
    expression = nullptr;
}

void ThrowStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

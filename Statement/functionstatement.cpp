#include "functionstatement.h"

using namespace SlavaScript::lang;

void FunctionStatement::execute(){
    function -> eval();
}

FunctionStatement::operator std::string(){
    return std::string(*function);
}

FunctionStatement::~FunctionStatement(){
    delete function;
    function = nullptr;
}

void FunctionStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

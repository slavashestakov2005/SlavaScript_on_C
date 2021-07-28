#include <sstream>
#include "functiondefinestatement.h"
#include "../Lib/names.h"
#include "../Lib/userdefinedfunction.h"

using namespace SlavaScript::lang;

void FunctionDefineStatement::execute(){
    execute(false); /// because FunctionAdder was doing execute(true)
}

void FunctionDefineStatement::execute(bool set){
    if (set) Names::setFunction(name, SHARE_2(UserDefinedFunction, arguments, body),
                   ArgumentsInfo(arguments.getRequiredCount(), arguments.size() - arguments.getRequiredCount() - arguments.getArrayCount(),
                                 arguments.getArrayCount()));
}

std::string FunctionDefineStatement::getName(){
    return name;
}

FunctionDefineStatement::operator std::string(){
    std::string result = "def '";
    result += name;
    result += "' (";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(arguments.get(i));
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ") ";
    if(body -> type() == Statements::ReturnStatement) result += " = ";
    result += std::string(*body);
    return result;
}

FunctionDefineStatement::~FunctionDefineStatement(){
    delete body;
    body = nullptr;
}

void FunctionDefineStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

#include <sstream>
#include "functiondefinestatement.h"
#include "../Lib/functions.h"
#include "../Lib/userdefinedfunction.h"

using namespace SlavaScript::lang;

void FunctionDefineStatement::execute(){
    Functions::set(name, new UserDefinedFunction(arguments, body));
}

void FunctionDefineStatement::execute(bool set){
    int start = arguments.getRequiredCount();
    int finish = arguments.getArrayCount() == 1 ? 100 : arguments.size();
    bool add = Functions::add(name, new UserDefinedFunction(arguments, body), start, finish);
    if (!add){
        std::ostringstream cnt;
        cnt << arguments.size();
        throw std::logic_error("Cannot redefinition user's function \"" + name + "\" with " + cnt.str() + " arguments");
    }
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

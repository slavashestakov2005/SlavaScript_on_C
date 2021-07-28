#include "classdeclarationsstatement.h"
#include "functiondefinestatement.h"
#include "../Expression/assignmentexpression.h"
#include "../Lib/names.h"

using namespace SlavaScript::lang;

void ClassDeclarationsStatement::addField(AssignmentExpression* expr){
    fields.push_back(expr);
}

void ClassDeclarationsStatement::addMethod(FunctionDefineStatement* statement){
    methods.push_back(statement);
}

void ClassDeclarationsStatement::execute(){
    Names::setClass(name, this);
}

ClassDeclarationsStatement::operator std::string(){
    std::string result = "class '" + name + "'{\n ";
    int i = 0;
    for(AssignmentExpression* expr : fields){
        result += std::string(*expr);
        if (i < fields.size() - 1) result += ", ";
        ++i;
    }
    i = 0;
    for(FunctionDefineStatement* function : methods){
        result += std::string(*function);
        if (i < methods.size() - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

ClassDeclarationsStatement::~ClassDeclarationsStatement(){
    for(int i = 0; i < methods.size(); ++i){
        delete methods[i];
        methods[i] = nullptr;
    }
    for(int i = 0; i < fields.size(); ++i){
        delete fields[i];
        fields[i] = nullptr;
    }
}

void ClassDeclarationsStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

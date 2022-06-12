#include "classdeclarationsstatement.h"
#include "functiondefinestatement.h"
#include "../Expression/assignmentexpression.h"
#include "../Lib/names.h"

using namespace SlavaScript::lang;

void ClassDeclarationsStatement::addField(std::vector<std::string> v, Expression* expr){
    fields.push_back({v, expr});
}

void ClassDeclarationsStatement::addMethod(FunctionDefineStatement* statement){
    methods.push_back(statement);
}

void ClassDeclarationsStatement::execute(){
    Names::setClass(name, this);
}

std::string ClassDeclarationsStatement::get_name(){
    return name;
}

ClassDeclarationsStatement::operator std::string(){
    std::string result = "class '" + name + "'{\n ";
    int i = 0;
    for(auto now : fields){
        for(auto field : now.first) result += "'" + field + "' = ";
        result += std::string(*now.second);
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
        delete fields[i].second;
        fields[i].second = nullptr;
    }
}

void ClassDeclarationsStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

#include "blockstatement.h"

using namespace SlavaScript::lang;

void BlockStatement::add(Statement* statement){
    statements.push_back(statement);
}

void BlockStatement::execute(){
    for(int i = 0; i < statements.size(); ++i){
        statements[i] -> execute();
    }
}

BlockStatement::operator std::string(){
    std::string result = "{\n";
    for(int i = 0; i < statements.size(); ++i){
        result += std::string(*statements[i]) + "\n";
    }
    result += "}";
    return result;
}

BlockStatement::~BlockStatement(){
    for(int i = 0; i < statements.size(); ++i) {
        delete statements[i];
        statements[i] = nullptr;
    }
}

void BlockStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

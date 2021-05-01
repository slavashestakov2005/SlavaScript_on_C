#include "breakstatement.h"
#include "continuestatement.h"
#include "switchstatement.h"

using namespace SlavaScript::lang;

void SwitchStatement::execute(){
    bool trueCase = false;
    try{
        for(int i = 0; i < body.size(); ++i){
            if (*(start -> eval()) == *(body[i].first -> eval())){
                trueCase = true;
                try{
                    body[i].second -> execute();
                } catch(ContinueStatement* cs){
                    // continue;
                }
            }
        }
        if (!trueCase && defaultCase != nullptr) defaultCase -> execute();
    } catch(BreakStatement* bs){
        // break;
    }
}

SwitchStatement::operator std::string(){
    std::string result = "switch " + std::string(*start) + " {\n";
    for (unsigned i = 0; i < body.size(); ++i){
        result += "case ";
        result += std::string(*body[i].first);
        result += " : ";
        result += std::string(*body[i].second);
        result += "\n";
    }
    if (defaultCase != nullptr){
        result += "default : ";
        result += std::string(*defaultCase);
        result += "\n";
    }
    result += "}\n";
    return result;
}

SwitchStatement::~SwitchStatement(){
    delete start;
    start = nullptr;
    for(unsigned i = 0; i < body.size(); ++i){
        delete body[i].first;
        body[i].first = nullptr;
        delete body[i].second;
        body[i].second = nullptr;
    }
    delete defaultCase;
    defaultCase = nullptr;
}

void SwitchStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

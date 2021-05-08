#include "callstack.h"
#include <sstream>

using namespace SlavaScript::lang;

std::vector<std::shared_ptr<CallInfo>> CallStack::calls = {};

void CallStack::push(std::string name, std::shared_ptr<Function> function){
    calls.push_back(SHARE_2(CallInfo, name, function));
}

void CallStack::pop(){
    calls.pop_back();
}

void CallStack::clear(){
    calls.clear();
}

std::string CallStack::callsToString(){
    std::string result;
    int size = calls.size();
    if (size > 0) result += "1 : " + std::string(*(calls[0]));
    for(int i = 1; i < size; ++i){
        std::stringstream ss;
        ss << i + 1;
        result += "\n" + ss.str() + " : " + std::string(*calls[i]);
    }
    return result;
}

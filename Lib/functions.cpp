#include <iostream>
#include <sstream>
#include "function.h"
#include "functions.h"
#include "../Exception/unknownfunctionexception.h"
#include "../Modules/global.h"

using namespace SlavaScript::lang;
using SlavaScript::modules::Global;
using SlavaScript::exceptions::UnknownFunctionException;

std::vector<FunctionsScope> Functions::scope = {};

void FunctionsScope::start(){
    functions.clear();
    Global::initFunctions();
}

std::map<std::string, Function*> FunctionsScope::getScope(){
    return functions;
}

bool FunctionsScope::isExists(std::string key){
    return functions.find(key) != functions.cend();
}

Function* FunctionsScope::get(std::string key){
    if (!isExists(key)) throw new UnknownFunctionException(key);
    else return functions[key];
}

void FunctionsScope::set(std::string key, Function* function){
    functions[key] = function;
}

bool FunctionsScope::add(std::string key, Function* function, int start, int finish){
    int i = start;
    bool result = true;
    key = "'" + key + "'";
    while(i <= finish && result){
        std::stringstream ss;
        ss << i;
        std::string now = key + ss.str();
        result = !isExists(now);
        if (result) functions[now] = function;
        ++i;
    }
    return result;
}

bool FunctionsScope::find(std::string key, int count){
    std::stringstream ss;
    ss << count;
    return isExists("'" + key + "'" + ss.str());
}

Function* FunctionsScope::get(std::string key, int count){
    std::stringstream ss;
    ss << count;
    return get("'" + key + "'" + ss.str());
}

void FunctionsScope::print(){
    for (auto now : functions) std::cout << now.first << "\t\t" << now.second -> type << std::endl;
}



void Functions::init(){
    pushScope();
}

void Functions::start() { scope.back().start(); }
std::map<std::string, Function*> Functions::getScope(){ return scope.back().getScope(); }
bool Functions::isExists(std::string key) { return scope.back().isExists(key); }
Function* Functions::get(std::string key) { return scope.back().get(key); }
Function* Functions::get(std::string key, int count) { return scope.back().get(key, count); }
void Functions::set(std::string key, Function* function) { scope.back().set(key, function); }
bool Functions::add(std::string key, Function* function, int start, int finish) { return scope.back().add(key, function, start, finish); }
bool Functions::find(std::string key, int count){ return scope.back().find(key, count); }
void Functions::print() { scope.back().print(); }

void Functions::pushScope(){
    scope.push_back(FunctionsScope());
    start();
}

void Functions::popScope(){
    scope.pop_back();
}

void Functions::copyScope(){
    std::map<std::string, Function*> top = scope.back().getScope();
    scope.pop_back();
    for(auto x : top){
        // if (!scope.back().isExists(x.first)) scope.back().set(x.first, x.second);
        scope.back().set(x.first, x.second);
    }
}

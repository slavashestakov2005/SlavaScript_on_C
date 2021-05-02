#include "variables.h"
#include "../Value/nullvalue.h"
#include "../Modules/global.h"
#include <iostream>

using namespace SlavaScript::lang;
using SlavaScript::modules::Global;

std::vector<VariablesScope> Variables::scope = {};

void VariablesScope::start(){
    variables.clear();
    vec.clear();
    Global::initConstants();
}

void VariablesScope::push(){
    vec.push_back(variables);
}

void VariablesScope::pop(){
    variables = vec.back();
    vec.pop_back();
}

std::map<std::string, std::shared_ptr<Value>> VariablesScope::getScope(){
    return variables;
}

bool VariablesScope::isExists(std::string key){
    return variables.find(key) != variables.cend();
}

std::shared_ptr<Value> VariablesScope::get(std::string key){
    if (!isExists(key)) return NullValue::NULL_;
    else return variables[key];
}

void VariablesScope::set(std::string key, std::shared_ptr<Value> value){
    variables[key] = value;
}

void VariablesScope::print(){
    for (auto now : variables) std::cout << now.first << "\t\t" << std::string(*now.second) << std::endl;
}



void Variables::init(){
    pushScope();
}

void Variables::start() { scope.back().start(); }
void Variables::push() { scope.back().push(); }
void Variables::pop() { scope.back().pop(); }
std::map<std::string, std::shared_ptr<Value>> Variables::getScope(){ return scope.back().getScope(); }
bool Variables::isExists(std::string key) { return scope.back().isExists(key); }
std::shared_ptr<Value> Variables::get(std::string key) { return scope.back().get(key); }
void Variables::set(std::string key, std::shared_ptr<Value> value) { scope.back().set(key, value); }
void Variables::print() { scope.back().print(); }

void Variables::pushScope(){
    scope.push_back(VariablesScope());
    start();
}

void Variables::popScope(){
    scope.pop_back();
}

void Variables::copyScope(){
    std::map<std::string, std::shared_ptr<Value>> top = scope.back().getScope();
    scope.pop_back();
    for(auto x : top){
        // if (!scope.back().isExists(x.first)) scope.back().set(x.first, x.second);
        scope.back().set(x.first, x.second);
    }
}

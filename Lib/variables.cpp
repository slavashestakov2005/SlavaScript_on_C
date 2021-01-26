#include "variables.h"
#include "../Value/numbervalue.h"
#include "../Value/boolvalue.h"
#include "../Value/nullvalue.h"
#include "../Modules/global.h"
#include <iostream>

using namespace SlavaScript::lang;
using SlavaScript::modules::Global;

std::map<std::string, Value*> Variables::variables = {};

std::vector<std::map<std::string, Value*>*> Variables::vec = {};

bool Variables::insert = true;

std::map<std::string, Value*> Variables::now = {};

void Variables::start(){
    variables.clear();
    vec.clear();
    now.clear();
    insert = true;
    Global::initConstants();
}

void Variables::setInsert(bool v){
    insert = v;
    now.clear();
}

std::map<std::string, Value*> Variables::getNow(){
    return now;
}

void Variables::push(){
    std::map<std::string, Value*>* cop = new std::map<std::string, Value*>();
    for(auto x : variables) (*cop)[x.first] = x.second;
    vec.push_back(cop);
}

void Variables::pop(){
    variables = *(vec.back());
    vec.pop_back();
}

bool Variables::isExists(std::string key){
    return variables.find(key) != variables.cend();
}

Value* Variables::get(std::string key){
    if (!isExists(key)) return NullValue::NULL_;
    else return variables[key];
}

void Variables::set(std::string key, Value* value){
    if (insert) variables[key] = value;
    else now[key] = value;
}

void Variables::print(){
    for (auto now : variables) std::cout << now.first << "\t\t" << std::string(*now.second) << std::endl;
}

#include <iostream>
#include <sstream>
#include "function.h"
#include "functions.h"
#include "../Exception/unknownfunctionexception.h"
#include "../Modules/global.h"

using namespace SlavaScript::lang;
using SlavaScript::modules::Global;
using SlavaScript::exceptions::UnknownFunctionException;

std::map<std::string, Function*> Functions::functions = {};

std::map<std::string, Function*> Functions::now = {};

bool Functions::insert = true;

void Functions::start(){
    functions.clear();
    now.clear();
    insert = true;
    Global::initFunctions();
}

void Functions::setInsert(bool v){
    insert = v;
    now.clear();
}

std::map<std::string, Function*> Functions::getNow(){
    return now;
}

void Functions::clear(){
    functions.clear();
}

bool Functions::isExists(std::string key){
    return functions.find(key) != functions.cend();
}

Function* Functions::get(std::string key){
    if (!isExists(key)) throw new UnknownFunctionException(key);
    else return functions[key];
}

void Functions::set(std::string key, Function* function){
    if (insert) functions[key] = function;
    else now[key] = function;
}

bool Functions::add(std::string key, Function* function, int start, int finish){
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

bool Functions::find(std::string key, int count){
    std::stringstream ss;
    ss << count;
    return isExists("'" + key + "'" + ss.str());
}

Function* Functions::get(std::string key, int count){
    std::stringstream ss;
    ss << count;
    return get("'" + key + "'" + ss.str());
}

void Functions::print(){
    for (auto now : functions) std::cout << now.first << "\t\t" << now.second -> type << std::endl;
}

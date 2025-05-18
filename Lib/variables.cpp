#include <iostream>

#include <Lib/names.h>
#include <Lib/variables.h>
#include <Modules/global.h>
#include <Value/nullvalue.h>


using namespace SlavaScript::lang;
using SlavaScript::modules::Global;


std::vector<VariablesScope> Variables::scope = {};

void VariablesScope::start() {
    variables.clear();
    vec.clear();
    Global::initConstants();
}

void VariablesScope::push() {
    vec.push_back(variables);
}

void VariablesScope::pop() {
    variables = vec.back();
    vec.pop_back();
}

std::map<std::string, std::shared_ptr<Value>> VariablesScope::getScope() {
    return variables;
}

bool VariablesScope::isExists(std::string key) {
    return variables.find(key) != variables.cend();
}

std::shared_ptr<Value> VariablesScope::get(std::string key) {
    if (!isExists(key)) return NullValue::NULL_;
    else return variables[key];
}

void VariablesScope::set(std::string key, std::shared_ptr<Value> value) {
    variables[key] = value;
}

void VariablesScope::erase(std::string key) {
    variables.erase(key);
}

void VariablesScope::print() {
    for (auto now : variables) std::cout << now.first << "\t\t" << std::string(*now.second) << std::endl;
}

std::shared_ptr<Value> VariablesScope::save(std::string key) {
    if (!isExists(key)) return nullptr;
    else return variables[key];
}

void VariablesScope::restore(NamedValue named) {
    variables[named.name] = named.variable;
}


void Variables::init() {
    pushScope();
}

void Variables::start() { scope.back().start(); }
void Variables::push() { scope.back().push(); }
void Variables::pop() { scope.back().pop(); }
std::map<std::string, std::shared_ptr<Value>> Variables::getScope() { return scope.back().getScope(); }
bool Variables::isExists(std::string key) { return scope.back().isExists(key); }
std::shared_ptr<Value> Variables::get(std::string key) { return scope.back().get(key); }
void Variables::set(std::string key, std::shared_ptr<Value> value) { scope.back().set(key, value); }
void Variables::erase(std::string key) { scope.back().erase(key); }
void Variables::print() { scope.back().print(); }
std::shared_ptr<Value> Variables::save(std::string key) { return scope.back().save(key); }
void Variables::restore(NamedValue named) { scope.back().restore(named); }

void Variables::pushScope() {
    scope.push_back(VariablesScope());
    start();
}

void Variables::popScope() {
    scope.pop_back();
}

void Variables::copyScope() {
    std::map<std::string, std::shared_ptr<Value>> top = scope.back().getScope();
    scope.pop_back();
    for (auto x : top) {
        // if (!scope.back().isExists(x.first)) scope.back().set(x.first, x.second);
        scope.back().set(x.first, x.second);
    }
}

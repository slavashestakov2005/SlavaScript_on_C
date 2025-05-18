#include <iostream>

#include <Exception/exceptions.h>
#include <Lib/functions.h>
#include <Lib/names.h>
#include <Modules/global.h>


using namespace SlavaScript::lang;
using SlavaScript::modules::Global;
using SlavaScript::exceptions::UnknownFunctionException;


ArgumentsInfo ArgumentsInfo::without(0), ArgumentsInfo::unary(1), ArgumentsInfo::binary(2), ArgumentsInfo::ternary(3), ArgumentsInfo::quaternary(4),
            ArgumentsInfo::inf(0, 0, 1), ArgumentsInfo::inf1(1, 0, 1);


ArgumentsInfo::ArgumentsInfo(int required, int optional, int array) : required(required), optional(optional), array(array) {}
int ArgumentsInfo::getRequired() const { return required; }
int ArgumentsInfo::getOptional() const { return optional; }
int ArgumentsInfo::getArray() const { return array; }
bool ArgumentsInfo::canCalled(int argsCount) const { return required <= argsCount && (array || argsCount <= required + optional); }


std::vector<FunctionsScope> Functions::scope = {};

void FunctionsScope::start() {
    functions.clear();
    Global::initFunctions();
}

std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> FunctionsScope::getScope() {
    return functions;
}

bool FunctionsScope::isExists(std::string key) {
    return functions.find(key) != functions.cend();
}

void FunctionsScope::set(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info) {
    if (!isExists(key)) functions[key] = {{info, function}};
    else functions[key].push_back({info, function});
}

void FunctionsScope::set(std::string key, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> vals) {
    functions[key] = vals;
}

void FunctionsScope::erase(std::string key) {
    functions.erase(key);
}

bool FunctionsScope::find(std::string key, int count) {
    if (!isExists(key)) return false;
    int goodCount = 0;
    for (auto x : functions[key]) {
        if (x.first.canCalled(count)) ++goodCount;
    }
    return goodCount == 1;
}

std::shared_ptr<Function> FunctionsScope::get(std::string key) {
    if (!isExists(key)) throw UnknownFunctionException(key);
    if (functions[key].size() > 1) throw UnknownFunctionException("overloaded " + key);
    return functions[key][0].second;
}

std::shared_ptr<Function> FunctionsScope::get(std::string key, int count) {
    for (auto x : functions[key]) {
        if (x.first.canCalled(count)) return x.second;
    }
    return nullptr;
}

void FunctionsScope::print() {
    for (auto now : functions) {
        for (auto now2 : now.second) std::cout << now.first << std::endl;
    }
}

std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> FunctionsScope::save(std::string key) {
    if (!isExists(key)) return {};
    else return functions[key];
}

void FunctionsScope::restore(NamedValue named) {
    functions[named.name] = named.function;
}


void Functions::init() {
    pushScope();
}

void Functions::start() { scope.back().start(); }
std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> Functions::getScope() { return scope.back().getScope(); }
bool Functions::isExists(std::string key) { return scope.back().isExists(key); }
std::shared_ptr<Function> Functions::get(std::string key) { return scope.back().get(key); }
std::shared_ptr<Function> Functions::get(std::string key, int count) { return scope.back().get(key, count); }
void Functions::set(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info) { scope.back().set(key, function, info); }
void Functions::erase(std::string key) { scope.back().erase(key); }
bool Functions::find(std::string key, int count) { return scope.back().find(key, count); }
void Functions::print() { scope.back().print(); }
std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> Functions::save(std::string key) { return scope.back().save(key); }
void Functions::restore(NamedValue named) { scope.back().restore(named); }

void Functions::pushScope() {
    scope.push_back(FunctionsScope());
    start();
}

void Functions::popScope() {
    scope.pop_back();
}

void Functions::copyScope() {
    std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> top = scope.back().getScope();
    scope.pop_back();
    for (auto x : top) {
        // if (!scope.back().isExists(x.first)) scope.back().set(x.first, x.second);
        scope.back().set(x.first, x.second);
    }
}

#include <Exception/exceptions.h>
#include <Lib/classes.h>
#include <Lib/names.h>
#include <Modules/global.h>


using namespace SlavaScript::lang;
using SlavaScript::modules::Global;
using SlavaScript::exceptions::UnknownClassException;


std::vector<ClassesScope> Classes::scope = {};

void ClassesScope::start() {
    declarations.clear();
    Global::initClasses();
}

std::map<std::string, std::shared_ptr<ClassValue>> ClassesScope::getScope() {
    return declarations;
}

bool ClassesScope::isExists(std::string key) {
    return declarations.find(key) != declarations.cend();
}

std::shared_ptr<ClassValue> ClassesScope::get(std::string key) {
    if (!isExists(key)) throw UnknownClassException(key);
    return declarations[key];
}

void ClassesScope::set(std::string key, std::shared_ptr<ClassValue> classDef) {
    declarations[key] = classDef;
}

void ClassesScope::erase(std::string key) {
    declarations.erase(key);
}

std::shared_ptr<ClassValue> ClassesScope::save(std::string key) {
    if (!isExists(key)) return nullptr;
    return declarations[key];
}

void ClassesScope::restore(NamedValue named) {
    declarations[named.name] = named.classDec;
}


void Classes::init() {
    pushScope();
}

void Classes::start() { scope.back().start(); }
std::map<std::string, std::shared_ptr<ClassValue>> Classes::getScope() { return scope.back().getScope(); }
bool Classes::isExists(std::string key) { return scope.back().isExists(key); }
std::shared_ptr<ClassValue> Classes::get(std::string key) { return scope.back().get(key); }
void Classes::set(std::string key, std::shared_ptr<ClassValue> classDef) { scope.back().set(key, classDef); }
void Classes::erase(std::string key) { scope.back().erase(key); }
std::shared_ptr<ClassValue> Classes::save(std::string key) { return scope.back().save(key); }
void Classes::restore(NamedValue named) { scope.back().restore(named); }

void Classes::pushScope() {
    scope.push_back(ClassesScope());
    start();
}

void Classes::popScope() {
    scope.pop_back();
}

void Classes::copyScope() {
    std::map<std::string, std::shared_ptr<ClassValue>> top = scope.back().getScope();
    scope.pop_back();
    for (auto x : top) {
        // if (!scope.back().isExists(x.first)) scope.back().set(x.first, x.second);
        scope.back().set(x.first, x.second);
    }
}

#include "classdeclarations.h"
#include "../Exception/unknownclassexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::UnknownClassException;

std::vector<ClassDeclarationsScope> ClassDeclarations::scope = {};

void ClassDeclarationsScope::start(){
    declarations.clear();
    // Global::initClasses();
}

std::map<std::string, ClassDeclarationsStatement*> ClassDeclarationsScope::getScope(){
    return declarations;
}

bool ClassDeclarationsScope::isExists(std::string key){
    return declarations.find(key) != declarations.cend();
}

ClassDeclarationsStatement* ClassDeclarationsScope::get(std::string key){
    if (!isExists(key)) throw new UnknownClassException(key);
    return declarations[key];
}

void ClassDeclarationsScope::set(std::string key, ClassDeclarationsStatement* classDef){
    declarations[key] = new ClassDeclarationsStatement(*classDef);
}


void ClassDeclarations::init(){
    pushScope();
}

void ClassDeclarations::start(){ scope.back().start(); }
std::map<std::string, ClassDeclarationsStatement*> ClassDeclarations::getScope() { return scope.back().getScope(); }
bool ClassDeclarations::isExists(std::string key){ return scope.back().isExists(key); }
ClassDeclarationsStatement* ClassDeclarations::get(std::string key){ return scope.back().get(key); }
void ClassDeclarations::set(std::string key, ClassDeclarationsStatement* classDef){ scope.back().set(key, classDef); }
//void print();
void ClassDeclarations::pushScope(){
    scope.push_back(ClassDeclarationsScope());
    start();
}

void ClassDeclarations::popScope(){
    scope.pop_back();
}

void ClassDeclarations::copyScope(){
    std::map<std::string, ClassDeclarationsStatement*> top = scope.back().getScope();
    scope.pop_back();
    for(auto x : top){
        // if (!scope.back().isExists(x.first)) scope.back().set(x.first, x.second);
        scope.back().set(x.first, x.second);
    }
}

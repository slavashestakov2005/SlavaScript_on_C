#include "importstatement.h"
#include "../Run/path.h"
#include "../Run/start.h"
#include "../Exception/unknownmoduleexception.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Lib/classdeclarations.h"
#include "../Modules/all.h"
#include "../Value/mapvalue.h"
#include "../Value/stringvalue.h"
#include "../Modules/modules.h"

using namespace SlavaScript::lang;
using SlavaScript::modules::try_import_module;
using SlavaScript::exceptions::UnknownModuleException;

void ImportStatement::execute(){
    if (!Path::getImpoted()) return;
    bool named = moduleName != "";
    Variables::pushScope();
    Functions::pushScope();
    ClassDeclarations::pushScope();
    for(std::string name : names){
        if (!try_import_module(name)){
            try{
                if (name.find("\\") == std::string::npos && name.find("/") == std::string::npos) name = Path::getPath() + name;
                Start start(name);
                start.start();
            }catch(...){
                Variables::popScope();
                Functions::popScope();
                ClassDeclarations::popScope();
                throw new UnknownModuleException(name);
            }
        }
    }
    if (named){
        std::map<std::string, std::shared_ptr<Value>> variables = Variables::getScope();
        std::map<std::string, std::shared_ptr<Function>> functions = Functions::getScope();
        // ClassDeclarations::getScope();
        std::shared_ptr<MapValue> map = std::make_shared<MapValue>(1);
        for(auto x : variables) map -> set(std::make_shared<StringValue>(x.first), x.second);
        for(auto x : functions) map -> set(std::make_shared<StringValue>(x.first), x.second);
        // for each
        map -> setThisMap(true);
        Variables::popScope();
        Functions::popScope();
        ClassDeclarations::popScope();
        Variables::set(moduleName, map);
    }
    else{
        Variables::copyScope();
        Functions::copyScope();
        ClassDeclarations::copyScope();
    }
}

ImportStatement::operator std::string(){
    std::string result = "import [";
    for(int i = 0; i < names.size(); ++i){
        result += "'" + names[i] + "'";
        if (i < names.size() - 1) result += ", ";
    }
    result += "]" + (moduleName == "" ? "" : " as '" + moduleName + "'");
    return result;
}

ImportStatement::~ImportStatement(){}

void ImportStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

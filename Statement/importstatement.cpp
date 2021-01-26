#include "importstatement.h"
#include "../path.h"
#include "../start.h"
#include "../Exception/unknownmoduleexception.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
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
    if (named){
        Variables::setInsert(false);
        Functions::setInsert(false);
    } else{
        Variables::setInsert(true);
        Functions::setInsert(true);
    }
    for(std::string name : names){
        if (!try_import_module(name)){
            try{
                if (name.find("\\") == std::string::npos && name.find("/") == std::string::npos) name = Path::getPath() + name;
                Start start(name);
                start.start();
            }catch(...){
                if (named){
                    Variables::setInsert(true);
                    Functions::setInsert(true);
                }
                throw new UnknownModuleException(name);
            }
        }
    }
    if (named){
        std::map<std::string, Value*> variables = Variables::getNow();
        std::map<std::string, Function*> functions = Functions::getNow();
        MapValue* map = new MapValue(1);
        for(auto x : variables) map -> set(new StringValue(x.first), x.second);
        for(auto x : functions) map -> set(new StringValue(x.first), x.second);
        map -> setThisMap(true);
        Variables::setInsert(true);
        Functions::setInsert(true);
        Variables::set(moduleName, map);
    }
    Variables::setInsert(true);
    Functions::setInsert(true);
}

ImportStatement::operator std::string(){
    std::string result = "import [";
    for(int i = 0; i < names.size(); ++i){
        result += names[i];
        if (i < names.size() - 1) result += ", ";
    }
    result += "]" + (moduleName == "" ? "" : " as " + moduleName);
    return result;
}

ImportStatement::~ImportStatement(){}

void ImportStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

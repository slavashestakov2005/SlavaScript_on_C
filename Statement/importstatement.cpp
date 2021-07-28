#include "importstatement.h"
#include "../Run/path.h"
#include "../Run/start.h"
#include "../Exception/unknownmoduleexception.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Lib/classdeclarations.h"
#include "../Lib/names.h"
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
    Names::pushScope();
    for(std::string name : names){
        if (!try_import_module(name)){
            try{
                if (name.find("\\") == std::string::npos && name.find("/") == std::string::npos) name = Path::getPath() + name;
                Start start(name);
                start.start();
            }catch(...){
                Names::popScope();
                throw new UnknownModuleException(name);
            }
        }
    }
    if (named){
        std::map<std::string, std::shared_ptr<Value>> variables = Variables::getScope();
        std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> functions = Functions::getScope();
        // ClassDeclarations::getScope();
        std::shared_ptr<MapValue> map = SHARE(MapValue, 1);
        for(auto x : variables) map -> set(SHARE(StringValue, x.first), x.second);
        for(auto x : functions){
            if (x.second.size() > 1) throw std::logic_error("Cannot import overloaded function");
            map -> set(SHARE(StringValue, x.first), x.second[0].second);
        }
        // for each
        map -> setThisMap(true);
        Names::popScope();
        Names::setVariable(moduleName, map);
    }
    else Names::copyScope();
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

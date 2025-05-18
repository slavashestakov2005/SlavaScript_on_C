#include <Exception/exceptions.h>
#include <Lib/moduleobject.h>
#include <Lib/names.h>
#include <Lib/variables.h>
#include <Modules/modules.h>
#include <Run/path.h>
#include <Run/start.h>
#include <Statement/importstatement.h>
#include <Value/mapvalue.h>
#include <Value/stringvalue.h>


using namespace SlavaScript::lang;
using SlavaScript::modules::try_import_module;
using SlavaScript::exceptions::LogicException;
using SlavaScript::exceptions::UnknownModuleException;

namespace {
    CLASS_IN_MODULE_1(Import)
        std::shared_ptr<MapValue> map;

        Import(std::shared_ptr<MapValue> map) : map(map) {}

        std::shared_ptr<Value> copy() override {
            SH_RET(Import, CAST(MapValue, map -> copy()));
        }

        std::shared_ptr<Value> getDot(std::shared_ptr<Value> property) override {
            return map -> getBracket(property);
        }

        ~Import() {}
    CLASS_IN_MODULE_2(Import)
}

ImportStatement::ImportStatement(std::vector<std::string> names, std::string moduleName) : names(names), moduleName(moduleName) {}

void ImportStatement::execute() {
    if (!Path::getImpoted()) return;
    bool named = moduleName != "";
    Names::pushScope();
    for (std::string name : names) {
        if (!try_import_module(name)) {
            try {
                if (name.find("\\") == std::string::npos && name.find("/") == std::string::npos) name = Path::getPath() + name;
                Start start(name);
                start.start();
            } catch (...) {
                Names::popScope();
                throw UnknownModuleException(name);
            }
        }
    }
    if (named) {
        std::map<std::string, std::shared_ptr<Value>> variables = Variables::getScope();
        std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> functions = Functions::getScope();
        // Classes::getScope();
        std::shared_ptr<MapValue> map = SHARE(MapValue);
        for (auto x : variables) map -> set(SHARE(StringValue, x.first), x.second);
        for (auto x : functions) {
            if (x.second.size() > 1) throw LogicException("Cannot import overloaded function");
            map -> set(SHARE(StringValue, x.first), x.second[0].second);
        }
        // for each
        Names::popScope();
        Names::setVariable(moduleName, SHARE(Import, map));
    } else Names::copyScope();
}

Statements ImportStatement::type() const {
    return Statements::ImportStatement;
}

ImportStatement::operator std::string() {
    std::string result = "import [";
    for (size_t i = 0; i < names.size(); ++i) {
        result += "'" + names[i] + "'";
        if (i < names.size() - 1) result += ", ";
    }
    result += "]" + (moduleName == "" ? "" : " as '" + moduleName + "'");
    return result;
}

void ImportStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}

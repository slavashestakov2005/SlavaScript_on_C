#include "integrationstatement.h"
#include "../Lib/names.h"
#include "../Value/integrationvalue.h"
#include "../Lib/filesystem.h"

using namespace SlavaScript::lang;

namespace{
    std::string replace_all(std::string str){
        std::string result;
        size_t pos = str.find("\n");
        int last = 0;
        while(pos != std::string::npos) {
            if (pos + 1 >= str.size() || str[pos + 1] != '\t') throw std::logic_error("Cannot used \\n with out \\t");
            result += str.substr(last, pos - last);
            result += "\n";
            last = pos + 2;
            pos = str.find("\n", last);
        }
        result += str.substr(last);
        return result;
    }
}

IntegrationStatement::IntegrationStatement(std::string lang, std::string name, std::string code) : lang(lang), name(name), code(code) {}

void IntegrationStatement::execute(){
    std::string fileBegin = "example_code";
    std::string fileEnd = "py";
    std::string filename = fileBegin + "." + fileEnd;
    FS::writeToCache(filename, replace_all(code));
    Names::setVariable(name, SHARE_2(IntegrationValue, fileBegin, fileEnd));
}

Statements IntegrationStatement::type() const{
    return Statements::IntegrationStatement;
}

IntegrationStatement::operator std::string(){
    return "##'" + lang + "' as '" + name + "' { " + code + "}";
}

void IntegrationStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

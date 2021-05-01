#include "integrationstatement.h"
#include "../Lib/variables.h"
#include "../Value/integrationvalue.h"
#include <fstream>
#include <exception>

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

void IntegrationStatement::execute(){
    std::string fileCount = "example_code";
    std::string fileEnd = "py";
    std::ofstream fout(fileCount + "." + fileEnd);
    fout << replace_all(code);
    fout.close();
    Variables::set(name, std::make_shared<IntegrationValue>(fileCount, fileEnd));
}

IntegrationStatement::operator std::string(){
    return "##'" + lang + "' as '" + name + "' { " + code + "}";
}

void IntegrationStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}

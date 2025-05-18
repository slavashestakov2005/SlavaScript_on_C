#include <Lib/names.h>
#include <Lib/userdefinedclass.h>
#include <Statement/classdeclarationsstatement.h>
#include <Statement/functiondefinestatement.h>


using namespace SlavaScript::lang;

ClassDeclarationsStatement::ClassDeclarationsStatement() : name("") {}

ClassDeclarationsStatement::ClassDeclarationsStatement(std::string name) : name(name) {}

void ClassDeclarationsStatement::addField(std::vector<std::string> v, Expression* expr) {
    fields.push_back({v, expr});
}

void ClassDeclarationsStatement::addMethod(FunctionDefineStatement* statement) {
    methods.push_back(statement);
}

std::string ClassDeclarationsStatement::get_name() {
    return name;
}

void ClassDeclarationsStatement::execute() {
    Names::setClass(name, SHARE(ClassValue, SHARE(UserDefinedClass, this)));
}

Statements ClassDeclarationsStatement::type() const {
    return Statements::ClassDeclarationsStatement;
}

ClassDeclarationsStatement::operator std::string() {
    std::string result = "class '" + name + "'{\n ";
    int i = 0;
    for (auto now : fields) {
        for (auto field : now.first) result += "'" + field + "' = ";
        result += std::string(*now.second);
        if (i < fields.size() - 1) result += ", ";
        ++i;
    }
    i = 0;
    for (FunctionDefineStatement* function : methods) {
        result += std::string(*function);
        if (i < methods.size() - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

ClassDeclarationsStatement::~ClassDeclarationsStatement() {
    for (size_t i = 0; i < methods.size(); ++i) {
        delete methods[i];
        methods[i] = nullptr;
    }
    for (size_t i = 0; i < fields.size(); ++i) {
        delete fields[i].second;
        fields[i].second = nullptr;
    }
}

void ClassDeclarationsStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}

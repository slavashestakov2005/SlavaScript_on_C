#include <Lib/names.h>
#include <Lib/userdefinedfunction.h>
#include <Statement/functiondefinestatement.h>


using namespace SlavaScript::lang;

FunctionDefineStatement::FunctionDefineStatement(std::string name, Arguments arguments, Statement* body) : name(name), arguments(arguments), body(body) {}

void FunctionDefineStatement::execute(bool set) {
    if (set) Names::setFunction(name, SHARE(UserDefinedFunction, arguments, body),
                   ArgumentsInfo(arguments.getRequiredCount(), arguments.size() - arguments.getRequiredCount() - arguments.getArrayCount(),
                                 arguments.getArrayCount()));
}

std::string FunctionDefineStatement::getName() {
    return name;
}

void FunctionDefineStatement::execute() {
    execute(false); // because FunctionAdder was doing execute(true)
}

Statements FunctionDefineStatement::type() const {
    return Statements::FunctionDefineStatement;
}

FunctionDefineStatement::operator std::string() {
    std::string result = "def '";
    result += name;
    result += "' (";
    for (int i = 0; i < arguments.size(); ++i) {
        result += std::string(arguments.get(i));
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ") ";
    if (body -> type() == Statements::ReturnStatement) result += " = ";
    result += std::string(*body);
    return result;
}

FunctionDefineStatement::~FunctionDefineStatement() {
    delete body;
    body = nullptr;
}

void FunctionDefineStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}

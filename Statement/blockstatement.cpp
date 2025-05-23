#include <Statement/blockstatement.h>


using namespace SlavaScript::lang;

BlockStatement::BlockStatement() {}

void BlockStatement::add(Statement* statement) {
    statements.push_back(statement);
}

void BlockStatement::execute() {
    for (size_t i = 0; i < statements.size(); ++i) {
        statements[i] -> execute();
    }
}

Statements BlockStatement::type() const {
    return Statements::BlockStatement;
}

BlockStatement::operator std::string() {
    std::string result = "{\n";
    for (size_t i = 0; i < statements.size(); ++i) {
        result += std::string(*statements[i]) + "\n";
    }
    result += "}";
    return result;
}

BlockStatement::~BlockStatement() {
    for (size_t i = 0; i < statements.size(); ++i) {
        delete statements[i];
        statements[i] = nullptr;
    }
}

void BlockStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}

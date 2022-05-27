#ifndef CLASSDECLARATIONSSTATEMENT_H_INCLUDED
#define CLASSDECLARATIONSSTATEMENT_H_INCLUDED

#include <vector>
#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class ClassDeclarationsStatement : public Statement{
    private:
        std::string name;
    public:
        std::vector<FunctionDefineStatement*> methods;
        std::vector<std::pair<std::vector<std::string>, Expression*>> fields;
        ClassDeclarationsStatement() : name("") { }
        ClassDeclarationsStatement(std::string name) : name(name) { }
        Statements type(){ return Statements::ClassDeclarationsStatement; }
        void addField(std::vector<std::string> v, Expression* expr);
        void addMethod(FunctionDefineStatement* statement);
        void execute();
        operator std::string();
        ~ClassDeclarationsStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // CLASSDECLARATIONSSTATEMENT_H_INCLUDED

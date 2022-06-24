#ifndef CLASSDECLARATIONSSTATEMENT_H_INCLUDED
#define CLASSDECLARATIONSSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"
#include <vector>

namespace SlavaScript::lang{
    class ClassDeclarationsStatement : public Statement{
    private:
        std::string name;
    public:
        std::vector<FunctionDefineStatement*> methods;
        std::vector<std::pair<std::vector<std::string>, Expression*>> fields;

        ClassDeclarationsStatement();
        ClassDeclarationsStatement(std::string name);

        void addField(std::vector<std::string> v, Expression* expr);
        void addMethod(FunctionDefineStatement* statement);
        std::string get_name();

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ClassDeclarationsStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // CLASSDECLARATIONSSTATEMENT_H_INCLUDED

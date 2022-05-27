#ifndef IMPORTSTATEMENT_H_INCLUDED
#define IMPORTSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Visitor/importadder.h"

namespace SlavaScript::lang{
    class ImportStatement : public Statement{
    private:
        std::vector<std::string> names;
        std::string moduleName;
    public:
        ImportStatement(std::vector<std::string> names, std::string moduleName) : names(names), moduleName(moduleName) {}
        Statements type(){ return Statements::ImportStatement; }
        /** @return  throw: UnknownModuleException*. */
        void execute();
        operator std::string();
        ~ImportStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend ImportAdder;
        friend compiler::CompilerVisitor;
    };
}

#endif // IMPORTSTATEMENT_H_INCLUDED

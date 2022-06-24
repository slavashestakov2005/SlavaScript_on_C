#ifndef IMPORTSTATEMENT_H_INCLUDED
#define IMPORTSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"
#include "../Visitor/importadder.h"

namespace SlavaScript::lang{
    class ImportStatement : public Statement{
    private:
        std::vector<std::string> names;
        std::string moduleName;
    public:
        ImportStatement(std::vector<std::string> names, std::string moduleName);

        /** @return  throw: UnknownModuleException*. */
        void execute() override;
        Statements type() const override;
        operator std::string() override;

        void accept(Visitor* visitor) override;
        friend Visitor;
        friend ImportAdder;
        friend compiler::CompilerVisitor;
    };
}

#endif // IMPORTSTATEMENT_H_INCLUDED

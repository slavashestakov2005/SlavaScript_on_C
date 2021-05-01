#ifndef INTEGRATIONSTATEMENT_H_INCLUDED
#define INTEGRATIONSTATEMENT_H_INCLUDED

#include "statement.h"

namespace SlavaScript{ namespace lang{
    class IntegrationStatement : public Statement{
    private:
        std::string lang, name, code;
    public:
        IntegrationStatement(std::string lang, std::string name, std::string code) : lang(lang), name(name), code(code) {}
        Statements type(){ return Statements::IntegrationStatement; }
        void execute();
        operator std::string();
        ~IntegrationStatement(){}
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // INTEGRATIONSTATEMENT_H_INCLUDED

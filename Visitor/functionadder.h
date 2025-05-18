#pragma once

#include <Visitor/visitor.h>


namespace SlavaScript::lang {
    class FunctionDefineStatement;

    class FunctionAdder : public Visitor {
    public:
        /** @return  throw: std::logic_error. */
        void visit(FunctionDefineStatement* v) override;
    };
}

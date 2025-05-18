#pragma once

#include <Visitor/visitor.h>


namespace SlavaScript::lang {
    class ImportAdder : public Visitor {
    public:
        void visit(ImportStatement* v) override;
    };
}

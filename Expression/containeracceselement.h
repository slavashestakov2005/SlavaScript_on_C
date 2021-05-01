#ifndef CONTAINERACCESELEMENT_H_INCLUDED
#define CONTAINERACCESELEMENT_H_INCLUDED

#include "expression.h"

namespace SlavaScript{ namespace lang{
    class ContainerAccessElement {
    private:
        bool dot;
    public:
        Expression* expression;
        ContainerAccessElement(Expression* expression, bool dot) : dot(dot), expression(expression) { }
        std::shared_ptr<Value> eval();
        bool isDot();
        operator std::string();
    };
}}

#endif // CONTAINERACCESELEMENT_H_INCLUDED

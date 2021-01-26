#ifndef VALUEEXPRESSION_H_INCLUDED
#define VALUEEXPRESSION_H_INCLUDED

#include "expression.h"
#include "../Value/arrayvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/boolvalue.h"
#include "../Value/functionvalue.h"
#include "../Value/mapvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/stringvalue.h"
#include "../Value/value.h"

namespace SlavaScript{ namespace lang{
    class ValueExpression : public Expression{
    public:
        Value* value;
        ValueExpression(std::string val){ value = new StringValue(val); }
        ValueExpression(ArrayValue val){ value = new ArrayValue(val); }
        ValueExpression(bool val){ value = new BoolValue(val); }
        ValueExpression(Function* val){ value = new FunctionValue(val); }
        ValueExpression(MapValue val){ value = new MapValue(val); }
        ValueExpression(Bignum val){ value = new NumberValue(val); }
        ValueExpression(NullValue null){ value = new NullValue(); }
        ValueExpression(Value* val);
        Expressions type(){ return Expressions::ValueExpression; }
        Value* eval();
        operator std::string();
        ~ValueExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // VALUEEXPRESSION_H_INCLUDED

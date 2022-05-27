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

namespace SlavaScript::lang{
    class ValueExpression : public Expression{
    public:
        std::shared_ptr<Value> value;
        ValueExpression(std::string val){ value = SHARE(StringValue, val); }
        ValueExpression(ArrayValue val){ value = SHARE(ArrayValue, val); }
        ValueExpression(bool val){ value = BoolValue::fromBool(val); }
        ValueExpression(Function* val){ value = SHARE(FunctionValue, val); }
        ValueExpression(MapValue val){ value = SHARE(MapValue, val); }
        ValueExpression(Bignum val){ value = SHARE(NumberValue, val); }
        ValueExpression(NullValue null){ value = SHARE(NullValue, ); }
        ValueExpression(Value* val);
        Expressions type(){ return Expressions::ValueExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~ValueExpression(){}
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // VALUEEXPRESSION_H_INCLUDED

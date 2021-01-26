#include "valueexpression.h"

using namespace SlavaScript::lang;

ValueExpression::ValueExpression(Value* val){
    if (val -> type() == Values::ARRAY) value = val;
    else if (val -> type() == Values::STRING) value = new StringValue(*(StringValue*)val);
    else if (val -> type() == Values::BOOL) value = new BoolValue(*(BoolValue*)val);
    else if (val -> type() == Values::FUNCTION) value = new FunctionValue(*(FunctionValue*)val);
    else if (val -> type() == Values::MAP) value = new MapValue(*(MapValue*)val);
    else if (val -> type() == Values::NUMBER) value = new NumberValue(*(NumberValue*)val);
    else if (val -> type() == Values::NULL_) value = NullValue::NULL_;
}

Value* ValueExpression::eval(){
    return value;
}

ValueExpression::operator std::string(){
    return std::string(*value);
}

ValueExpression::~ValueExpression(){
    delete value;
    value = nullptr;
}

void ValueExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

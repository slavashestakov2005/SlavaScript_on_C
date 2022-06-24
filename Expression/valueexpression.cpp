#include "valueexpression.h"

using namespace SlavaScript::lang;


ValueExpression::ValueExpression(Value* val){
    if (val -> type() == Values::ARRAY) value = SHARE(ArrayValue, *(ArrayValue*)val);
    else if (val -> type() == Values::STRING) value = SHARE(StringValue, *(StringValue*)val);
    else if (val -> type() == Values::BOOL) value = BoolValue::fromBool(val -> asBool());
    else if (val -> type() == Values::FUNCTION) value = SHARE(FunctionValue, *(FunctionValue*)val);
    else if (val -> type() == Values::MAP) value = SHARE(MapValue, *(MapValue*)val);
    else if (val -> type() == Values::NUMBER) value = SHARE(NumberValue, *(NumberValue*)val);
    else if (val -> type() == Values::NULL_) value = NullValue::NULL_;
}

std::shared_ptr<Value> ValueExpression::eval(){
    return value;
}
Expressions ValueExpression::type() const{
    return Expressions::ValueExpression;
}

ValueExpression::operator std::string(){
    return std::string(*value);
}

ValueExpression::~ValueExpression() {}

void ValueExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

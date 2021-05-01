#include "valueexpression.h"

using namespace SlavaScript::lang;

ValueExpression::ValueExpression(Value* val){
    if (val -> type() == Values::ARRAY) value = std::make_shared<ArrayValue>(*(ArrayValue*)val);
    else if (val -> type() == Values::STRING) value = std::make_shared<StringValue>(*(StringValue*)val);
    else if (val -> type() == Values::BOOL) value = std::make_shared<BoolValue>((BoolValue*)val);
    else if (val -> type() == Values::FUNCTION) value = std::make_shared<FunctionValue>(*(FunctionValue*)val);
    else if (val -> type() == Values::MAP) value = std::make_shared<MapValue>(*(MapValue*)val);
    else if (val -> type() == Values::NUMBER) value = std::make_shared<NumberValue>(*(NumberValue*)val);
    else if (val -> type() == Values::NULL_) value = NullValue::NULL_;
}

std::shared_ptr<Value> ValueExpression::eval(){
    return value;
}

ValueExpression::operator std::string(){
    return std::string(*value);
}

ValueExpression::~ValueExpression(){
    //delete value;
    //value = nullptr;
}

void ValueExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

#include "stringvalue.h"
#include <sstream>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Value/arrayvalue.h"
#include "../Lib/function.h"
#include "../Value/numbervalue.h"
#include "../Value/functionvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::UnknownPropertyException;
using SlavaScript::exceptions::TypeException;

namespace{
    class Trim : public Function {
    private:
        std::string str;
    public:
        Trim(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            return new StringValue("This is trimmed for : " + str + " : end");
        }
    };

    class To_upper : public Function {
    private:
        std::string str;
    public:
        To_upper(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            for(char& x : str) x = toupper(x);
            return new StringValue(str);
        }
    };

    class To_lower : public Function {
    private:
        std::string str;
    public:
        To_lower(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            for(char& x : str) x = tolower(x);
            return new StringValue(str);
        }
    };

    class Chars : public Function {
    private:
        std::string str;
    public:
        Chars(std::string str) : str(str) {}
        Value* execute(std::vector<Value*> values){
            if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
            std::vector<Value*> vec;
            for(auto x : str){
                std::string s;
                s += x;
                vec.push_back(new StringValue(s));
            }
            return new ArrayValue(vec);
        }
    };
}

int StringValue::size(){
    return value.size();
}

void StringValue::set(int index, Value* val){
    value = value.substr(0, index) + val -> asString() + value.substr(index + 1);
}

Value* StringValue::accessDot(Value* property){
    std::string prop = property -> asString();
    if (prop == "length") return new NumberValue(size());
    if (prop == "trim") return new FunctionValue(new Trim(value));
    if (prop == "to_upper") return new FunctionValue(new To_upper(value));
    if (prop == "to_lower") return new FunctionValue(new To_lower(value));
    if (prop == "chars") return new FunctionValue(new Chars(value));
    throw new UnknownPropertyException(prop);
}

Value* StringValue::accessBracket(Value* property){
    std::string s;
    s += value[(int) property -> asDouble()];
    return new StringValue(s);
}

double StringValue::asDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw new TypeException("Cannot cast string to number");
    }
}

std::string StringValue::asString(){
    return value;
}

bool StringValue::asBool(){
    throw new TypeException("Cannot cast string to bool");
}

Bignum StringValue::asBignum(){
    try{
        return Bignum(value);
    }catch(...){
        throw new TypeException("Cannot cast string to number");
    }
}

Values StringValue::type() const{
    return Values::STRING;
}

StringValue::operator std::string(){
    return asString();
};

bool SlavaScript::lang::operator==(StringValue const& a, StringValue const& b){
    return a.value == b.value;
}

bool SlavaScript::lang::operator!=(StringValue const& a, StringValue const& b){
    return a.value != b.value;
}

bool SlavaScript::lang::operator<(StringValue const& a, StringValue const& b){
    return a.value < b.value;
}

bool SlavaScript::lang::operator<=(StringValue const& a, StringValue const& b){
    return a.value <= b.value;
}

bool SlavaScript::lang::operator>(StringValue const& a, StringValue const& b){
    return a.value > b.value;
}

bool SlavaScript::lang::operator>=(StringValue const& a, StringValue const& b){
    return a.value >= b.value;
}

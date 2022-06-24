#include "stringvalue.h"
#include "../Exception/exceptions.h"
#include "../Lib/classmethod.h"
#include "../Lib/utils.h"
#include "arrayvalue.h"
#include "numbervalue.h"
#include <algorithm>
#include <sstream>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;
using SlavaScript::exceptions::UnknownPropertyException;


namespace{
    CLASS_METHOD(Trim, StringValue::container_type)
        argsCount(0, values.size());
        std::string ans;
        for(int i = 0; i < instance.size(); ++i){
            if (instance[i] != ' ' && instance[i] != '\t' && instance[i] != '\n' || ans.size()) ans += instance[i];
        }
        instance = "";
        for(int i = ans.size() - 1; i > -1; --i){
            if (ans[i] != ' ' && ans[i] != '\t' && ans[i] != '\n' || instance.size()) instance += ans[i];
        }
        reverse(instance.begin(), instance.end());
        SH_RET(StringValue, instance);
    CME

    CLASS_METHOD(To_upper, StringValue::container_type)
        argsCount(0, values.size());
        for(char& x : instance) x = toupper(x);
        SH_RET(StringValue, instance);
    CME

    CLASS_METHOD(To_lower, StringValue::container_type)
        argsCount(0, values.size());
        for(char& x : instance) x = tolower(x);
        SH_RET(StringValue, instance);
    CME

    CLASS_METHOD(Chars, StringValue::container_type)
        argsCount(0, values.size());
        std::vector<std::shared_ptr<Value>> vec;
        for(auto x : instance){
            std::string s;
            s += x;
            vec.push_back(SHARE(StringValue, s));
        }
        SH_RET(ArrayValue, vec);
    CME

    CLASS_METHOD(Find, StringValue::container_type)
        argsCount(1, 2, values.size());
        argType(Values::STRING, values[0]);
        if (values.size() == 2) argType(Values::NUMBER, values[1]);
        std::string str2 = values[0] -> asString();
        int position = ((values.size() == 2) ? (int)values[1] -> asDouble() : 0);
        size_t x = instance.find(str2, position);
        if (x == std::string::npos) return NumberValue::M_ONE;
        SH_RET(NumberValue, x);
    CME

    CLASS_METHOD(Join, StringValue::container_type)
        argsCountLtEq(1, values.size());
        std::string ans;
        if (values.size() == 1 && values[0] -> type() == Values::ARRAY){
            std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, values[0]);
            for(int i = 0; i < arr -> size(); ++i){
                ans += arr -> get(i) -> asString();
                if (i < arr -> size() - 1) ans += instance;
            }
        }
        else{
            for(int i = 0; i < values.size(); ++i){
                ans += values[i] -> asString();
                if (i < values.size() - 1) ans += instance;
            }
        }
        SH_RET(StringValue, ans);
    CME

    CLASS_METHOD(Replace, StringValue::container_type)
        argsCount(2, values.size());
        argType(Values::STRING, values[0]);
        argType(Values::STRING, values[1]);
        std::string start = values[0] -> asString(), finish = values[1] -> asString(), result;
        /// using regex
        //std::regex rx(start.c_str());
        //return new StringValue(std::regex_replace(instance, rx, finish));
        int last = 0;
        size_t pos = instance.find(start);
        while(pos != std::string::npos) {
            result += instance.substr(last, pos - last);
            result += finish;
            last = pos + start.size();
            pos = instance.find(start, last);
        }
        result += instance.substr(last);
        SH_RET(StringValue, result);
    CME

    CLASS_METHOD(ReplaceFirst, StringValue::container_type)
        argsCount(2, values.size());
        argType(Values::STRING, values[0]);
        argType(Values::STRING, values[1]);
        std::string start = values[0] -> asString(), finish = values[1] -> asString(), result;
        size_t pos = instance.find(start);
        if (pos != std::string::npos) result = instance.substr(0, pos) + finish + instance.substr(pos + start.size());
        else result = instance;
        SH_RET(StringValue, result);
    CME

    CLASS_METHOD(Rfind, StringValue::container_type)
        argsCount(1, 2, values.size());
        argType(Values::STRING, values[0]);
        if (values.size() == 2) argType(Values::NUMBER, values[1]);
        std::string str2 = values[0] -> asString();
        int position = ((values.size() == 2) ? (int)values[1] -> asDouble() : 0);
        size_t x = instance.rfind(str2, position);
        if (x == std::string::npos) return NumberValue::M_ONE;
        SH_RET(NumberValue, x);
    CME

    CLASS_METHOD(Split, StringValue::container_type)
        argsCount({0, 1, 2}, values.size());
        if (values.size() > 0) argType(Values::STRING, values[0]);
        if (values.size() > 1) argType(Values::NUMBER, values[1]);
        std::string reg = values.size() ? values[0] -> asString() : " ";
        int limit = (values.size() > 1) ? (int)values[1] -> asDouble() - 1 : -1;
        if (limit <= 0) limit = -1;
        std::vector<std::shared_ptr<Value>> val;
        int pos = instance.find(reg), last = 0;
        std::string t;
        while(pos != std::string::npos){
            std::string temp;
            for(int i = last; i < pos; ++i) temp += instance[i];
            if (limit == -1 || val.size() < limit) val.push_back(SHARE(StringValue, temp));
            else break;
            last = pos + 1;
            pos = instance.find(reg, last);
        }
        for(int i = last; i < instance.size(); ++i) t += instance[i];
        if (t != "") val.push_back(SHARE(StringValue, t));
        SH_RET(ArrayValue, val);
    CME

    CLASS_METHOD(Substring, StringValue::container_type)
        argsCount(1, 2, values.size());
        argType(Values::NUMBER, values[0]);
        if (values.size() == 2) argType(Values::NUMBER, values[1]);
        std::string ans;
        int start = values[0] -> asDouble();
        if (values.size() == 1) ans = instance.substr(start);
        else{
            int finish = values[1] -> asDouble();
            ans = instance.substr(start, finish - start);
        }
        SH_RET(StringValue, ans);
    CME
}


StringValue::StringValue(StringValue::container_type value) : value(value) {}


void StringValue::set(int index, std::shared_ptr<Value> val){
    value = value.substr(0, index) + val -> asString() + value.substr(index + 1);
}


std::shared_ptr<Value> StringValue::copy(){
    return SHARE(StringValue, value);
}

double StringValue::asDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw CastException(Values::STRING, Values::NUMBER);
    }
}

std::string StringValue::asString(){
    return value;
}

bool StringValue::asBool(){
    throw CastException(Values::STRING, Values::BOOL);
}

Bignum StringValue::asBignum(){
    try{
        return Bignum(value);
    }catch(...){
        throw CastException(Values::STRING, Values::NUMBER);
    }
}

Values StringValue::type() const{
    return Values::STRING;
}

StringValue::operator std::string(){
    return asString();
};

std::shared_ptr<Value> StringValue::getDot(std::shared_ptr<Value> property){
    std::string prop = property -> asString();
    if (prop == "length") SH_RET(NumberValue, size());
    ADD_METHOD("trim", Trim, value);
    ADD_METHOD("to_upper", To_upper, value);
    ADD_METHOD("to_lower", To_lower, value);
    ADD_METHOD("chars", Chars, value);
    ADD_METHOD("find", Find, value);
    ADD_METHOD("join", Join, value);
    ADD_METHOD("replace", Replace, value);
    ADD_METHOD("replace_first", ReplaceFirst, value);
    ADD_METHOD("rfind", Rfind, value);
    ADD_METHOD("split", Split, value);
    ADD_METHOD("substring", Substring, value);
    throw UnknownPropertyException(prop);
}

std::shared_ptr<Value> StringValue::getBracket(std::shared_ptr<Value> property){
    std::string s;
    s += value[(int) property -> asDouble()];
    return SHARE(StringValue, s);
}

void StringValue::setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    int stringIndex = (int) key -> asDouble();
    set(stringIndex, value);
}


int StringValue::size() const{
    return value.size();
}

std::string::iterator StringValue::begin(){
    return value.begin();
}

std::string::iterator StringValue::end(){
    return value.end();
}


namespace SlavaScript::lang{
    CMP(StringValue){
        RCHECK(a.value, b.value);
    }

    DEF_CMP(StringValue)
}

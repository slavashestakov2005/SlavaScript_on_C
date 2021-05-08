#include "stringvalue.h"
#include <sstream>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Value/arrayvalue.h"
#include "../Lib/function.h"
#include "../Value/numbervalue.h"
#include "../Value/functionvalue.h"
#include <algorithm>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::UnknownPropertyException;
using SlavaScript::exceptions::TypeException;

namespace{
    CLASS_MODULE_FUNCTION_(Trim, std::string, str)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        std::string ans;
        for(int i = 0; i < str.size(); ++i){
            if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' || ans.size()) ans += str[i];
        }
        str = "";
        for(int i = ans.size() - 1; i > -1; --i){
            if (ans[i] != ' ' && ans[i] != '\t' && ans[i] != '\n' || str.size()) str += ans[i];
        }
        reverse(str.begin(), str.end());
        SH_RET(StringValue, str);
    CMFE

    CLASS_MODULE_FUNCTION_(To_upper, std::string, str)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        for(char& x : str) x = toupper(x);
        SH_RET(StringValue, str);
    CMFE

    CLASS_MODULE_FUNCTION_(To_lower, std::string, str)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        for(char& x : str) x = tolower(x);
        SH_RET(StringValue, str);
    CMFE

    CLASS_MODULE_FUNCTION_(Chars, std::string, str)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        std::vector<std::shared_ptr<Value>> vec;
        for(auto x : str){
            std::string s;
            s += x;
            vec.push_back(SHARE(StringValue, s));
        }
        SH_RET(ArrayValue, vec);
    CMFE

    CLASS_MODULE_FUNCTION_(Find, std::string, str)
        if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
        if (values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
        if (values.size() == 2 && values[1] -> type() != Values::NUMBER) throw new TypeException("Number expected in second argument");
        std::string str2 = values[0] -> asString();
        int position = ((values.size() == 2) ? (int)values[1] -> asDouble() : 0);
        size_t x = str.find(str2, position);
        if (x == std::string::npos) return NumberValue::M_ONE;
        SH_RET(NumberValue, x);
    CMFE

    CLASS_MODULE_FUNCTION_(Join, std::string, delimiter)
        if (values.size() < 1) throw new ArgumentsMismatchException("At least one argument expected");
        std::string ans;
        if (values.size() == 1 && values[0] -> type() == Values::ARRAY){
            std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, values[0]);
            for(int i = 0; i < arr -> size(); ++i){
                ans += arr -> get(i) -> asString();
                if (i < arr -> size() - 1) ans += delimiter;
            }
        }
        else{
            for(int i = 0; i < values.size(); ++i){
                ans += values[i] -> asString();
                if (i < values.size() - 1) ans += delimiter;
            }
        }
        SH_RET(StringValue, ans);
    CMFE

    CLASS_MODULE_FUNCTION_(Replace, std::string, str)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
        if (values[1] -> type() != Values::STRING) throw new TypeException("String expected in second argument");
        std::string start = values[0] -> asString(), finish = values[1] -> asString(), result;
        /// using regex
        //std::regex rx(start.c_str());
        //return new StringValue(std::regex_replace(str, rx, finish));
        int last = 0;
        size_t pos = str.find(start);
        while(pos != std::string::npos) {
            result += str.substr(last, pos - last);
            result += finish;
            last = pos + start.size();
            pos = str.find(start, last);
        }
        result += str.substr(last);
        SH_RET(StringValue, result);
    CMFE

    CLASS_MODULE_FUNCTION_(ReplaceFirst, std::string, str)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
        if (values[1] -> type() != Values::STRING) throw new TypeException("String expected in second argument");
        std::string start = values[0] -> asString(), finish = values[1] -> asString(), result;
        size_t pos = str.find(start);
        if (pos != std::string::npos) result = str.substr(0, pos) + finish + str.substr(pos + start.size());
        else result = str;
        SH_RET(StringValue, result);
    CMFE

    CLASS_MODULE_FUNCTION_(Rfind, std::string, str)
        if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
        if (values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
        if (values.size() == 2 && values[1] -> type() != Values::NUMBER) throw new TypeException("Number expected in second argument");
        std::string str2 = values[0] -> asString();
        int position = ((values.size() == 2) ? (int)values[1] -> asDouble() : 0);
        size_t x = str.rfind(str2, position);
        if (x == std::string::npos) return NumberValue::M_ONE;
        SH_RET(NumberValue, x);
    CMFE

    CLASS_MODULE_FUNCTION_(Split, std::string, str)
        if (values.size() > 2) throw new ArgumentsMismatchException("Two and less arguments expected");
        if (values.size() > 0 && values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
        if (values.size() > 1 && values[1] -> type() != Values::NUMBER) throw new TypeException("Number expected in second argument");
        std::string reg = values.size() ? values[0] -> asString() : " ";
        int limit = (values.size() > 1) ? (int)values[1] -> asDouble() - 1 : -1;
        if (limit <= 0) limit = -1;
        std::vector<std::shared_ptr<Value>> val;
        int pos = str.find(reg), last = 0;
        std::string t;
        while(pos != std::string::npos){
            std::string temp;
            for(int i = last; i < pos; ++i) temp += str[i];
            if (limit == -1 || val.size() < limit) val.push_back(SHARE(StringValue, temp));
            else break;
            last = pos + 1;
            pos = str.find(reg, last);
        }
        for(int i = last; i < str.size(); ++i) t += str[i];
        if (t != "") val.push_back(SHARE(StringValue, t));
        SH_RET(ArrayValue, val);
    CMFE

    CLASS_MODULE_FUNCTION_(Substring, std::string, str)
        if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
        if (values[0] -> type() != Values::NUMBER) throw new TypeException("Number expected in first argument");
        if (values.size() == 2 && values[1] -> type() != Values::NUMBER) throw new TypeException("Number expected in second argument");
        std::string ans;
        int start = values[0] -> asDouble();
        if (values.size() == 1) ans = str.substr(start);
        else{
            int finish = values[1] -> asDouble();
            ans = str.substr(start, finish - start);
        }
        SH_RET(StringValue, ans);
    CMFE
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

void StringValue::set(int index, std::shared_ptr<Value> val){
    value = value.substr(0, index) + val -> asString() + value.substr(index + 1);
}

std::shared_ptr<Value> StringValue::accessDot(std::shared_ptr<Value> property){
    std::string prop = property -> asString();
    if (prop == "length") SH_RET(NumberValue, size());
    if (prop == "trim") SH_RET(FunctionValue, new Trim(value));
    if (prop == "to_upper") SH_RET(FunctionValue, new To_upper(value));
    if (prop == "to_lower") SH_RET(FunctionValue, new To_lower(value));
    if (prop == "chars") SH_RET(FunctionValue, new Chars(value));
    if (prop == "find") SH_RET(FunctionValue, new Find(value));
    if (prop == "join") SH_RET(FunctionValue, new Join(value));
    if (prop == "replace") SH_RET(FunctionValue, new Replace(value));
    if (prop == "replace_first") SH_RET(FunctionValue, new ReplaceFirst(value));
    if (prop == "rfind") SH_RET(FunctionValue, new Rfind(value));
    if (prop == "split") SH_RET(FunctionValue, new Split(value));
    if (prop == "substring") SH_RET(FunctionValue, new Substring(value));
    throw new UnknownPropertyException(prop);
}

std::shared_ptr<Value> StringValue::accessBracket(std::shared_ptr<Value> property){
    std::string s;
    s += value[(int) property -> asDouble()];
    return SHARE(StringValue, s);
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
    return "\"" + asString() + "\"";
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

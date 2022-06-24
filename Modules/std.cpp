#include "std.h"
#include "../Exception/exceptions.h"
#include "../Lib/functions.h"
#include "../Lib/utils.h"
#include "../Lib/variables.h"
#include "../Run/path.h"
#include "../Value/arrayvalue.h"
#include "../Value/mapvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include <iostream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::std_f;
using SlavaScript::modules::Std;
using SlavaScript::exceptions::MathException;


namespace SlavaScript::modules::std_out{

    double modulo(double a, double b){
        if (a < 0) return std::max(b, -b) - modulo(-a, b);
        long long k = a / b;
        double res = a - k * b;
        return res;
    }

    std::shared_ptr<ArrayValue> createArray(std::vector<std::shared_ptr<Value>> values, int index){
        int size = int(values[index] -> asDouble());
        int last = values.size() - 1;
        std::shared_ptr<ArrayValue> arr = SHARE(ArrayValue, size);
        if (index == last){
            for(int i = 0; i < size; ++i){
                arr -> set(i, NullValue::NULL_);
            }
        }
        else if(index < last){
            for(int i = 0; i < size; ++i){
                arr -> set(i, createArray(values, index + 1));
            }
        }
        return arr;
    }
}


namespace SlavaScript::modules::std_f{
    CREATE_FUNCTION(array_combine)
        argsCount(2, values.size());
        argType(Values::ARRAY, values[0]);
        argType(Values::ARRAY, values[1]);
        std::shared_ptr<ArrayValue> keys = CAST(ArrayValue, values[0]), value = CAST(ArrayValue, values[1]);
        int len = std::min(keys -> size(), value -> size());
        std::shared_ptr<MapValue> map = SHARE(MapValue, );
        for(int i = 0; i < len; ++i) map -> set(keys -> get(i), value -> get(i));
        return map;
    FE

    CREATE_FUNCTION(echo)
        for(auto value : values) std::cout << value -> asString();
        std::cout << std::endl;
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(len)
        argsCount(1, values.size());
        int length;
        switch(values[0] -> type()){
            case Values::ARRAY : length = CAST(ArrayValue, values[0]) -> size(); break;
            case Values::MAP : length = CAST(MapValue, values[0]) -> size(); break;
            case Values::STRING : length = CAST(StringValue, values[0]) -> size(); break;
            default : length = 0; break;
        }
        SH_RET(NumberValue, length);
    FE

    CREATE_FUNCTION(new_array)
        return std_out::createArray(values, 0);
    FE

    CREATE_FUNCTION(parse_number)
        argsCount(1, 2, values.size());
        int radix = values.size() == 2 ? values[1] -> asDouble() : 10;
        Bignum power = 1, ans = 0;
        std::string parsed = values[0] -> asString();
        for(int i = parsed.size() - 1; i > -1; --i){
            int current;
            if (parsed[i] >= '0' && parsed[i] <= '9') current = parsed[i] - '0';
            else current = tolower(parsed[i]) - 'a';
            if (current < 0 || current >= radix) throw MathException("Bad radix for parse string");
            ans += current * power;
            power *= radix;
        }
        SH_RET(NumberValue, ans);
    FE

    CREATE_FUNCTION(rand)
        argsCount({0, 1, 2}, values.size());
        int siz = values.size();
        double random = 1. * std::rand() / (RAND_MAX + 1), result;
        switch(siz){
            case (0) : result = random; break;
            case (1) : result = random * values[0] -> asDouble(); break;
            case (2) : {
                double start = std::min(values[0] -> asDouble(), values[1] -> asDouble());
                double finish = std::max(values[0] -> asDouble(), values[1] -> asDouble());
                result = start + (finish - start) * random;
                break;
            }
        }
        SH_RET(NumberValue, result);
    FE

    CREATE_FUNCTION(sleep)
        argsCount(1, values.size());
        argType(Values::NUMBER, values[0]);
        long long start = clock(), finish = clock();
        double tim = values[0] -> asDouble();
        while(finish - start < tim) finish = clock();
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(time)
        argsCount(0, values.size());
        SH_RET(NumberValue, clock());
    FE

    CREATE_FUNCTION(to_char)
        argsCount(1, values.size());
        std::string str;
        str += char(values[0] -> asDouble());
        SH_RET(StringValue, str);
    FE

    CREATE_FUNCTION(to_hex_string)
        argsCount(1, values.size());
        argType(Values::NUMBER, values[0]);
        long long value = values[0] -> asDouble();
        std::string ans;
        while(value){
            int current = value % 16;
            ans += current < 10 ? '0' + current : 'a' + current - 10;
            value /= 16;
        }
        reverse(ans.begin(), ans.end());
        SH_RET(StringValue, ans);
    FE
}

void Std::initConstants(){
    Variables::set("ARGS", Path::getCommandArguments());
}

void Std::initFunctions(){
    srand(std::time(0));
    std::rand();
    BINARY_F(array_combine)
    INF_F(echo)
    UNARY_F(len)
    INF_F(new_array)
    INFO_F(parse_number, ArgumentsInfo(1, 1))
    INFO_F_(std_f, rand, ArgumentsInfo(0, 2))
    UNARY_F(sleep)
    WITHOUT_F_(std_f, time)
    UNARY_F(to_char)
    UNARY_F(to_hex_string)
}

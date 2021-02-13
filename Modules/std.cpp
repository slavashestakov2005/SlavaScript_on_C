#include "std.h"
#include "../Lib/function.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/arrayvalue.h"
#include "../Value/functionvalue.h"
#include "../Value/mapvalue.h"
#include "../Value/stringvalue.h"
#include "../Lib/userdefinedfunction.h"
#include "../Expression/valueexpression.h"
#include <iostream>
#include <vector>
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/mathexception.h"
#include "../Exception/typeexception.h"
#include "../Run/path.h"
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::std_f;
using SlavaScript::modules::Std;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::MathException;

namespace SlavaScript{ namespace modules{ namespace std_out{

    double modulo(double a, double b){
        if (a < 0) return std::max(b, -b) - modulo(-a, b);
        long long k = a / b;
        double res = a - k * b;
        return res;
    }

    bool comparator(Value* a, Value* b){
        return (*a) < (*b);
    }

    ArrayValue* createArray(std::vector<Value*> values, int index){
        int size = int(values[index] -> asDouble());
        int last = values.size() - 1;
        ArrayValue* arr = new ArrayValue(size);
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
}}}

namespace SlavaScript{ namespace modules{ namespace std_f{
    Function* array_combine = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
        if (values[1] -> type() != Values::ARRAY) throw new TypeException("Array expected in second argument");
        ArrayValue* keys = (ArrayValue*)values[0], *value = (ArrayValue*)values[1];
        int len = std::min(keys -> size(), value -> size());
        MapValue* map = new MapValue(len);
        for(int i = 0; i < len; ++i) map -> set(keys -> get(i), value -> get(i));
        return map;
    });

    Function* echo = new FunctionModule([](std::vector<Value*> values) -> Value*{
        for(Value* value : values) std::cout << value -> asString();
        std::cout << std::endl;
        return NullValue::NULL_;
    });

    Function* len = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        int length;
        switch(values[0] -> type()){
            case Values::ARRAY : length = ((ArrayValue*)values[0]) -> size(); break;
            case Values::MAP : length = ((MapValue*)values[0]) -> size(); break;
            case Values::STRING : length = ((StringValue*)values[0]) -> size(); break;
            case Values::FUNCTION :{
                if (((FunctionValue*)values[0]) -> getFunction() -> type) length = ((UserDefinedFunction*)(((FunctionValue*)values[0]) -> getFunction())) -> getArgsCount();
                else length = 0;
                break;
            }
            default : length = 0; break;
        }
        return new NumberValue(length);
    });

    Function* map_key_exists = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[0] -> type() != Values::MAP) throw new TypeException("Map expected in first argument");
        MapValue* map = (MapValue*)values[0];
        return new BoolValue(map -> containsKey(values[1]));
    });

    Function* map_keys = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        if (values[0] -> type() != Values::MAP) throw new TypeException("Map expected in first argument");
        MapValue* map = (MapValue*)values[0];
        std::vector<Value*> keys;
        int siz = map -> size();
        auto iter = map -> begin();
        for(int i = 0; i < siz; ++i, ++iter) keys.push_back(iter -> first);
        return new ArrayValue(keys);
    });

    Function* map_values = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        if (values[0] -> type() != Values::MAP) throw new TypeException("Map expected in first argument");
        MapValue* map = (MapValue*)values[0];
        std::vector<Value*> keys;
        int siz = map -> size();
        auto iter = map -> begin();
        for(int i = 0; i < siz; ++i, ++iter) keys.push_back(iter -> second);
        return new ArrayValue(keys);
    });

    Function* new_array = new FunctionModule([](std::vector<Value*> values) -> Value*{
        return std_out::createArray(values, 0);
    });

    Function* parse_number = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
        int radix = values.size() == 2 ? values[1] -> asDouble() : 10;
        Bignum power = 1, ans = 0;
        std::string parsed = values[0] -> asString();
        for(int i = parsed.size() - 1; i > -1; --i){
            int current;
            if (parsed[i] >= '0' && parsed[i] <= '9') current = parsed[i] - '0';
            else current = tolower(parsed[i]) - 'a';
            if (current < 0 || current >= radix) throw new MathException("Bad radix for parse string");
            ans += current * power;
            power *= radix;
        }
        return new NumberValue(ans);
    });

    Function* rand = new FunctionModule([](std::vector<Value*> values) -> Value*{
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
            default : throw new ArgumentsMismatchException("Fewer arguments expected");
        }
        return new NumberValue(result);
    });

    Function* sleep = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        if (values[0] -> type() != Values::NUMBER) throw new TypeException("Number expected in first argument");
        long long start = clock(), finish = clock();
        double tim = values[0] -> asDouble();
        while(finish - start < tim) finish = clock();
        return NullValue::NULL_;
    });

    Function* sort = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() < 1 || values.size() > 2) throw new ArgumentsMismatchException("One or two arguments expected");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
        ArrayValue* arr = (ArrayValue*)values[0];
        if (values.size() == 1) std::sort(arr -> begin(), arr -> end(), std_out::comparator);
        if (values.size() == 2){
            if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
            Function* func = ((FunctionValue*)values[1]) -> getFunction();
            std::sort(arr -> begin(), arr -> end(), [func](Value* l, Value* r) -> bool { return std_out::comparator(func -> execute({l}), func -> execute({r})); });
        }
        return arr;
    });

    Function* time = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
        return new NumberValue(clock());
    });

    Function* to_char = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        std::string str;
        str += char(values[0] -> asDouble());
        return new StringValue(str);
    });

    Function* to_hex_string = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        if (values[0] -> type() != Values::NUMBER) throw new TypeException("Number expected in first argument");
        long long value = values[0] -> asDouble();
        std::string ans;
        while(value){
            int current = value % 16;
            ans += current < 10 ? '0' + current : 'a' + current - 10;
            value /= 16;
        }
        reverse(ans.begin(), ans.end());
        return new StringValue(ans);
    });
}}}

void Std::initConstants(){
    Variables::set("ARGS", Path::getCommandArguments());
}

void Std::initFunctions(){
    srand(std::time(0));
    std::rand();
    Functions::set("array_combine", array_combine);
    Functions::set("echo", echo);
    Functions::set("len", len);
    Functions::set("map_key_exists", map_key_exists);
    Functions::set("map_keys", map_keys);
    Functions::set("map_values", map_values);
    Functions::set("new_array", new_array);
    Functions::set("parse_number", parse_number);
    Functions::set("rand", std_f::rand);
    Functions::set("sleep", sleep);
    Functions::set("sort", sort);
    Functions::set("time", std_f::time);
    Functions::set("to_char", to_char);
    Functions::set("to_hex_string", to_hex_string);
}

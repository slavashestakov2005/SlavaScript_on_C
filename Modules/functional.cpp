#include "functional.h"
#include "../Lib/functions.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Value/functionvalue.h"
#include "../Value/arrayvalue.h"
#include "../Value/mapvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include <algorithm>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::functional_f;
using SlavaScript::modules::Functional;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::TypeException;

namespace SlavaScript{ namespace modules{ namespace functional_out{
    bool comparator(Value* a, Value* b){
        return (*a) < (*b);
    }

    Value* filterArray(ArrayValue* arr, Function* consumer){
        int size = arr -> size();
        std::vector<Value*> value;
        for(int i = 0; i < size; ++i){
            std::vector<Value*> temp;
            temp.push_back(arr -> get(i));
            if (consumer -> execute(temp) -> asBool()) value.push_back(arr -> get(i));
        }
        return new ArrayValue(value);
    }

    Value* filterMap(MapValue* map, Function* consumer){
        int i = 0;
        MapValue* value;
        auto iter = map -> begin();
        while (i < map -> size()){
            std::vector<Value*> args = { iter -> first, iter -> second };
            if (consumer -> execute(args)) value -> set(iter -> first, iter -> second);
            ++iter;
            ++i;
        }
        return value;
    }

    Value* FlatmapArray(ArrayValue* arr, Function* mapper){
        int siz = arr -> size();
        std::vector<Value*> values;
        for(int i = 0; i < siz; ++i){
            std::vector<Value*> temp = { arr -> get(i) };
            Value* inner = mapper -> execute(temp);
            if (inner -> type() != Values::ARRAY) throw new TypeException("Array expected " + std::string(*inner));
            ArrayValue* valArr = (ArrayValue*) inner;
            for(int i = 0; i < valArr -> size(); ++i){
                values.push_back(valArr -> get(i));
            }
        }
        return new ArrayValue(values);
    }

    Value* mapArray(ArrayValue* arr, Function* consumer){
        int size = arr -> size();
        std::vector<Value*> value;
        for(int i = 0; i < size; ++i){
            std::vector<Value*> temp;
            temp.push_back(arr -> get(i));
            value.push_back(consumer -> execute(temp));
        }
        return new ArrayValue(value);
    }

    Value* mapMap(MapValue* map, Function* consumer, Function* consumer2){
        int i = 0;
        MapValue* value;
        auto iter = map -> begin();
        while (i < map -> size()){
            std::vector<Value*> args1 = { iter -> first};
            std::vector<Value*> args2 = { iter -> second};
            value -> set(consumer -> execute(args1), consumer2 -> execute(args2));
            ++iter;
            ++i;
        }
        return value;
    }
}}}

namespace SlavaScript{ namespace modules{ namespace functional_f{
    Function* chain = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() < 3) throw new ArgumentsMismatchException("3 and least arguments expected");
        Value* result = values[0];
        for(int i = 1; i < values.size(); i += 2){
            if (values[i] -> type() != Values::FUNCTION) throw new TypeException(std::string(*values[i]) + " is not a function");
            Function* function = ((FunctionValue*)values[i]) -> getFunction();
            result = function -> execute({result, values[i + 1]});
        }
        return result;
    });

    Function* combine = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() < 1) throw new ArgumentsMismatchException("At least one arg expected");
        Function* result = nullptr;
        for(Value* arg : values){
            if (arg -> type() != Values::FUNCTION){
                throw new TypeException(std::string(*arg) + " is not a function");
            }
            Function* current = result;
            Function* next = ((FunctionValue*) arg) -> getFunction();
            result = new FunctionModule([current, next](std::vector<Value*> values) -> Value*{
                if (current == nullptr) return next -> execute(values);
                return next -> execute({current -> execute(values)});
            });
        }
        return new FunctionValue(result);
    });

    Function* drop_while = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        Function* function = ((FunctionValue*) values[1]) -> getFunction();
        ArrayValue* array = (ArrayValue*) values[0];
        int skipCount = 0;
        for(int i = 0; i < array -> size(); ++i){
            Value* value = array -> get(i);
            std::vector<Value*> vec = { value };
            if (function -> execute(vec) -> asBool()) ++skipCount;
            else break;
        }
        std::vector<Value*> vec;
        for(int i = skipCount; i < array -> size(); ++i){
            vec.push_back(array -> get(i));
        }
        return new ArrayValue(vec);
    });

    Function* filter = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        Value* container = values[0];
        Function* consumer = ((FunctionValue*) values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) return functional_out::filterArray((ArrayValue*) container, consumer);
        if (container -> type() == Values::MAP) return functional_out::filterMap((MapValue*) container, consumer);
        throw new TypeException("Invalid first argument. Array or map expected");
    });

    Function* flat_map = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() < 2) throw new ArgumentsMismatchException("At least arguments excepted");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected at first argument");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected at second arguments");
        return functional_out::FlatmapArray((ArrayValue*)values[0], ((FunctionValue*)values[1]) -> getFunction());
    });

    Function* foreach = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected at second argument");
        Function* function = ((FunctionValue*) values[1]) -> getFunction();
        Value* container = values[0];
        if (container -> type() == Values::ARRAY){
            ArrayValue* arr = (ArrayValue*)container;
            for(int i = 0; i < arr -> size(); ++i){
                std::vector<Value*> args = {arr -> get(i)};
                function -> execute(args);
            }
        }
        else if (container -> type() == Values::MAP){
            MapValue map = *(MapValue*)container;
            int i = 0;
            auto iter = map.begin();
            while (i < map.size()){
                std::vector<Value*> args = { iter -> first, iter -> second };
                function -> execute(args);
                ++iter;
                ++i;
            }
        }
        else throw new TypeException("Invalid first argument. Array or map expected");
        return NullValue::NULL_;
    });

    Function* map = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("At least two arguments excepted");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        Value* container = values[0];
        Function* consumer = ((FunctionValue*) values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) return functional_out::mapArray((ArrayValue*) container, consumer);
        if (container -> type() == Values::MAP){
            if (values.size() < 3) throw new ArgumentsMismatchException("Three arguments excepted for map function for map type");
            if (values[2] -> type() != Values::FUNCTION) throw new TypeException("Function expected in third argument");
            Function* consumer2 = ((FunctionValue*) values[1]) -> getFunction();
            return functional_out::mapMap((MapValue*) container, consumer, consumer2);
        }
        throw new TypeException("Invalid first argument. Array or map expected");
    });

    Function* reduce = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
        if (values[2] -> type() != Values::FUNCTION) throw new TypeException("Function expected in third argument");
        Value* container = values[0], *identy = values[1];
        Function* accumulator = ((FunctionValue*) values[2]) -> getFunction();
        if (container -> type() == Values::ARRAY){
            Value* result = identy;
            ArrayValue* arr = (ArrayValue*) container;
            for(int i = 0; i < arr -> size(); ++i){
                std::vector<Value*> args = {result, arr -> get(i)};
                result = accumulator -> execute(args);
            }
            return result;
        }
        if (container -> type() == Values::MAP){
            Value* result = identy;
            MapValue map = *(MapValue*)container;
            int i = 0;
            auto iter = map.begin();
            while (i < map.size()){
                std::vector<Value*> args = { result, iter -> first, iter -> second };
                result = accumulator -> execute(args);
                ++iter;
                ++i;
            }
            return result;
        }
        throw new TypeException("Invalid first argument. Array or map expected");
    });

    Function* sortby = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        ArrayValue* arr = (ArrayValue*)values[0];
        Function* func = ((FunctionValue*)values[1]) -> getFunction();
        std::sort(arr -> begin(), arr -> end(), [func](Value* l, Value* r) -> bool { return functional_out::comparator(func -> execute({l}), func -> execute({r})); });
        return arr;
    });

    Function* take_while = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        Value* container = values[0];
        Function* function = ((FunctionValue*) values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) {
            ArrayValue* array = (ArrayValue*) container;
            int size = array -> size();
            std::vector<Value*> vals;
            for(int i = 0; i < size; ++i) {
                Value* value = array -> get(i);
                std::vector<Value*> vec = {value};
                if (function -> execute(vec) -> asBool()) {
                    vals.push_back(value);
                } else break;
            }
            return new ArrayValue(vals);
        }
        if (container -> type() == Values::MAP) {
            MapValue* map = (MapValue*) container;
            MapValue* result = new MapValue(map -> size());
            for (auto x = map -> begin(); x != map -> end(); ++x) {
                std::vector<Value*> vals = {x -> first, x -> second};
                if (function -> execute(vals) != new NumberValue(0)){
                    result -> set(x -> first, x -> second);
                } else break;
            }
            return result;
        }
        throw new TypeException("Invalid first argument. Array or map expected");
    });
}}}

void Functional::initFunctions(){
    Functions::set("chain", chain);
    Functions::set("combine", combine);
    Functions::set("drop_while", drop_while);
    Functions::set("filter", filter);
    Functions::set("flat_map", flat_map);
    Functions::set("foreach", foreach);
    Functions::set("map", map);
    Functions::set("reduce", reduce);
    Functions::set("sortby", sortby);
    Functions::set("take_while", take_while);
}

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

namespace SlavaScript::modules::functional_out{
    bool comparator(std::shared_ptr<Value> a, std::shared_ptr<Value> b){
        return (*a) < (*b);
    }

    std::shared_ptr<Value> filterArray(std::shared_ptr<ArrayValue> arr, std::shared_ptr<Function> consumer){
        int size = arr -> size();
        std::vector<std::shared_ptr<Value>> result;
        for(auto value : *arr){
            if (consumer -> execute({value}) -> asBool()) result.push_back(value);
        }
        SH_RET(ArrayValue, result);
    }

    std::shared_ptr<Value> filterMap(std::shared_ptr<MapValue> map, std::shared_ptr<Function> consumer){
        int i = 0;
        std::shared_ptr<MapValue> result = SHARE(MapValue, );
        auto iter = map -> begin();
        while (i < map -> size()){
            std::vector<std::shared_ptr<Value>> args = { iter -> first, iter -> second };
            if (consumer -> execute(args)) result -> set(iter -> first, iter -> second);
            ++iter;
            ++i;
        }
        return result;
    }

    std::shared_ptr<Value> flatMapArray(std::shared_ptr<ArrayValue> arr, std::shared_ptr<Function> mapper){
        std::vector<std::shared_ptr<Value>> values;
        for(auto value : *arr){
            std::shared_ptr<Value> inner = mapper -> execute({value});
            if (inner -> type() != Values::ARRAY) throw new TypeException("Array expected " + std::string(*inner));
            std::shared_ptr<ArrayValue> valArr = CAST(ArrayValue, inner);
            for(auto value2 : *valArr){
                values.push_back(value2);
            }
        }
        SH_RET(ArrayValue, values);
    }

    std::shared_ptr<Value> mapArray(std::shared_ptr<ArrayValue> arr, std::shared_ptr<Function> consumer){
        int size = arr -> size();
        std::vector<std::shared_ptr<Value>> result;
        for(auto value : *arr){
            result.push_back(consumer -> execute({value}));
        }
        SH_RET(ArrayValue, result);
    }

    std::shared_ptr<Value> mapMap(std::shared_ptr<MapValue> map, std::shared_ptr<Function> consumer, std::shared_ptr<Function> consumer2){
        int i = 0;
        std::shared_ptr<MapValue> value = SHARE(MapValue, );
        auto iter = map -> begin();
        while (i < map -> size()){
            std::vector<std::shared_ptr<Value>> args1 = { iter -> first};
            std::vector<std::shared_ptr<Value>> args2 = { iter -> second};
            value -> set(consumer -> execute(args1), consumer2 -> execute(args2));
            ++iter;
            ++i;
        }
        return value;
    }
}

namespace SlavaScript::modules::functional_f{
    CREATE_FUNCTION(chain)
        if (values.size() < 3) throw new ArgumentsMismatchException("3 and least arguments expected");
        std::shared_ptr<Value> result = values[0];
        for(int i = 1; i < values.size(); i += 2){
            if (values[i] -> type() != Values::FUNCTION) throw new TypeException(std::string(*values[i]) + " is not a function");
            std::shared_ptr<Function> function = CAST(FunctionValue, values[i]) -> getFunction();
            result = function -> execute({result, values[i + 1]});
        }
        return result;
    FE

    CREATE_FUNCTION(combine)
        if (values.size() < 1) throw new ArgumentsMismatchException("At least one arg expected");
        std::shared_ptr<Function> result = nullptr;
        for(auto arg : values){
            if (arg -> type() != Values::FUNCTION){
                throw new TypeException(std::string(*arg) + " is not a function");
            }
            std::shared_ptr<Function> current = result;
            std::shared_ptr<Function> next = CAST(FunctionValue, arg) -> getFunction();
            result = std::make_shared<FunctionModule>([current, next](std::vector<std::shared_ptr<Value>> values) -> std::shared_ptr<Value>{
                if (current == nullptr) return next -> execute(values);
                return next -> execute({current -> execute(values)});
            });
        }
        SH_RET(FunctionValue, result);
    FE

    CREATE_FUNCTION(drop_while)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        std::shared_ptr<Function> function = CAST(FunctionValue, values[1]) -> getFunction();
        std::shared_ptr<ArrayValue> array = CAST(ArrayValue, values[0]);
        int skipCount = 0;
        for(auto value : *array){
            std::vector<std::shared_ptr<Value>> vec = { value };
            if (function -> execute(vec) -> asBool()) ++skipCount;
            else break;
        }
        std::vector<std::shared_ptr<Value>> vec;
        for(int i = skipCount; i < array -> size(); ++i){
            vec.push_back(array -> get(i));
        }
        SH_RET(ArrayValue, vec);
    FE

    CREATE_FUNCTION(filter)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        std::shared_ptr<Value> container = values[0];
        std::shared_ptr<Function> consumer = CAST(FunctionValue, values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) return functional_out::filterArray(CAST(ArrayValue, container), consumer);
        if (container -> type() == Values::MAP) return functional_out::filterMap(CAST(MapValue, container), consumer);
        throw new TypeException("Invalid first argument. Array or map expected");
    FE

    CREATE_FUNCTION(flat_map)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected at first argument");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected at second arguments");
        return functional_out::flatMapArray(CAST(ArrayValue, values[0]), CAST(FunctionValue, values[1]) -> getFunction());
    FE

    CREATE_FUNCTION(foreach)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected at second argument");
        std::shared_ptr<Function> function = CAST(FunctionValue, values[1]) -> getFunction();
        std::shared_ptr<Value> container = values[0];
        if (container -> type() == Values::ARRAY){
            std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, container);
            for(auto element : *arr){
                function -> execute({element});
            }
        }
        else if (container -> type() == Values::MAP){
            std::shared_ptr<MapValue> map = CAST(MapValue, container);
            int i = 0;
            auto iter = map -> begin();
            while (i < map -> size()){
                std::vector<std::shared_ptr<Value>> args = { iter -> first, iter -> second };
                function -> execute(args);
                ++iter;
                ++i;
            }
        }
        else throw new TypeException("Invalid first argument. Array or map expected");
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(map)
        if (values.size() < 2 || values.size() > 3) throw new ArgumentsMismatchException("Two or three arguments excepted");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        std::shared_ptr<Value> container = values[0];
        std::shared_ptr<Function> consumer = CAST(FunctionValue, values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY){
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
            return functional_out::mapArray(CAST(ArrayValue, container), consumer);
        }
        if (container -> type() == Values::MAP){
            if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments excepted");
            if (values[2] -> type() != Values::FUNCTION) throw new TypeException("Function expected in third argument");
            std::shared_ptr<Function> consumer2 = CAST(FunctionValue, values[1]) -> getFunction();
            return functional_out::mapMap(CAST(MapValue, container), consumer, consumer2);
        }
        throw new TypeException("Invalid first argument. Array or map expected");
    FE

    CREATE_FUNCTION(reduce)
        if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
        if (values[2] -> type() != Values::FUNCTION) throw new TypeException("Function expected in third argument");
        std::shared_ptr<Value> container = values[0], identy = values[1];
        std::shared_ptr<Function> accumulator = CAST(FunctionValue, values[2]) -> getFunction();
        if (container -> type() == Values::ARRAY){
            std::shared_ptr<Value> result = identy;
            std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, container);
            for(auto element : *arr){
                result = accumulator -> execute({result, element});
            }
            return result;
        }
        if (container -> type() == Values::MAP){
            std::shared_ptr<Value> result = identy;
            std::shared_ptr<MapValue> map = CAST(MapValue, container);
            int i = 0;
            auto iter = map -> begin();
            while (i < map -> size()){
                std::vector<std::shared_ptr<Value>> args = { result, iter -> first, iter -> second };
                result = accumulator -> execute(args);
                ++iter;
                ++i;
            }
            return result;
        }
        throw new TypeException("Invalid first argument. Array or map expected");
    FE

    CREATE_FUNCTION(sortby)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments excepted");
        if (values[0] -> type() != Values::ARRAY) throw new TypeException("Array expected in first argument");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, values[0]);
        std::shared_ptr<Function> func = CAST(FunctionValue, values[1]) -> getFunction();
        std::sort(arr -> begin(), arr -> end(), [func](std::shared_ptr<Value> l, std::shared_ptr<Value> r) -> bool { return functional_out::comparator(func -> execute({l}), func -> execute({r})); });
        return arr;
    FE

    CREATE_FUNCTION(take_while)
        if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected");
        if (values[1] -> type() != Values::FUNCTION) throw new TypeException("Function expected in second argument");
        std::shared_ptr<Value> container = values[0];
        std::shared_ptr<Function> function = CAST(FunctionValue, values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) {
            std::shared_ptr<ArrayValue> array = CAST(ArrayValue, container);
            std::vector<std::shared_ptr<Value>> result;
            for(auto element : *array) {
                if (function -> execute({element}) -> asBool()) {
                    result.push_back(element);
                } else break;
            }
            SH_RET(ArrayValue, result);
        }
        if (container -> type() == Values::MAP) {
            std::shared_ptr<MapValue> map = CAST(MapValue, container);
            std::shared_ptr<MapValue> result = SHARE(MapValue, map -> size());
            for (auto x = map -> begin(); x != map -> end(); ++x) {
                std::vector<std::shared_ptr<Value>> vals = {x -> first, x -> second};
                if (function -> execute(vals) -> asBool()){
                    result -> set(x -> first, x -> second);
                } else break;
            }
            return result;
        }
        throw new TypeException("Invalid first argument. Array or map expected");
    FE
}

void Functional::initFunctions(){
    INFO_F(chain, ArgumentsInfo(3, 0, 1))
    INFO_F(combine, ArgumentsInfo(1, 0, 1))
    BINARY_F(drop_while)
    BINARY_F(filter)
    BINARY_F(flat_map)
    BINARY_F(foreach)
    INFO_F(map, ArgumentsInfo(2, 1))
    TERNARY_F(reduce)
    BINARY_F(sortby)
    BINARY_F(take_while)
}

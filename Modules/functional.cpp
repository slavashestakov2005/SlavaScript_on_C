#include <Lib/functions.h>
#include <Lib/utils.h>
#include <Modules/functional.h>
#include <Value/arrayvalue.h>
#include <Value/mapvalue.h>
#include <Value/nullvalue.h>


using namespace SlavaScript::lang;
using namespace SlavaScript::modules::functional_f;
using SlavaScript::modules::Functional;


namespace SlavaScript::modules::functional_out {
    std::shared_ptr<Value> filterArray(std::shared_ptr<ArrayValue> arr, std::shared_ptr<Function> consumer) {
        std::vector<std::shared_ptr<Value>> result;
        for (auto value : *arr) {
            if (consumer -> execute({value}) -> asBool()) result.push_back(value);
        }
        SH_RET(ArrayValue, result);
    }

    std::shared_ptr<Value> filterMap(std::shared_ptr<MapValue> map, std::shared_ptr<Function> consumer) {
        int i = 0;
        std::shared_ptr<MapValue> result = SHARE(MapValue);
        auto iter = map -> begin();
        while (i < map -> size()) {
            std::vector<std::shared_ptr<Value>> args = { iter -> first, iter -> second };
            if (consumer -> execute(args)) result -> set(iter -> first, iter -> second);
            ++iter;
            ++i;
        }
        return result;
    }

    std::shared_ptr<Value> flatMapArray(std::shared_ptr<ArrayValue> arr, std::shared_ptr<Function> mapper) {
        std::vector<std::shared_ptr<Value>> values;
        for (auto value : *arr) {
            std::shared_ptr<Value> inner = mapper -> execute({value});
            argType(Values::ARRAY, inner);
            std::shared_ptr<ArrayValue> valArr = CAST(ArrayValue, inner);
            for (auto value2 : *valArr) {
                values.push_back(value2);
            }
        }
        SH_RET(ArrayValue, values);
    }

    std::shared_ptr<Value> mapArray(std::shared_ptr<ArrayValue> arr, std::shared_ptr<Function> consumer) {
        std::vector<std::shared_ptr<Value>> result;
        for (auto value : *arr) {
            result.push_back(consumer -> execute({value}));
        }
        SH_RET(ArrayValue, result);
    }

    std::shared_ptr<Value> mapMap(std::shared_ptr<MapValue> map, std::shared_ptr<Function> consumer, std::shared_ptr<Function> consumer2) {
        int i = 0;
        std::shared_ptr<MapValue> value = SHARE(MapValue);
        auto iter = map -> begin();
        while (i < map -> size()) {
            std::vector<std::shared_ptr<Value>> args1 = { iter -> first};
            std::vector<std::shared_ptr<Value>> args2 = { iter -> second};
            value -> set(consumer -> execute(args1), consumer2 -> execute(args2));
            ++iter;
            ++i;
        }
        return value;
    }
}

namespace SlavaScript::modules::functional_f {
    CREATE_FUNCTION(chain)
        argsCountLtEq(3, values.size());
        std::shared_ptr<Value> result = values[0];
        for (size_t i = 1; i < values.size(); i += 2) {
            argType(Values::FUNCTION, values[i]);
            std::shared_ptr<Function> function = CAST(FunctionValue, values[i]) -> getFunction();
            result = function -> execute({result, values[i + 1]});
        }
        return result;
    FE

    CREATE_FUNCTION(combine)
        argsCountLtEq(1, values.size());
        std::shared_ptr<Function> result = nullptr;
        for (auto arg : values) {
            argType(Values::FUNCTION, arg);
            std::shared_ptr<Function> current = result;
            std::shared_ptr<Function> next = CAST(FunctionValue, arg) -> getFunction();
            result = std::make_shared<ModuleFunction>([current, next](std::vector<std::shared_ptr<Value>> values) -> std::shared_ptr<Value>{
                if (current == nullptr) return next -> execute(values);
                return next -> execute({current -> execute(values)});
            });
        }
        SH_RET(FunctionValue, result);
    FE

    CREATE_FUNCTION(drop_while)
        argsCount(2, values.size());
        argType(Values::ARRAY, values[0]);
        argType(Values::FUNCTION, values[1]);
        std::shared_ptr<Function> function = CAST(FunctionValue, values[1]) -> getFunction();
        std::shared_ptr<ArrayValue> array = CAST(ArrayValue, values[0]);
        int skipCount = 0;
        for (auto value : *array) {
            std::vector<std::shared_ptr<Value>> vec = { value };
            if (function -> execute(vec) -> asBool()) ++skipCount;
            else break;
        }
        std::vector<std::shared_ptr<Value>> vec;
        for (int i = skipCount; i < array -> size(); ++i) {
            vec.push_back(array -> get(i));
        }
        SH_RET(ArrayValue, vec);
    FE

    CREATE_FUNCTION(filter)
        argsCount(2, values.size());
        argType(Values::ARRAY, Values::MAP, values[0]);
        argType(Values::FUNCTION, values[1]);
        std::shared_ptr<Value> container = values[0];
        std::shared_ptr<Function> consumer = CAST(FunctionValue, values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) return functional_out::filterArray(CAST(ArrayValue, container), consumer);
        if (container -> type() == Values::MAP) return functional_out::filterMap(CAST(MapValue, container), consumer);
    FE

    CREATE_FUNCTION(flat_map)
        argsCount(2, values.size());
        argType(Values::ARRAY, values[0]);
        argType(Values::FUNCTION, values[1]);
        return functional_out::flatMapArray(CAST(ArrayValue, values[0]), CAST(FunctionValue, values[1]) -> getFunction());
    FE

    CREATE_FUNCTION(foreach)
        argsCount(2, values.size());
        argType(Values::ARRAY, Values::MAP, values[0]);
        argType(Values::FUNCTION, values[1]);
        std::shared_ptr<Function> function = CAST(FunctionValue, values[1]) -> getFunction();
        std::shared_ptr<Value> container = values[0];
        if (container -> type() == Values::ARRAY) {
            std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, container);
            for (auto element : *arr) {
                function -> execute({element});
            }
        } else if (container -> type() == Values::MAP) {
            std::shared_ptr<MapValue> map = CAST(MapValue, container);
            int i = 0;
            auto iter = map -> begin();
            while (i < map -> size()) {
                std::vector<std::shared_ptr<Value>> args = { iter -> first, iter -> second };
                function -> execute(args);
                ++iter;
                ++i;
            }
        }
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(map)
        argsCount(2, 3, values.size());
        argType(Values::ARRAY, Values::MAP, values[0]);
        argType(Values::FUNCTION, values[1]);
        std::shared_ptr<Value> container = values[0];
        std::shared_ptr<Function> consumer = CAST(FunctionValue, values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) {
            argsCount(2, values.size());
            return functional_out::mapArray(CAST(ArrayValue, container), consumer);
        }
        if (container -> type() == Values::MAP) {
            argsCount(3, values.size());
            argType(Values::FUNCTION, values[2]);
            std::shared_ptr<Function> consumer2 = CAST(FunctionValue, values[1]) -> getFunction();
            return functional_out::mapMap(CAST(MapValue, container), consumer, consumer2);
        }
    FE

    CREATE_FUNCTION(reduce)
        argsCount(3, values.size());
        argType(Values::ARRAY, Values::MAP, values[0]);
        argType(Values::FUNCTION, values[2]);
        std::shared_ptr<Value> container = values[0], identy = values[1];
        std::shared_ptr<Function> accumulator = CAST(FunctionValue, values[2]) -> getFunction();
        if (container -> type() == Values::ARRAY) {
            std::shared_ptr<Value> result = identy;
            std::shared_ptr<ArrayValue> arr = CAST(ArrayValue, container);
            for (auto element : *arr) {
                result = accumulator -> execute({result, element});
            }
            return result;
        }
        if (container -> type() == Values::MAP) {
            std::shared_ptr<Value> result = identy;
            std::shared_ptr<MapValue> map = CAST(MapValue, container);
            int i = 0;
            auto iter = map -> begin();
            while (i < map -> size()) {
                std::vector<std::shared_ptr<Value>> args = { result, iter -> first, iter -> second };
                result = accumulator -> execute(args);
                ++iter;
                ++i;
            }
            return result;
        }
    FE

    CREATE_FUNCTION(take_while)
        argsCount(2, values.size());
        argType(Values::ARRAY, Values::MAP, values[0]);
        argType(Values::FUNCTION, values[1]);
        std::shared_ptr<Value> container = values[0];
        std::shared_ptr<Function> function = CAST(FunctionValue, values[1]) -> getFunction();
        if (container -> type() == Values::ARRAY) {
            std::shared_ptr<ArrayValue> array = CAST(ArrayValue, container);
            std::vector<std::shared_ptr<Value>> result;
            for (auto element : *array) {
                if (function -> execute({element}) -> asBool()) {
                    result.push_back(element);
                } else break;
            }
            SH_RET(ArrayValue, result);
        }
        if (container -> type() == Values::MAP) {
            std::shared_ptr<MapValue> map = CAST(MapValue, container);
            std::shared_ptr<MapValue> result = SHARE(MapValue);
            for (auto x = map -> begin(); x != map -> end(); ++x) {
                std::vector<std::shared_ptr<Value>> vals = {x -> first, x -> second};
                if (function -> execute(vals) -> asBool()) {
                    result -> set(x -> first, x -> second);
                } else break;
            }
            return result;
        }
    FE
}

void Functional::initFunctions() {
    MFUNC_INFO(chain, ArgumentsInfo(3, 0, 1))
    MFUNC_INFO(combine, ArgumentsInfo(1, 0, 1))
    MFUNC_BINARY(drop_while)
    MFUNC_BINARY(filter)
    MFUNC_BINARY(flat_map)
    MFUNC_BINARY(foreach)
    MFUNC_INFO(map, ArgumentsInfo(2, 1))
    MFUNC_TERNARY(reduce)
    MFUNC_BINARY(take_while)
}

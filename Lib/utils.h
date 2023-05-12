#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "function.h"

namespace SlavaScript::lang{
    CMP(std::string);
    void argsCount(std::vector<int> expected, int got);
    void argsCount(int a, int got);
    void argsCount(int a, int b, int got);
    void argsCountLtEq(int expected, int got);
    void argType(std::vector<Values> expected, std::shared_ptr<Value> got, std::string info = "");
    void argType(Values a, std::shared_ptr<Value> got, std::string info = "");
    void argType(Values a, Values b, std::shared_ptr<Value> got, std::string info = "");

    template<typename T>
    std::shared_ptr<Function> get_property(std::shared_ptr<Value> value, T operation);
}

#include "utils_impl.h"

#endif // UTILS_H_INCLUDED

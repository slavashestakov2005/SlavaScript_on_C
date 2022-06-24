#ifndef NAMES_H_INCLUDED
#define NAMES_H_INCLUDED

#include "functions.h"
#include "../Value/value.h"
#include "../Value/classvalue.h"

namespace SlavaScript::lang{
    struct NamedValue{
        std::string name;
        std::shared_ptr<Value> variable = nullptr;
        std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> function;
        std::shared_ptr<ClassValue> classDec = nullptr;
    };

    class Names{
    private:
        static void erase(std::string name, int type);
    public:
        static std::shared_ptr<Value> get(std::string name, bool ignore = false);
        static NamedValue getNamed(std::string name);
        static void erase(std::string name);
        static void pushScope();
        static void popScope();
        static void copyScope();
        static void init();
        static bool isExists(std::string name);
        static void setVariable(std::string key, std::shared_ptr<Value> value);
        static void setFunction(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info);
        static void setClass(std::string key, std::shared_ptr<ClassValue> classDef);
        static void restore(NamedValue named);
    };
}

#endif // NAMES_H_INCLUDED

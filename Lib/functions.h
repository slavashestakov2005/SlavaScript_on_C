#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <map>
#include <string>
#include "function.h"
#include "functions.h"

namespace SlavaScript::lang{
    struct NamedValue;

    class ArgumentsInfo{
    private:
        int required, optional, array;
    public:
        static ArgumentsInfo without, unary, binary, ternary, quaternary, inf, inf1;
        ArgumentsInfo(int required, int optional = 0, int array = 0) : required(required), optional(optional), array(array) {}
        int getRequired() { return required; }
        int getOptional() { return optional; }
        int getArray() { return array; }
        bool canCalled(int argsCount){
            return required <= argsCount && (array || argsCount <= required + optional);
        }
    };

    class FunctionsScope{
    private:
        std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> functions;
    public:
        void start();
        std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> getScope();
        bool isExists(std::string key);
        /** @return  throw: UnknownFunctionException*. */
        std::shared_ptr<Function> get(std::string key);
        std::shared_ptr<Function> get(std::string key, int count);
        void set(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info);
        void set(std::string key, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> vals);
        void erase(std::string key);
        bool find(std::string key, int count);
        void print();
        std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> save(std::string key);
        void restore(NamedValue named);
    };

    class Functions{
    private:
        static std::vector<FunctionsScope> scope;
    public:
        static void init();
        static void start();
        static std::map<std::string, std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>>> getScope();
        static bool isExists(std::string key);
        static std::shared_ptr<Function> get(std::string key);
        static std::shared_ptr<Function> get(std::string key, int count);
        static void set(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info);
        static void erase(std::string key);
        static bool find(std::string key, int count);
        static void print();
        static std::vector<std::pair<ArgumentsInfo, std::shared_ptr<Function>>> save(std::string key);
        static void restore(NamedValue named);
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}

#endif // FUNCTIONS_H_INCLUDED

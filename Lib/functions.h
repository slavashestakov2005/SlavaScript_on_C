#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <map>
#include <string>
#include "function.h"

namespace SlavaScript{ namespace lang{
    class FunctionsScope{
    private:
        std::map<std::string, std::shared_ptr<Function>> functions;
    public:
        void start();
        std::map<std::string, std::shared_ptr<Function>> getScope();
        bool isExists(std::string key);
        /** @return  throw: UnknownFunctionException*. */
        std::shared_ptr<Function> get(std::string key);
        std::shared_ptr<Function> get(std::string key, int count);
        void set(std::string key, std::shared_ptr<Function> function);
        bool add(std::string key, std::shared_ptr<Function> function, int start, int finish);
        bool find(std::string key, int count);
        void print();
    };

    class Functions{
    private:
        static std::vector<FunctionsScope> scope;
    public:
        static void init();
        static void start();
        static std::map<std::string, std::shared_ptr<Function>> getScope();
        static bool isExists(std::string key);
        static std::shared_ptr<Function> get(std::string key);
        static std::shared_ptr<Function> get(std::string key, int count);
        static void set(std::string key, std::shared_ptr<Function> function);
        static bool add(std::string key, std::shared_ptr<Function> function, int start, int finish);
        static bool find(std::string key, int count);
        static void print();
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}}

#endif // FUNCTIONS_H_INCLUDED

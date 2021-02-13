#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "../Value/value.h"

namespace SlavaScript{ namespace lang{
    class VariablesScope{
    private:
        std::map<std::string, Value*> variables;
        std::vector<std::map<std::string, Value*>*> vec;
    public:
        void start();
        void push();
        void pop();
        std::map<std::string, Value*> getScope();
        bool isExists(std::string key);
        Value* get(std::string key);
        void set(std::string key, Value* value);
        void print();
    };

    class Variables{
    private:
        static std::vector<VariablesScope> scope;
    public:
        static void init();
        static void start();
        static void push();
        static void pop();
        static std::map<std::string, Value*> getScope();
        static bool isExists(std::string key);
        static Value* get(std::string key);
        static void set(std::string key, Value* value);
        static void print();
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}}

#endif // VARIABLES_H_INCLUDED

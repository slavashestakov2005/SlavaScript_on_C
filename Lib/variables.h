#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#include "../Value/value.h"

namespace SlavaScript{ namespace lang{
    class Variables{
    private:
        static std::map<std::string, Value*> variables, now;
        static std::vector<std::map<std::string, Value*>*> vec;
        static bool insert;
    public:
        static void start();
        static void setInsert(bool v);
        static std::map<std::string, Value*> getNow();
        static void push();
        static void pop();
        static bool isExists(std::string key);
        static Value* get(std::string key);
        static void set(std::string key, Value* value);
        static void print();
    };
}}

#endif // VARIABLES_H_INCLUDED

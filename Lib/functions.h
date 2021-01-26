#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <map>
#include <string>
#include "function.h"

namespace SlavaScript{ namespace lang{
    class Functions{
    private:
        static std::map<std::string, Function*> functions, now;
        static bool insert;
    public:
        static void start();
        static void setInsert(bool v);
        static std::map<std::string, Function*> getNow();
        static void clear();
        static bool isExists(std::string key);
        /** @return  throw: UnknownFunctionException*. */
        static Function* get(std::string key);
        static void set(std::string key, Function* function);
        static bool add(std::string key, Function* function, int start, int finish);
        static bool find(std::string key, int count);
        static Function* get(std::string key, int count);
        static void print();
    };
}}

#endif // FUNCTIONS_H_INCLUDED

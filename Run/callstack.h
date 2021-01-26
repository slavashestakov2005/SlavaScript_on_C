#ifndef CALLSTACK_H_INCLUDED
#define CALLSTACK_H_INCLUDED

#include <vector>
#include <string>
#include "../Lib/function.h"

namespace SlavaScript{ namespace lang{
    class CallInfo{
    private:
        std::string name;
        Function* function;
    public:
        CallInfo(std::string name, Function* function) : name(name), function(function) { }
        operator std::string(){ return name; }
    };

    class CallStack{
    private:
        static std::vector<CallInfo*> calls;
    public:
        static void push(std::string name, Function* function);
        static void pop();
        static void clear();
        static std::string callsToString();
    };
}}

#endif // CALLSTACK_H_INCLUDED

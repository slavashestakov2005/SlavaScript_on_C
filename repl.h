#ifndef REPL_H_INCLUDED
#define REPL_H_INCLUDED

#include <string>

namespace SlavaScript{ namespace lang{
    class Repl{
    private:
        static std::string HELP, VARS, FUNCS, SOURCE, CLEAR, EXIT;
        static void help(bool full);
        static void vars();
        static void funcs();
    public:
        static void start();
    };
}}

#endif // REPL_H_INCLUDED

#pragma once

#include <string>


namespace SlavaScript::lang {
    class Repl {
    private:
        static std::string HELP, VARS, FUNCS, SOURCE, CLEAR, EXIT;
        static void help(bool full);
        static void vars();
        static void funcs();
    public:
        static void start();
    };
}

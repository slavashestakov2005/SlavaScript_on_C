#ifndef START_H_INCLUDED
#define START_H_INCLUDED

#include "../Parser/lexer.h"
#include "../Statement/statement.h"
#include <string>
#include <vector>

namespace SlavaScript::lang{
    class Start{
    private:
        double time = 0;
        std::string path;
        Lexer lexer;
        std::vector<Token*> tokens;
        Statement* program;
        std::string read();
    public:
        Start(std::string path);
        void start();
        void printAST();
        void printTokens();
        void printWorkTime();
    };
}

#endif // START_H_INCLUDED

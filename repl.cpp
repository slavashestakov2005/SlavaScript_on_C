#include "repl.h"
#include <iostream>
#include "Parser/lexer.h"
#include "Parser/parser.h"
#include "Statement/statement.h"
#include "path.h"
#include "Lib/variables.h"
#include "Lib/functions.h"

using namespace SlavaScript::lang;

std::string Repl::HELP = "help", Repl::VARS = "vars", Repl::FUNCS = "funcs", Repl::SOURCE = "source", Repl::CLEAR = "clear", Repl::EXIT = "exit";

void Repl::start(){
    std::cout << "Welcome to SlavaScript 1.2.0 REPL" << std::endl;
    std::cout << "You can use this commands in REPL:" << std::endl;
    std::cout << "  exit    for exit of REPL" << std::endl;
    std::cout << "  Ctrl+Z  for exit of REPL" << std::endl;
    std::cout << "  clear   for clear buffer" << std::endl;
    std::string code, start = ">>> ", line;
    std::cout << start;
    while(getline(std::cin, line)){
        if (line == EXIT) break;
        if (line == CLEAR){
            code = "";
            std::cout << start;
            continue;
        }
        if (line == HELP){ help(true); continue; }
        if (line == VARS){ vars(); continue; }
        if (line == FUNCS){ funcs(); continue; }
        if (line == SOURCE){ std::cout << code << std::endl; continue; }
        if (line == ""){
            std::cout << start;
            continue;
        }
        code += line;
        code += "\n";
        try{
            Lexer lexer = Lexer(code);
            std::vector<Token*> tokens = lexer.tokenize();
            Parser parser = Parser(tokens);
            Statement* program = parser.parse();
            if (parser.getParseErrors().hasError()){
                std::cout << std::string(parser.getParseErrors());
                continue;
            }
            /** Запуск программы **/
            Path::setImpoted(true);
            for(unsigned i = 0; i < tokens.size(); ++i) delete tokens[i];
            program -> execute();
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
        }
        catch(std::exception* e){
            std::cout << e -> what() << std::endl;
        }
        std::cout << start;
    }
}

void Repl::help(bool full){
    std::cout << "Type in expressions to have them evaluated." << std::endl;
    if (full){
        std::cout << VARS << " - listing variables" << std::endl;
        std::cout << FUNCS << " - listing functions" << std::endl;
        std::cout << SOURCE << " - listing source" << std::endl;
    }
    std::cout << HELP << " - show help" << std::endl;
    std::cout << CLEAR << " - clear buffer" << std::endl;
    std::cout << EXIT << " - exit REPL" << std::endl;
}

void Repl::vars(){
    Variables::print();
}

void Repl::funcs(){
    Functions::print();
}

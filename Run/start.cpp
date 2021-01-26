#include "start.h"
#include <iostream>
#include <fstream>
#include "../Parser/parser.h"
#include "../Visitor/assignvalidator.h"
#include "../Visitor/functionadder.h"
#include "../Visitor/importadder.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include <ctime>
#include "path.h"
#include "../Parser/token.h"

using namespace SlavaScript::lang;

Start::Start(std::string path) : path(path), lexer(Lexer("")) {
    if (this -> path.find(".") == std::string::npos) this -> path += ".s++";
    std::string directory;
    int pos;
    for(pos = path.size() - 1; pos > -1 && path[pos] != '\\' && path[pos] != '/'; --pos);
    for(int i = 0; i <= pos; ++i) directory += path[i];
    Path::setPath(directory);
}

std::string Start::read(){
    std::string str, in;
    std::ifstream fin(path);
    while(getline(fin, in)) { str += in; str += "\n"; }
    fin.close();
    return str;
}

void Start::start(){
    double startTime = clock();
    std::string code = read();
    /** Очищение данных **/
    Variables::start();
    Functions::start();
    try{
        lexer = Lexer(code);
        tokens = lexer.tokenize();
        Parser parser = Parser(tokens);
        program = parser.parse();
        if (parser.getParseErrors().hasError()){
            std::cout << std::string(parser.getParseErrors());
            return;
        }
        Path::setImpoted(true);
        /** Запуск программы **/
        //Functions::print();
        //program -> accept(new VariablePrinter());
        //std::cout << "Tokenize:\n";
        //printTokens();
        program -> accept(new ImportAdder());
        program -> accept(new FunctionAdder());
        program -> accept(new AssignValidator());
        for(unsigned i = 0; i < tokens.size(); ++i) delete tokens[i];
        Path::setImpoted(false);
        //std::cout << "Execute v\n";
        //printAST();
        program -> execute();
        Path::setImpoted(true);
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::exception* e){
        std::cout << e -> what() << std::endl;
    }
    time = clock() - startTime;
}

void Start::printAST(){
    std::cout << std::string(*program) << std::endl;
}

void Start::printTokens(){
    std::string code = read();
    lexer = Lexer(code);
    try{
        std::vector<Token*> temp = lexer.tokenize();
        std::cout << temp.size() << std::endl;
        int i = 0;
        for(auto x : temp){
            std::cout << x << std::endl;
            ++i;
        }
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
}

void Start::printWorkTime(){
    std::cout << time << std::endl;
}

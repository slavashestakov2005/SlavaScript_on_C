#include <Compiler/compiler.h>
#include <Parser/lexer.h>
#include <Parser/parser.h>


using namespace SlavaScript::compiler;
using namespace SlavaScript::lang;


std::string Compiler::read_file = "";
std::string Compiler::write_file = "";
std::ofstream Compiler::generated_file;
int Compiler::tabs_count = 0;

void Compiler::create_compiler(std::string file) {
    read_file = file;
    int dot = read_file.rfind(".");
    write_file = read_file.substr(0, dot) + "_generated.cpp";
    compile();
}

void Compiler::compile() {
    generated_file.open(write_file);
    std::string code = read();
    Parser(Lexer(code).tokenize()).parse() -> accept(new CompilerVisitor());
    generated_file.close();
}

std::string Compiler::read() {
    std::string str, in;
    std::ifstream fin(read_file);
    while (getline(fin, in)) { str += in; str += "\n"; }
    fin.close();
    return str;
}

void Compiler::write(std::string text) {
    write(text, true);
}

void Compiler::write(std::string text, bool new_line) {
    for (int i = 0; i < tabs_count; ++i) generated_file << "\t";
    generated_file << text;
    if (new_line) generated_file << "\n";
}

void Compiler::append(std::string text) {
    append(text, true);
}

void Compiler::append(std::string text, bool new_line) {
    generated_file << text;
    if (new_line) generated_file << "\n";
}

void Compiler::incrementTabsCount() {
    ++tabs_count;
}

void Compiler::decrementTabsCount() {
    --tabs_count;
}

int Compiler::getTabsCount() {
    return tabs_count;
}

void Compiler::enterLoop() {
    incrementTabsCount();
    write("try{");
    incrementTabsCount();
}

void Compiler::goOutLoop() {
    decrementTabsCount();
    write("}");
    write("catch(SlavaScript::lang::BreakStatement*){ break; }");
    write("catch(SlavaScript::lang::ContinueStatement*){}");
    decrementTabsCount();
}

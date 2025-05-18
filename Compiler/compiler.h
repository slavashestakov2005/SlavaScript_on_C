#pragma once

#include <fstream>
#include <string>


namespace SlavaScript::compiler {
    class Compiler {
    private:
        static std::ofstream generated_file;
        static std::string read_file, write_file;
        static int tabs_count;
    public:
        static void create_compiler(std::string file);
        static void compile();
        static std::string read();
        static void write(std::string text);
        static void write(std::string text, bool new_line);
        static void append(std::string text);
        static void append(std::string text, bool new_line);
        static void incrementTabsCount();
        static void decrementTabsCount();
        static int getTabsCount();
        static void enterLoop();
        static void goOutLoop();
    };
}

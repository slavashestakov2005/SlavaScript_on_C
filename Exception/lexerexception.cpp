#include "lexerexception.h"
#include <sstream>

using SlavaScript::exceptions::LexerException;

LexerException::LexerException(std::string text, int row, int col){
    std::ostringstream r, c;
    r << row;
    c << col;
    this -> text = "[" + r.str() + ", " + c.str() + "] " + text;
}

char const* LexerException::what() const noexcept{
    return text.c_str();
}

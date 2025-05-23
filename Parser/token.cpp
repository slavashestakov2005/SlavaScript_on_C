#include <sstream>

#include <Parser/token.h>


using namespace SlavaScript::lang;

namespace {
    std::string mas[] = {
        "NUMBER", "HEX_NUMBER", "WORD", "TEXT",
        "PRINT", "PRINTLN", "IF", "ELIF", "ELSE", "WHILE", "FOR", "DO",
        "BREAK", "CONTINUE", "DEF", "RETURN", "IMPORT", "AS", "SWITCH", "CASE", "DEFAULT",
        "TRY", "THROW", "CATCH", "CLASS",
        "PlUS", "MINUS", "STAR", "SLASH", "PERCENT", "STARSTAR",
        "PlUSEQ", "MINUSEQ", "STAREQ", "SLASHEQ", "PERCENTEQ", "STARSTAREQ",
        "LTLT", "LTLTEQ", "GTGT", "GTGTEQ",
        "PLUSPLUS", "MINUSMINUS",
        "EQ", "EQEQ", "EXCL", "EXCLEQ", "LT", "LTEQ", "GT", "GTEQ",
        "BAR", "BARBAR", "AMP", "AMPAMP", "CARET", "TILDE",
        "BAREQ", "AMPEQ", "CARETEQ",
        "QUESTION", "COLON", "COMMA", "DOT", "GRIDGRID",
        "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
        "EOF"
    };
}


Token::Token() {}
Token::Token(TokenType type, std::string text, int row, int col) : type(type), text(text), row(row), col(col) {}


int Token::getRow() {
    return row;
}

int Token::getCol() {
    return col;
}

std::string Token::position() {
    std::ostringstream os;
    os << "{" << row << " " << col << "}";
    return os.str();
}

void Token::setType(TokenType type) {
    this -> type = type;
}

TokenType Token::getType() {
    return type;
}

void Token::setText(std::string text) {
    this -> text = text;
}

std::string Token::getText() {
    return text;
}

Token::operator std::string() {
    std::string temp = getText();
    return mas[int(getType())] + (temp.empty() ? "" : " '" + temp + "'");
}

std::ostream& operator<<(std::ostream& os, Token& tok) {
    std::string out = mas[int(tok.getType())] + " " + tok.getText();
    os << out;
    return os;
}

std::ostream& operator<<(std::ostream& os, Token* tok) {
    std::string out = mas[int(tok -> getType())] + " " + tok -> getText();
    os << out;
    return os;
}

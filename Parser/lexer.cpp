#include <Exception/exceptions.h>
#include <Parser/lexer.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::LexerException;

std::map<std::string, TokenType> Lexer::OPERATORS = {
    std::make_pair("+", TokenType::PLUS),
    std::make_pair("-", TokenType::MINUS),
    std::make_pair("*", TokenType::STAR),
    std::make_pair("/", TokenType::SLASH),
    std::make_pair("%", TokenType::PERCENT),
    std::make_pair("**", TokenType::STARSTAR),

    std::make_pair("+=", TokenType::PLUSEQ),
    std::make_pair("-=", TokenType::MINUSEQ),
    std::make_pair("*=", TokenType::STAREQ),
    std::make_pair("/=", TokenType::SLASHEQ),
    std::make_pair("%=", TokenType::PERCENTEQ),
    std::make_pair("**=", TokenType::STARSTAREQ),

    std::make_pair("<<", TokenType::LTLT),
    std::make_pair(">>", TokenType::GTGT),

    std::make_pair("<<=", TokenType::LTLTEQ),
    std::make_pair(">>=", TokenType::GTGTEQ),

    std::make_pair("++", TokenType::PLUSPLUS),
    std::make_pair("--", TokenType::MINUSMINUS),

    std::make_pair("=", TokenType::EQ),
    std::make_pair("<", TokenType::LT),
    std::make_pair(">", TokenType::GT),
    std::make_pair("==", TokenType::EQEQ),
    std::make_pair("!=", TokenType::EXCLEQ),
    std::make_pair("<=", TokenType::LTEQ),
    std::make_pair(">=", TokenType::GTEQ),

    std::make_pair("!", TokenType::EXCL),
    std::make_pair("|", TokenType::BAR),
    std::make_pair("||", TokenType::BARBAR),
    std::make_pair("&", TokenType::AMP),
    std::make_pair("&&", TokenType::AMPAMP),
    std::make_pair("^", TokenType::CARET),
    std::make_pair("~", TokenType::TILDE),

    std::make_pair("|=", TokenType::BAREQ),
    std::make_pair("&=", TokenType::AMPEQ),
    std::make_pair("^=", TokenType::CARETEQ),
    std::make_pair("##", TokenType::GRIDGRID),

    std::make_pair("(", TokenType::LPAREN),
    std::make_pair(")", TokenType::RPAREN),
    std::make_pair("{", TokenType::LBRACE),
    std::make_pair("}", TokenType::RBRACE),
    std::make_pair("[", TokenType::LBRACKET),
    std::make_pair("]", TokenType::RBRACKET),
    std::make_pair(",", TokenType::COMMA),
    std::make_pair(".", TokenType::DOT),

    std::make_pair("?", TokenType::QUESTION),
    std::make_pair(":", TokenType::COLON),
};

std::map<std::string, TokenType> Lexer::KEYWORDS = {
    std::make_pair("print", TokenType::PRINT),
    std::make_pair("println", TokenType::PRINTLN),
    std::make_pair("if", TokenType::IF),
    std::make_pair("elif", TokenType::ELIF),
    std::make_pair("else", TokenType::ELSE),
    std::make_pair("while", TokenType::WHILE),
    std::make_pair("for", TokenType::FOR),
    std::make_pair("do", TokenType::DO),
    std::make_pair("break", TokenType::BREAK),
    std::make_pair("continue", TokenType::CONTINUE),
    std::make_pair("def", TokenType::DEF),
    std::make_pair("return", TokenType::RETURN),
    std::make_pair("import", TokenType::IMPORT),
    std::make_pair("as", TokenType::AS),
    std::make_pair("switch", TokenType::SWITCH),
    std::make_pair("case", TokenType::CASE),
    std::make_pair("default", TokenType::DEFAULT),
    std::make_pair("try", TokenType::TRY),
    std::make_pair("throw", TokenType::THROW),
    std::make_pair("catch", TokenType::CATCH),
    std::make_pair("class", TokenType::CLASS),
};

std::string Lexer::OPERATOR_CHARS = "+-*/%(){}[]=<>!&|.,?:^~";

Lexer::Lexer(std::string input) {
    this -> input = input;
    length = input.size();
    pos = 0;
    last_row = last_col = col = row = 1;
}

std::vector<Token*> Lexer::tokenize() {
    while (pos < length) {
        if (!tokens.empty() && tokens.back() -> getType() == TokenType::GRIDGRID) tokenizeIntegration();
        else tokenizeToken();
    }
    return tokens;
}

void Lexer::tokenizeToken() {
    char current = peek(0);
    if (isdigit(current)) tokenizeNumber();
    else if (islower(current) || isupper(current) || current == '_' || current == '$') tokenizeWord();
    else if (current == '#' && peek(1) == '#') {
        next();
        next();
        addToken(TokenType::GRIDGRID);
    } else if (current == '#') {
        next();
        tokenizeHexNumber();
    } else if (current == '"') tokenizeText();
    else if (current == '\'') tokenizeExtendedWord();
    else if (Lexer::OPERATOR_CHARS.find(current) != std::string::npos) tokenizeOperator();
    else next();
}

void Lexer::tokenizeNumber() {
    std::string str;
    char current = peek(0);
    while (true) {
        if (current == '.') {
            if (str.find(current) != std::string::npos) error("Invalid float number");
        } else if (!isdigit(current)) break;
        str += current;
        current = next();
    }
    addToken(TokenType::NUMBER, str);
}

void Lexer::tokenizeHexNumber() {
    std::string str;
    char current = peek(0);
    while (isdigit(current) || current >= 'A' && current <= 'F' || current >= 'a' && current <= 'f') {
        str += current;
        current = next();
    }
    addToken(TokenType::HEX_NUMBER, str);
}

void Lexer::tokenizeText() {
    next();
    std::string str;
    char current = peek(0);
    while (true) {
        if (current == '\0') error("Reached end of file while parsing text string");
        if (current == '\\') {
            current = next();
            switch (current) {
                case '"' : str += '"'; current = next(); continue;
                case '0' : str += '\0'; current = next(); continue;
                case 'r' : str += '\r'; current = next(); continue;
                case 'n' : str += '\n'; current = next(); continue;
                case 't' : str += '\t'; current = next(); continue;
            }
            str += '\\';
            continue;
        }
        if (current == '"') break;
        str += current;
        current = next();
    }
    next();
    addToken(TokenType::TEXT, str);
}

void Lexer::tokenizeExtendedWord() {
    next();
    std::string str;
    char current = peek(0);
    while (true) {
        if (current == '\0') error("Reached end of file while parsing extended word");
        if (current == '\n' || current == '\r') error("Reached end of line while parsing extended word");
        if (current == '\'') break;
        str += current;
        current = next();
    }
    next();
    addToken(TokenType::WORD, str);
}

void Lexer::tokenizeOperator() {
    char current = peek(0);
    if (current == '/') {
        if (peek(1) == '/') {
            next();
            next();
            tokenizeComment();
            return;
        } else if (peek(1) == '*') {
            next();
            next();
            tokenizeMultilineComment();
            return;
        }
    }
    std::string str;
    while (true) {
        std::string text = str;
        if (OPERATORS.find(text + current) == OPERATORS.cend() && text != "") {
            addToken(OPERATORS[text]);
            return;
        }
        str += current;
        current = next();
    }
}

void Lexer::tokenizeWord() {
    std::string str;
    char current = peek(0);
    while (true) {
        if (!isdigit(current) && !islower(current) && !isupper(current) && current != '_' && current != '$') break;
        str += current;
        current = next();
    }
    if (KEYWORDS.find(str) != KEYWORDS.cend()) addToken(KEYWORDS[str]);
    else addToken(TokenType::WORD, str);
}

void Lexer::tokenizeComment() {
    char current = peek(0);
    while (true) {
        if (current == '\r' || current == '\n' || current == '\0') break;
        current = next();
    }
}

void Lexer::tokenizeMultilineComment() {
    char current = peek(0);
    while (true) {
        if (current == '\0') error("Reached end of file while parsing multiline comment");
        if (current == '*' && peek(1) == '/') break;
        current = next();
    }
    next();
    next();
}

void Lexer::tokenizeIntegration() {
    while (tokens.back() -> getType() != TokenType::LBRACE && pos < length) tokenizeToken();
    int start = pos;
    char current = peek(0);
    while (true) {
        if (current == '\0') error("Reached end of file while parsing code integration");
        if (current == '\n' && peek(1) == '}') break;
        current = next();
    }
    addToken(TokenType::TEXT, input.substr(start, pos - start));
    next();
    next();
    addToken(TokenType::RBRACE);
}

void Lexer::addToken(TokenType type) {
    tokens.push_back(new Token(type, "", last_row, last_col));
}

void Lexer::addToken(TokenType type, std::string text) {
    tokens.push_back(new Token(type, text, last_row, last_col));
}

char Lexer::next() {
    last_row = row, last_col = col;
    ++pos;
    char result = peek(0);
    if (result == '\n') {
        ++row;
        col = 0;
    } else ++col;
    return result;
}

char Lexer::peek(int position){
    int now = pos + position;
    if (now >= length) return '\0';
    else return input[now];
}

void Lexer::error(std::string text){
    throw LexerException(text, last_row, last_col);
}

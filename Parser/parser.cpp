#include <sstream>
#include <map>
#include "parser.h"
#include "../Exception/parseexception.h"
#include "../Expression/all.h"
#include "../Lib/userdefinedfunction.h"
#include "../Statement/all.h"
#include "../Value/numbervalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ParseException;

namespace{
    #define ASSIGN_TO_WORD(start, end) \
        if(lookMatch(1, TokenType::start)){ \
            std::string variable = consume(TokenType::WORD) -> getText(); \
            consume(TokenType::start); \
            return new AssignmentExpression(AssignmentOperator::end, variable, expression()); \
        }

    #define ASSIGN_TO_CONTAINER(start, end) \
        if (match(TokenType::start)) return new ContainerAssignmentExpression(AssignmentOperator::end, (ContainerAccessExpression*)nameExpression, expression());
}

ParseErrors Parser::getParseErrors(){
    return parseErrors;
}

int Parser::getErrorsLine(){
    if (!size) return 0;
    if (pos >= size) return tokens[size - 1] -> getRow();
    return tokens[pos] -> getRow();
}

void Parser::recover(){
    int recPos = pos;
    for(int i = recPos; i <= size; ++i){
        pos = i;
        try{
            statement();
            pos = i;
            return;
        }catch(std::exception* ex){}
    }
}

Statement* Parser::parse(){
    parseErrors.clear();
    BlockStatement* block = new BlockStatement();
    while(!match(TokenType::END_OF_FILE)){
        try{
            block -> add(statement());
        }catch(std::exception* ex){
            parseErrors.add(ex, getErrorsLine());
            recover();
        }
    }
    return block;
}

Statement* Parser::statementOrBlock(){
    if (lookMatch(0, TokenType::LBRACE)) return block();
    else return statement();
}

Statement* Parser::block(){
    BlockStatement* block = new BlockStatement();
    consume(TokenType::LBRACE);
    while(!match(TokenType::RBRACE)){
        block -> add(statement());
    }
    return block;
}

Statement* Parser::statement(){
    if (match(TokenType::PRINT)) return new PrintStatement(expression());
    if (match(TokenType::PRINTLN)) return new PrintlnStatement(expression());
    if (match(TokenType::IF)) return ifelseStatement();
    if (match(TokenType::WHILE)) return whileStatement();
    if (match(TokenType::DO)) return doWhileStatement();
    if (match(TokenType::FOR)) return forStatement();
    if (match(TokenType::BREAK)) return new BreakStatement();
    if (match(TokenType::CONTINUE)) return new ContinueStatement();
    if (match(TokenType::RETURN)) return new ReturnStatement(expression());
    if (match(TokenType::THROW)) return new ThrowStatement(expression());
    if (match(TokenType::TRY)) return tryStatement();
    if (match(TokenType::SWITCH)) return switchStatement();
    if (match(TokenType::CLASS)) return classDeclaration();
    if (match(TokenType::GRIDGRID)) return integrationStatement();
    if (match(TokenType::IMPORT)) return importStatement();
    if (match(TokenType::DEF)) return functionDefine();
    return exprStatement();
}

Statement* Parser::ifelseStatement(){
    Expression* condition = expression();
    Statement* ifstatement = statementOrBlock();
    Statement* elsestatement;
    if(match(TokenType::ELSE)) elsestatement = statementOrBlock();
    else if (match(TokenType::ELIF)) elsestatement = ifelseStatement();
    else elsestatement = nullptr;
    return new IfStatement(condition, ifstatement, elsestatement);
}

Statement* Parser::whileStatement(){
    Expression* condition = expression();
    Statement* statement = statementOrBlock();
    return new WhileStatement(condition, statement);
}

Statement* Parser::doWhileStatement(){
    Statement* statement = statementOrBlock();
    consume(TokenType::WHILE);
    Expression* condition = expression();
    return new DoWhileStatement(condition, statement);
}

Statement* Parser::forStatement(){
    int foreachIndex = lookMatch(0, TokenType::LPAREN) ? 1 : 0;
    if (lookMatch(foreachIndex, TokenType::WORD) && lookMatch(foreachIndex + 1, TokenType::COLON)){
        return foreachArrayStatement();
    }
    if (lookMatch(foreachIndex, TokenType::WORD) && lookMatch(foreachIndex + 1, TokenType::COMMA) &&
        lookMatch(foreachIndex + 2, TokenType::WORD) && lookMatch(foreachIndex + 3, TokenType::COLON)){
        return foreachMapStatement();
    }
    bool openParen = match(TokenType::LPAREN);
    Statement* initialization = exprStatement();
    consume(TokenType::COMMA);
    Expression* termination = expression();
    consume(TokenType::COMMA);
    Statement* increment = exprStatement();
    if (openParen) consume(TokenType::RPAREN);
    Statement* statement = statementOrBlock();
    return new ForStatement(initialization, termination, increment, statement);
}

ForeachArrayStatement* Parser::foreachArrayStatement(){
    bool openParen = match(TokenType::LPAREN);
    std::string variable = consume(TokenType::WORD) -> getText();
    consume(TokenType::COLON);
    Expression* container = expression();
    if (openParen) consume(TokenType::RPAREN);
    Statement* statement = statementOrBlock();
    return new ForeachArrayStatement(variable, container, statement);
}

ForeachMapStatement* Parser::foreachMapStatement(){
    bool openParen = match(TokenType::LPAREN);
    std::string key = consume(TokenType::WORD) -> getText();
    consume(TokenType::COMMA);
    std::string value = consume(TokenType::WORD) -> getText();
    consume(TokenType::COLON);
    Expression* container = expression();
    if (openParen) consume(TokenType::RPAREN);
    Statement* statement = statementOrBlock();
    return new ForeachMapStatement(key, value, container, statement);
}

Statement* Parser::tryStatement(){
    Statement* body = statementOrBlock();
    if (lookMatch(0, TokenType::CATCH) && lookMatch(1, TokenType::WORD)){
        consume(TokenType::CATCH);
        std::string name = consume(TokenType::WORD) -> getText();
        return new TryStatement(body, name, statementOrBlock());
    }
    else throw new ParseException("Catch block not found after try block");
}

Statement* Parser::switchStatement(){
    Expression* start = expression();
    bool openParen, defaultLabel = false;
    openParen = match(TokenType::LBRACE);
    std::vector<std::pair<Expression*, Statement*>> body;
    Statement* defaultCase = nullptr;
    while(true){
        if (match(TokenType::CASE)){
            Expression* condition = expression();
            consume(TokenType::COLON);
            Statement* casestatement = statementOrBlock();
            body.push_back(std::pair<Expression*, Statement*>(condition, casestatement));
        }
        else if (match(TokenType::DEFAULT)){
            if (!defaultLabel){
                defaultLabel = true;
                consume(TokenType::COLON);
                defaultCase = statementOrBlock();
            }
            else throw std::logic_error("Multiple default in one switch");
        }
        else break;
    }
    if (!openParen && (body.size() + (defaultCase != nullptr)) > 1) throw std::logic_error("Missing open tag for switch");
    if (openParen) consume(TokenType::RBRACE);
    return new SwitchStatement(start, body, defaultCase);
}

Statement* Parser::classDeclaration(){
    std::string name = consume(TokenType::WORD) -> getText();
    ClassDeclarationsStatement* classDeclaration = new ClassDeclarationsStatement(name);
    consume(TokenType::LBRACE);
    do{
        if (match(TokenType::DEF)) classDeclaration -> addMethod(functionDefine());
        else{
            std::vector<std::string> names;
            while(lookMatch(0, TokenType::WORD) && lookMatch(1, TokenType::EQ)){
                names.push_back(consume(TokenType::WORD) -> getText());
                consume(TokenType::EQ);
            }
            if (names.empty()) throw new ParseException("Class can only assignments and declarations");
            Expression* expr = expression();
            if (expr != nullptr) classDeclaration -> addField(names, expr);
            else throw new ParseException("Class can only assignments and declarations");
        }
    }while(!match(TokenType::RBRACE));
    return classDeclaration;
}

Statement* Parser::integrationStatement(){
    std::string lang = consume(TokenType::WORD) -> getText();
    consume(TokenType::AS);
    std::string name = consume(TokenType::WORD) -> getText();
    consume(TokenType::LBRACE);
    std::string code = consume(TokenType::TEXT) -> getText();
    consume(TokenType::RBRACE);
    return new IntegrationStatement(lang, name, code);
}

Statement* Parser::importStatement(){
    std::vector<std::string> modules;
    if (lookMatch(0, TokenType::WORD)) modules.push_back(consume(TokenType::WORD) -> getText());
    else if (match(TokenType::LBRACKET)){
        while(true){
            modules.push_back(consume(TokenType::WORD) -> getText());
            if (match(TokenType::RBRACKET)) break;
            consume(TokenType::COMMA);
        }
    }
    if (modules.empty()) throw new ParseException("Unknown syntax for import");
    std::string name;
    if (match(TokenType::AS)) name = consume(TokenType::WORD) -> getText();
    return new ImportStatement(modules, name);
}

Arguments Parser::functionArguments(){
    consume(TokenType::LPAREN);
    Arguments args = Arguments();
    bool startOption = false, arrayArguments = false;
    while(!match(TokenType::RPAREN)){
        bool star = match(TokenType::STAR);
        std::string s = consume(TokenType::WORD) -> getText();
        if (star){
            if (arrayArguments) throw new ParseException("Two or more array argument");
            arrayArguments = true;
            args.addArrayArgument(s);
        }
        else if (arrayArguments) throw new ParseException("Argument cannot be after array argument");
        else if (match(TokenType::EQ)){
            startOption = true;
            args.addOptional(s, expression());
        }
        else if (!startOption) args.addRequired(s);
        else throw new ParseException("Required argument cannot be after optional");
        if (match(TokenType::RPAREN)) break;
        else consume(TokenType::COMMA);
    }
    return args;
}

Statement* Parser::functionBody(){
    if (match(TokenType::EQ)) return new ReturnStatement(expression());
    return statementOrBlock();
}

FunctionDefineStatement* Parser::functionDefine(){
    std::string name = consume(TokenType::WORD) -> getText();
    Arguments args = functionArguments();
    Statement* body = functionBody();
    return new FunctionDefineStatement(name, args, body);
}

std::vector<Expression*> Parser::functionCallArguments(){
    std::vector<Expression*> args;
    consume(TokenType::LPAREN);
    while(!match(TokenType::RPAREN)){
        args.push_back(expression());
        if (match(TokenType::RPAREN)) break;
        consume(TokenType::COMMA);
    }
    return args;
}

FunctionalExpression* Parser::function(Expression* nameExpression){
    FunctionalExpression* function = new FunctionalExpression(nameExpression);
    std::vector<Expression*> args = functionCallArguments();
    for(Expression* now : args) function -> addArguments(now);
    return function;
}

Statement* Parser::exprStatement(){
    Expression* expr = expression();
    if (expr != nullptr) return new ExprStatement(expr);
    throw new ParseException("Unknown statement: " + std::string(*(get(0))));
}

Expression* Parser::expression(){
    return assignment();
}

Expression* Parser::assignment(){
    if (lookMatch(0, TokenType::WORD)){
        ASSIGN_TO_WORD(EQ, ASSIGN)
        ASSIGN_TO_WORD(PLUSEQ, ADD)
        ASSIGN_TO_WORD(MINUSEQ, SUBSTRACT)
        ASSIGN_TO_WORD(STAREQ, MULTIPLY)
        ASSIGN_TO_WORD(SLASHEQ, DIVIDE)
        ASSIGN_TO_WORD(PERCENTEQ, REMAINDER)
        ASSIGN_TO_WORD(STARSTAREQ, POWER)
        ASSIGN_TO_WORD(LTLTEQ, LSHIFT)
        ASSIGN_TO_WORD(GTGTEQ, RSHIFT)
        ASSIGN_TO_WORD(BAREQ, OR)
        ASSIGN_TO_WORD(AMPEQ, AND)
        ASSIGN_TO_WORD(CARETEQ, XOR)
        if(lookMatch(1, TokenType::PLUSPLUS)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::PLUSPLUS);
            return new AssignmentExpression(AssignmentOperator::_PLUSPLUS, variable, new ValueExpression(Bignum(1)));
        }
        if(lookMatch(1, TokenType::MINUSMINUS)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::MINUSMINUS);
            return new AssignmentExpression(AssignmentOperator::_MINUSMINUS, variable, new ValueExpression(Bignum(1)));
        }
    }
    Expression* nameExpression = ternary();
    if (nameExpression != nullptr && nameExpression -> type() == Expressions::ContainerAccessExpression){
        ASSIGN_TO_CONTAINER(EQ, ASSIGN)
        ASSIGN_TO_CONTAINER(PLUSEQ, ADD)
        ASSIGN_TO_CONTAINER(MINUSEQ, SUBSTRACT)
        ASSIGN_TO_CONTAINER(STAREQ, MULTIPLY)
        ASSIGN_TO_CONTAINER(SLASHEQ, DIVIDE)
        ASSIGN_TO_CONTAINER(PERCENTEQ, REMAINDER)
        ASSIGN_TO_CONTAINER(STARSTAREQ, POWER)
        ASSIGN_TO_CONTAINER(LTLTEQ, LSHIFT)
        ASSIGN_TO_CONTAINER(GTGTEQ, RSHIFT)
        ASSIGN_TO_CONTAINER(BAREQ, OR)
        ASSIGN_TO_CONTAINER(AMPEQ, AND)
        ASSIGN_TO_CONTAINER(CARETEQ, XOR)
        if (match(TokenType::PLUSPLUS)) return new ContainerAssignmentExpression(AssignmentOperator::_PLUSPLUS, (ContainerAccessExpression*)nameExpression, new ValueExpression(Bignum(1)));
        if (match(TokenType::MINUSMINUS)) return new ContainerAssignmentExpression(AssignmentOperator::_MINUSMINUS, (ContainerAccessExpression*)nameExpression, new ValueExpression(Bignum(1)));
    }
    return nameExpression;
}

Expression* Parser::ternary(){
    Expression* result = logicalOr();
    while(true){
        if (match(TokenType::QUESTION)){
            Expression* trueExpr = expression();
            consume(TokenType::COLON);
            Expression* falseExpr = expression();
            result = new TernaryExpression(result, trueExpr, falseExpr);
        }
        else break;
    }
    return result;
}

Expression* Parser::logicalOr(){
    Expression* result = logicalAnd();
    while(true){
        if (match(TokenType::BARBAR)){
            result = new ConditionalExpression(ConditionalOperator::OR, result, logicalAnd());
        }
        else break;
    }
    return result;
}

Expression* Parser::logicalAnd(){
    Expression* result = bitOr();
    while(true){
        if (match(TokenType::AMPAMP)){
            result = new ConditionalExpression(ConditionalOperator::AND, result, bitOr());
        }
        else break;
    }
    return result;
}

Expression* Parser::bitOr(){
    Expression* result = bitXor();
    while(true){
        if (match(TokenType::BAR)){
            result = new BinaryExpression(BinaryOperator::OR, result, bitXor());
        }
        else break;
    }
    return result;
}

Expression* Parser::bitXor(){
    Expression* result = bitAnd();
    while(true){
        if (match(TokenType::CARET)){
            result = new BinaryExpression(BinaryOperator::XOR, result, bitAnd());
        }
        else break;
    }
    return result;
}

Expression* Parser::bitAnd(){
    Expression* result = equality();
    while(true){
        if (match(TokenType::AMP)){
            result = new BinaryExpression(BinaryOperator::AND, result, equality());
        }
        else break;
    }
    return result;
}

Expression* Parser::equality(){
    Expression* result = conditional();
    if (match(TokenType::EQEQ)) return new ConditionalExpression(ConditionalOperator::EQUALS, result, conditional());
    else if (match(TokenType::EXCLEQ)) return new ConditionalExpression(ConditionalOperator::NOT_EQUALS, result, conditional());
    else return result;
}

Expression* Parser::conditional(){
    Expression* result = shift();
    while(true){
        if (match(TokenType::LT)) result = new ConditionalExpression(ConditionalOperator::LT, result, shift());
        else if (match(TokenType::LTEQ)) result = new ConditionalExpression(ConditionalOperator::LTEQ, result, shift());
        else if (match(TokenType::GT)) result = new ConditionalExpression(ConditionalOperator::GT, result, shift());
        else if (match(TokenType::GTEQ)) result = new ConditionalExpression(ConditionalOperator::GTEQ, result, shift());
        else break;
    }
    return result;
}

Expression* Parser::shift(){
    Expression* result = additive();
    while(true){
        if (match(TokenType::LTLT)) result = new BinaryExpression(BinaryOperator::LSHIFT, result, additive());
        else if (match(TokenType::GTGT)) result = new BinaryExpression(BinaryOperator::RSHIFT, result, additive());
        else break;
    }
    return result;
}

Expression* Parser::additive(){
    Expression* result = multiplicative();
    while(true){
        if (match(TokenType::PLUS)) result = new BinaryExpression(BinaryOperator::ADD, result, multiplicative());
        else if (match(TokenType::MINUS)) result = new BinaryExpression(BinaryOperator::SUBSTRACT, result, multiplicative());
        else break;
    }
    return result;
}

Expression* Parser::multiplicative(){
    Expression* result = objectCreation();
    while(true){
        if (match(TokenType::STAR)) result = new BinaryExpression(BinaryOperator::MULTIPLY, result, objectCreation());
        else if (match(TokenType::SLASH)) result = new BinaryExpression(BinaryOperator::DIVIDE, result, objectCreation());
        else if (match(TokenType::PERCENT)) result = new BinaryExpression(BinaryOperator::REMAINDER, result, objectCreation());
        else break;
    }
    return result;
}

Expression* Parser::objectCreation(){
    if (match(TokenType::NEW)){
        std::string className = consume(TokenType::WORD) -> getText();
        std::vector<Expression*> args = functionCallArguments();
        return new ObjectCreationExpression(className, args);
    }
    return unary();
}

Expression* Parser::unary(){
    if (match(TokenType::MINUS)) return new UnaryExpression(UnaryOperator::NEGATIVE, unary());
    if (match(TokenType::PLUS)) return new UnaryExpression(UnaryOperator::PLUS, unary());
    if (match(TokenType::EXCL)) return new UnaryExpression(UnaryOperator::NOT, unary());
    if (match(TokenType::TILDE)) return new UnaryExpression(UnaryOperator::COMPLEMENT, unary());
    if (match(TokenType::PLUSPLUS)){
        Expression* prim = unary();
        if (prim -> type() == Expressions::ContainerAccessExpression) return new ContainerAssignmentExpression(AssignmentOperator::PLUSPLUS_, (ContainerAccessExpression*)prim, new ValueExpression(Bignum(1)));
        else if (prim -> type() == Expressions::VariableExpression) return new AssignmentExpression(AssignmentOperator::PLUSPLUS_, ((VariableExpression*) prim) -> name, new ValueExpression(Bignum(1)));
        return new UnaryExpression(UnaryOperator::PLUSPLUS, prim);
    }
    if (match(TokenType::MINUSMINUS)){
        Expression* prim = unary();
        if (prim -> type() == Expressions::ContainerAccessExpression) return new ContainerAssignmentExpression(AssignmentOperator::MINUSMINUS_, (ContainerAccessExpression*)prim, new ValueExpression(Bignum(1)));
        else if (prim -> type() == Expressions::VariableExpression) return new AssignmentExpression(AssignmentOperator::MINUSMINUS_, ((VariableExpression*) prim) -> name, new ValueExpression(Bignum(1)));
        return new UnaryExpression(UnaryOperator::MINUSMINUS, prim);
    }
    return exponential();
}

Expression* Parser::exponential(){
    Expression* left = primaryWithSuffix();
    if (match(TokenType::STARSTAR)) return new BinaryExpression(BinaryOperator::POWER, left, unary());
    return left;
}

Expression* Parser::primaryWithSuffix(){
    if (match(TokenType::DEF)){
        Arguments args = functionArguments();
        Statement* body = functionBody();
        return new ValueExpression(new UserDefinedFunction(args, body));
    }
    return suffix(primary());
}

Expression* Parser::primary(){
    if (match(TokenType::LPAREN)){
        Expression* result = expression();
        consume(TokenType::RPAREN);
        return result;
    }
    return value();
}

Expression* Parser::value(){
    if (lookMatch(0, TokenType::LBRACKET)) return array();
    if (lookMatch(0, TokenType::LBRACE)) return map();
    Token* current = get(0);
    if (match(TokenType::WORD)) return new VariableExpression(current -> getText());
    if (match(TokenType::TEXT)) return new ValueExpression(current -> getText());;
    if (match(TokenType::NUMBER)) return new ValueExpression(new NumberValue(current -> getText()));
    if (match(TokenType::HEX_NUMBER)){
        Bignum big = 0;
        std::string str = current -> getText();
        for(unsigned i = 0; i < str.size(); ++i){
            big *= 16;
            if (isdigit(str[i])) big += str[i] - '0';
            else if (str[i] >= 'A' && str[i] <= 'F') big += str[i] - 'A' + 10;
            else if (str[i] >= 'a' && str[i] <= 'f') big += str[i] - 'a' + 10;
        }
        return new ValueExpression(new NumberValue(big));
    }
    throw new ParseException("Unknown expression: " + std::string(*current));
}

Expression* Parser::array(){
    consume(TokenType::LBRACKET);
    std::vector<Expression*> elements;
    if (!match(TokenType::RBRACKET)){
        while(true){
            elements.push_back(expression());
            if (match(TokenType::RBRACKET)) break;
            consume(TokenType::COMMA);
        }
    }
    return new ArrayExpression(elements);
}

Expression* Parser::map(){
    consume(TokenType::LBRACE);
    std::map<Expression*, Expression*> elements;
    if (!match(TokenType::RBRACE)){
        while(true){
            Expression* key = expression();
            consume(TokenType::COLON);
            Expression* value = expression();
            elements[key] = value;
            if (match(TokenType::RBRACE)) break;
            consume(TokenType::COMMA);
        }
    }
    return new MapExpression(elements);
}

Expression* Parser::suffix(Expression* root){
    while(true){
        if (match(TokenType::DOT)){
            root = new ContainerAccessExpression(root,
                        new ContainerAccessElement(new ValueExpression(consume(TokenType::WORD) -> getText()), true) );
        }
        else if (match(TokenType::LBRACKET)){
            root = new ContainerAccessExpression(root, new ContainerAccessElement(expression(), false) );
            consume(TokenType::RBRACKET);
        }
        else if (lookMatch(0, TokenType::LPAREN)){
            root = function(root);
        }
        else break;
    }
    return root;
}

Token* Parser::get(int position){
    int now = pos + position;
    if (now >= size) return new Token(TokenType::END_OF_FILE, "");
    else return tokens[now];
}

bool Parser::lookMatch(int position, TokenType type){
    return get(position) -> getType() == type;
}

bool Parser::match(TokenType type){
    Token* current = get(0);
    if (type != current -> getType()) return false;
    ++pos;
    return true;
}

Token* Parser::consume(TokenType type){
    Token* current = get(0);
    if (type != current -> getType()){
        std::string str = "Token " + std::string(*current) + " does not match " + std::string(Token(type, ""));
        throw new ParseException(str);
    }
    ++pos;
    return current;
}

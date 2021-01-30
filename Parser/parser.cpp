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
    if (match(TokenType::FOR)) return forStatement();
    if (match(TokenType::DO)) return doWhileStatement();
    if (match(TokenType::BREAK)) return new BreakStatement();
    if (match(TokenType::CONTINUE)) return new ContinueStatement();
    if (match(TokenType::RETURN)) return new ReturnStatement(expression());
    if (match(TokenType::DEF)) return functionDefine();
    if (match(TokenType::IMPORT)) return importStatement();
    if (match(TokenType::SWITCH)) return switchStatement();
    if (lookMatch(0, TokenType::WORD) && lookMatch(1, TokenType::LPAREN)){
        return new ExprStatement(functionChain(qualifiedName()));
    }
    if (match(TokenType::THROW)) return new ThrowStatement(expression());
    if (match(TokenType::TRY)) return tryStatement();
    if (match(TokenType::CLASS)) return classDeclaration();
    return assignmentStatement();
}

Statement* Parser::assignmentStatement(){
    Expression* expr = expression();
    if (expr != nullptr) return new ExprStatement(expr);
    throw new ParseException("Unknown statement: " + std::string(*(get(0))));
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
    Statement* initialization = assignmentStatement();
    consume(TokenType::COMMA);
    Expression* termination = expression();
    consume(TokenType::COMMA);
    Statement* increment = assignmentStatement();
    if (openParen) match(TokenType::RPAREN);
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

Statement* Parser::tryStatement(){
    Statement* body = statementOrBlock();
    if (lookMatch(0, TokenType::CATCH) && lookMatch(1, TokenType::WORD)){
        consume(TokenType::CATCH);
        std::string name = consume(TokenType::WORD) -> getText();
        return new TryStatement(body, name, statementOrBlock());
    }
    else throw new ParseException("Catch block not found after try block");
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

Expression* Parser::functionChain(Expression* nameExpression){              /// rec: function()
    Expression* expr = function(nameExpression);                        // name()
    if (lookMatch(0, TokenType::LPAREN)) return functionChain(expr);    // 'name()'() = ''()
    if (lookMatch(0, TokenType::DOT)){                                  // name(). ...
        std::vector<ContainerAccessElement> indices = variableSuffix();
        if (!indices.size()) return expr;
        if (lookMatch(0, TokenType::LPAREN)) return functionChain(new ContainerAccessExpression(expr, indices));
        return new ContainerAccessExpression(expr, indices);
    }
    return expr;
}

FunctionalExpression* Parser::function(Expression* nameExpression){         /// name(args)
    consume(TokenType::LPAREN);
    FunctionalExpression* function = new FunctionalExpression(nameExpression);
    while(!match(TokenType::RPAREN)){
        function -> addArguments(expression());
        if (match(TokenType::RPAREN)) break;
        consume(TokenType::COMMA);
    }
    return function;
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
            Expression* key = primary();
            consume(TokenType::COLON);
            Expression* value = expression();
            elements[key] = value;
            if (match(TokenType::RBRACE)) break;
            consume(TokenType::COMMA);
        }
    }
    return new MapExpression(elements);
}

Statement* Parser::classDeclaration(){
    std::string name = consume(TokenType::WORD) -> getText();
    ClassDeclarationsStatement* classDeclaration = new ClassDeclarationsStatement(name);
    consume(TokenType::LBRACE);
    do{
        if (match(TokenType::DEF)) classDeclaration -> addMethod(functionDefine());
        else{
            Expression* expression = assignmentStrict();
            if (expression != nullptr) classDeclaration -> addField((AssignmentExpression*) expression);
            else throw new ParseException("Class can only assignments and declarations");
        }
    }while(!match(TokenType::RBRACE));
    return classDeclaration;
}

Expression* Parser::expression(){
    return assignment();
}

Expression* Parser::assignment(){
    Expression* assignment = assignmentStrict();
    if (assignment == nullptr) return ternary();
    else return assignment;
}

Expression* Parser::assignmentStrict(){
    if (lookMatch(0, TokenType::WORD)){
        if(lookMatch(1, TokenType::EQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::EQ);
            return new AssignmentExpression(AssignmentOperator::ASSIGN, variable, expression());
        }
        if(lookMatch(1, TokenType::PLUSEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::PLUSEQ);
            return new AssignmentExpression(AssignmentOperator::ADD, variable, expression());
        }
        if(lookMatch(1, TokenType::MINUSEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::MINUSEQ);
            return new AssignmentExpression(AssignmentOperator::SUBSTRACT, variable, expression());
        }
        if(lookMatch(1, TokenType::STAREQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::STAREQ);
            return new AssignmentExpression(AssignmentOperator::MULTIPLY, variable, expression());
        }
        if(lookMatch(1, TokenType::SLASHEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::SLASHEQ);
            return new AssignmentExpression(AssignmentOperator::DIVIDE, variable, expression());
        }
        if(lookMatch(1, TokenType::PERCENTEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::PERCENTEQ);
            return new AssignmentExpression(AssignmentOperator::REMAINDER, variable, expression());
        }
        if(lookMatch(1, TokenType::STARSTAREQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::STARSTAREQ);
            return new AssignmentExpression(AssignmentOperator::POWER, variable, expression());
        }
        if(lookMatch(1, TokenType::LTLTEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::LTLTEQ);
            return new AssignmentExpression(AssignmentOperator::LSHIFT, variable, expression());
        }
        if(lookMatch(1, TokenType::GTGTEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::GTGTEQ);
            return new AssignmentExpression(AssignmentOperator::RSHIFT, variable, expression());
        }
        if(lookMatch(1, TokenType::BAREQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::BAREQ);
            return new AssignmentExpression(AssignmentOperator::OR, variable, expression());
        }
        if(lookMatch(1, TokenType::AMPEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::AMPEQ);
            return new AssignmentExpression(AssignmentOperator::AND, variable, expression());
        }
        if(lookMatch(1, TokenType::CARETEQ)){
            std::string variable = consume(TokenType::WORD) -> getText();
            consume(TokenType::CARETEQ);
            return new AssignmentExpression(AssignmentOperator::XOR, variable, expression());
        }
    }
    /** Add AssignmentOperator :: _PLUSPLUS and _MINUSMINUS **/
    int position = pos;
    Expression* nameExpression = qualifiedName();
    if (nameExpression != nullptr && nameExpression -> type() == Expressions::ContainerAccessExpression){
        if (match(TokenType::EQ)) return new ContainerAssignmentExpression(AssignmentOperator::ASSIGN, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::PLUSEQ)) return new ContainerAssignmentExpression(AssignmentOperator::ADD, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::MINUSEQ)) return new ContainerAssignmentExpression(AssignmentOperator::SUBSTRACT, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::STAREQ)) return new ContainerAssignmentExpression(AssignmentOperator::MULTIPLY, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::SLASHEQ)) return new ContainerAssignmentExpression(AssignmentOperator::DIVIDE, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::PERCENTEQ)) return new ContainerAssignmentExpression(AssignmentOperator::REMAINDER, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::STARSTAREQ)) return new ContainerAssignmentExpression(AssignmentOperator::POWER, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::LTLTEQ)) return new ContainerAssignmentExpression(AssignmentOperator::LSHIFT, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::GTGTEQ)) return new ContainerAssignmentExpression(AssignmentOperator::RSHIFT, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::BAREQ)) return new ContainerAssignmentExpression(AssignmentOperator::OR, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::AMPEQ)) return new ContainerAssignmentExpression(AssignmentOperator::AND, (ContainerAccessExpression*)nameExpression, expression());
        if (match(TokenType::CARETEQ)) return new ContainerAssignmentExpression(AssignmentOperator::XOR, (ContainerAccessExpression*)nameExpression, expression());
    }
    pos = position;
    return nullptr;
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
        std::vector<Expression*> args;
        consume(TokenType::LPAREN);
        while(!match(TokenType::RPAREN)){
            args.push_back(expression());
            match(TokenType::COMMA);
        }
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
    Expression* left = primary();
    if (match(TokenType::STARSTAR)) return new BinaryExpression(BinaryOperator::POWER, left, unary());
    return left;
}

Expression* Parser::primary(){          /// () | :: | lambda
    if (match(TokenType::LPAREN)){
        Expression* result = expression();
        consume(TokenType::RPAREN);
        return result;
    }
    if (match(TokenType::COLONCOLON)){      /// [[maybe_unused]]
        std::string name = consume(TokenType::WORD) -> getText();
        return new FunctionReferenceExpression(name);
    }
    if (match(TokenType::DEF)){
        Arguments args = functionArguments();
        Statement* body = functionBody();
        return new ValueExpression(new UserDefinedFunction(args, body));
    }
    return variable();
}

Expression* Parser::variable(){         /// name() | 'q.name'() | 'q.name' ++ / -- | [...] | {...}
    if (lookMatch(0, TokenType::WORD) && lookMatch(1, TokenType::LPAREN)){
        return functionChain(new ValueExpression(consume(TokenType::WORD) -> getText()));
    }
    Expression* nameExpression = qualifiedName();
    if (nameExpression != nullptr){
        if (lookMatch(0, TokenType::LPAREN)) return functionChain(nameExpression);
        if (nameExpression -> type() == Expressions::ContainerAccessExpression){
            if (match(TokenType::PLUSPLUS)) return new ContainerAssignmentExpression(AssignmentOperator::_PLUSPLUS, (ContainerAccessExpression*)nameExpression, new ValueExpression(Bignum(0)));
            if (match(TokenType::MINUSMINUS)) return new ContainerAssignmentExpression(AssignmentOperator::_MINUSMINUS, (ContainerAccessExpression*)nameExpression, new ValueExpression(Bignum(0)));
        }
        if (nameExpression -> type() == Expressions::VariableExpression){
            if (match(TokenType::PLUSPLUS)) return new AssignmentExpression(AssignmentOperator::_PLUSPLUS, ((VariableExpression*) nameExpression) -> name, new ValueExpression(Bignum(0)));
            if (match(TokenType::MINUSMINUS)) return new AssignmentExpression(AssignmentOperator::_MINUSMINUS, ((VariableExpression*) nameExpression) -> name, new ValueExpression(Bignum(0)));
        }
        return nameExpression;
    }
    if (lookMatch(0, TokenType::LBRACKET)){
        Expression* _array = array();
        return primarySuffix(_array);
    }
    if (lookMatch(0, TokenType::LBRACE)){
        Expression* _map = map();
        return primarySuffix(_map);
    }
    return value();
}

Expression* Parser::value(){            /// 123 | #2F3C53 | "..."
    Token* current = get(0);
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
        return new ValueExpression(NumberValue(big));
    }
    if (match(TokenType::TEXT)){
        ValueExpression* stringExpr = new ValueExpression(current -> getText());
        return primarySuffix(stringExpr);
    }
    throw new ParseException("Unknown expression: " + current -> getText());
}

Expression* Parser::qualifiedName(){        /// word 'var.Suffix'
    Token* current = get(0);
    if (!match(TokenType::WORD)) return nullptr;
    std::vector<ContainerAccessElement> indices = variableSuffix();
    if (!indices.size()) return new VariableExpression(current -> getText());
    return new ContainerAccessExpression(current -> getText(), indices);
}

std::vector<ContainerAccessElement> Parser::variableSuffix(){   /// .---[---]
    std::vector<ContainerAccessElement> indices;
    while(lookMatch(0, TokenType::DOT) || lookMatch(0, TokenType::LBRACKET)){
        if (match(TokenType::DOT)){
            indices.push_back(ContainerAccessElement(new ValueExpression(consume(TokenType::WORD) -> getText()), true));
        }
        if (match(TokenType::LBRACKET)){
            indices.push_back(ContainerAccessElement(expression(), false));
            consume(TokenType::RBRACKET);
        }
    }
    return indices;
}

Expression* Parser::primarySuffix(Expression* root){            /// primary 'var.Suffix' | primary.name() | primary
     if (lookMatch(0, TokenType::DOT) && lookMatch(1, TokenType::WORD) && lookMatch(2, TokenType::LPAREN)){
        match(TokenType::DOT);
        return functionChain(new ContainerAccessExpression(root, std::vector<ContainerAccessElement>{
            ContainerAccessElement(new ValueExpression(consume(TokenType::WORD) -> getText()), true)
            }));
    }
    std::vector<ContainerAccessElement> indices = variableSuffix();
    if (!indices.size()) return root;
    return new ContainerAccessExpression(root, indices);
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
        std::string str = "Token " + std::string(*current) + " does not match ";
        throw new ParseException(str);
    }
    ++pos;
    return current;
}

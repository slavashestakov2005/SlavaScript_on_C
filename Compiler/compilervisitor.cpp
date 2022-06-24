#include "compilervisitor.h"
#include "compiler.h"
#include "../Statement/all.h"
#include "../Expression/all.h"
#include <set>

using namespace SlavaScript::compiler;


namespace{
    std::set<std::string> variables;

    void add(std::string name){
        variables.insert(name);
    }

    bool isExists(std::string name){
        return variables.find(name) != variables.cend();
    }
}


void CompilerVisitor::visit(lang::BlockStatement* v){
    if (Compiler::getTabsCount() == 0){
        Compiler::write("int main(){");
        Compiler::incrementTabsCount();
    }
    for(int i = 0; i < v -> statements.size(); ++i){
        v -> statements[i] -> accept(this);
    }
    if (Compiler::getTabsCount() == 1){
        Compiler::write("return 0;");
        Compiler::decrementTabsCount();
        Compiler::write("}");
    }
}

void CompilerVisitor::visit(lang::BreakStatement* v){
    Compiler::write("throw new BreakStatement();");
}

void CompilerVisitor::visit(lang::ClassDeclarationsStatement* v){}

void CompilerVisitor::visit(lang::ContinueStatement* v){
    Compiler::write("throw new ContinueStatement();");
}

void CompilerVisitor::visit(lang::DoWhileStatement* v){
    Compiler::write("do{");
    Compiler::enterLoop();
    v -> body -> accept(this);
    Compiler::goOutLoop();
    Compiler::write("} while(", false);
    v -> condition -> accept(this);
    Compiler::append(")");
}

void CompilerVisitor::visit(lang::ExprStatement* v){
    Compiler::write("", false);
    v -> expression -> accept(this);
    Compiler::append(";");
}

void CompilerVisitor::visit(lang::ForeachArrayStatement* v){
    Compiler::write("for(Value* " + v -> variable + " : ", false);
    v -> container -> accept(this);
    Compiler::append("){");
    Compiler::enterLoop();
    v -> body -> accept(this);
    Compiler::goOutLoop();
    Compiler::write("}");
}

void CompilerVisitor::visit(lang::ForeachMapStatement* v){}

void CompilerVisitor::visit(lang::ForStatement* v){
    Compiler::write("for(", false);
    v -> initialization -> accept(this);
    Compiler::append("; ", false);
    v -> termination -> accept(this);
    Compiler::append("; ", false);
    v -> increment -> accept(this);
    Compiler::append("){");
    Compiler::enterLoop();
    v -> body -> accept(this);
    Compiler::goOutLoop();
    Compiler::write("}");
}

void CompilerVisitor::visit(lang::FunctionDefineStatement* v){}

void CompilerVisitor::visit(lang::IfStatement* v){
    Compiler::write("if (", false);
    v -> expression -> accept(this);
    Compiler::append("){");
    Compiler::incrementTabsCount();
    v -> ifStatement -> accept(this);
    Compiler::decrementTabsCount();
    if (v -> elseStatement != nullptr){
        Compiler::write("} else{");
        Compiler::incrementTabsCount();
        v -> elseStatement -> accept(this);
        Compiler::decrementTabsCount();
    }
    Compiler::write("}");
}

void CompilerVisitor::visit(lang::IntegrationStatement* v){}

void CompilerVisitor::visit(lang::ImportStatement* v){}

void CompilerVisitor::visit(lang::PrintlnStatement* v){
    Compiler::write("std::cout << ", false);
    v -> expression -> accept(this);
    Compiler::append(" << std::endl;");
}

void CompilerVisitor::visit(lang::PrintStatement* v){
    Compiler::write("std::cout << ", false);
    v -> expression -> accept(this);
    Compiler::append(";");
}

void CompilerVisitor::visit(lang::ReturnStatement* v){
    Compiler::write("return ", false);
    v -> expression -> accept(this);
    Compiler::append(";");
}

void CompilerVisitor::visit(lang::SwitchStatement* v){
    Compiler::write("SlavaScript::compiler::switch_function(", false);
    v -> start -> accept(this);
    Compiler::append(", {");
    Compiler::incrementTabsCount();
    for (int i = 0; i < v -> body.size(); ++i){
        Compiler::write("{", false);
        v -> body[i].first -> accept(this);
        Compiler::append(", [&]() -> void{");
        Compiler::incrementTabsCount();
        v -> body[i].second -> accept(this);
        Compiler::decrementTabsCount();
        Compiler::write("}},");
    }
    if (v -> defaultCase != nullptr){
        Compiler::write("}, [&]() -> void{");
        Compiler::incrementTabsCount();
        v -> defaultCase -> accept(this);
        Compiler::decrementTabsCount();
        Compiler::write("});");
    }
    else Compiler::write("}, [&]() -> void{});");
    Compiler::decrementTabsCount();
}

void CompilerVisitor::visit(lang::ThrowStatement* v){
    Compiler::write("throw new SlavaScript::lang::ThrowStatement(", false);
    v -> expression -> accept(this);
    Compiler::append(");");
}

void CompilerVisitor::visit(lang::TryStatement* v){
    Compiler::write("try{");
    Compiler::incrementTabsCount();
    v -> body -> accept(this);
    Compiler::decrementTabsCount();
    Compiler::write("} catch(SlavaScript::lang::ThrowStatement* " + v -> name + "){");
    Compiler::incrementTabsCount();
    v -> catchBlock -> accept(this);
    Compiler::decrementTabsCount();
    Compiler::write("}");
}

void CompilerVisitor::visit(lang::WhileStatement* v){
    Compiler::write("while(", false);
    v -> condition -> accept(this);
    Compiler::append("){");
    Compiler::enterLoop();
    v -> body -> accept(this);
    Compiler::goOutLoop();
    Compiler::write("}");
}

void CompilerVisitor::visit(lang::ArrayExpression* v){
    Compiler::append("new SlavaScript::lang::ArrayValue({", false);
    for (int i = 0; i < v -> elements.size(); ++i){
        v -> elements[i] -> accept(this);
        Compiler::append(", ", false);
    }
    Compiler::append("})", false);
}

void CompilerVisitor::visit(lang::AssignmentExpression* v){
    Compiler::append("(", false);
    std::string name = v -> variable;
    if (!isExists(name)){
        Compiler::append("Value* ", false);
        add(name);
    }
    Compiler::append(name + " <assign op> ", false);
    if (v -> expression != nullptr) v -> expression -> accept(this);
    Compiler::append(")", false);
}

void CompilerVisitor::visit(lang::BinaryExpression* v){
    Compiler::append("(", false);
    v -> expr1 -> accept(this);
    Compiler::append(" <binary op> ", false);
    v -> expr2 -> accept(this);
    Compiler::append(")", false);
}

void CompilerVisitor::visit(lang::ConditionalExpression* v){
    Compiler::append("(", false);
    v -> expr1 -> accept(this);
    Compiler::append(" <conditional op> ", false);
    v -> expr2 -> accept(this);
    Compiler::append(")", false);
}

void CompilerVisitor::visit(lang::MapExpression* v){
    Compiler::append("new SlavaScript::lang::MapyValue({", false);
    for (auto now : v -> elements){
        Compiler::append("{", false);
        now.first -> accept(this);
        Compiler::append(", ", false);
        now.second -> accept(this);
        Compiler::append("}, ", false);
    }
    Compiler::append("})", false);
}

void CompilerVisitor::visit(lang::SuffixExpression* v){}

void CompilerVisitor::visit(lang::SuffixAssignmentExpression* v){}

void CompilerVisitor::visit(lang::TernaryExpression* v){
    Compiler::append("((", false);
    v -> condition -> accept(this);
    Compiler::append(") ? (", false);
    v -> trueExpr -> accept(this);
    Compiler::append(") : (", false);
    v -> falseExpr -> accept(this);
    Compiler::append("))", false);
}

void CompilerVisitor::visit(lang::UnaryExpression* v){
    Compiler::append("(<op> ", false);
    v -> expr -> accept(this);
    Compiler::append(")", false);
}

void CompilerVisitor::visit(lang::ValueExpression* v){
    switch(v -> value -> type()){
        case lang::Values::BOOL:{
            Compiler::append(v -> value -> asString(), false);
            break;
        }
        case lang::Values::NUMBER:{
            Compiler::append("new SlavaScript::lang::NumberValue(\"" + v -> value -> asString() + "\")", false);
            break;
        }
        case lang::Values::STRING:{
            Compiler::append("new SlavaScript::lang::StringValue(\"" + v -> value -> asString() + "\")", false);
            break;
        }
        case lang::Values::ARRAY: Compiler::append("ARRAY", false); break;
        case lang::Values::MAP: Compiler::append("MAP", false); break;
        case lang::Values::NULL_:{
            Compiler::append("NULL_", false);
            break;
        }
        case lang::Values::FUNCTION: Compiler::append("FUNCTION", false); break;
        case lang::Values::OBJECT: Compiler::append("OBJECT", false); break;
        case lang::Values::CLASS: Compiler::append("CLASS", false); break;
    }
}

void CompilerVisitor::visit(lang::VariableExpression* v){
    Compiler::append("var : \'" + v -> name + "\'", false);
}

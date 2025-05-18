#include <sstream>

#include <Exception/exceptions.h>
#include <Value/value.h>


using namespace SlavaScript::exceptions;
using SlavaScript::lang::Value;
using SlavaScript::lang::Values;


ArgumentsMismatchException::ArgumentsMismatchException(int expected, int got) {
    std::ostringstream os;
    os << "Arguments count mismatch. Expected " << expected << " arguments, got " << got << ".";
    setText(os.str());
}

ArgumentsMismatchException::ArgumentsMismatchException(std::string expected, int got) {
    std::ostringstream os;
    os << "Arguments count mismatch. Expected " << expected << " arguments, got " << got << ".";
    setText(os.str());
}


CastException::CastException(std::string tp1, std::string tp2) : Exception("Cannot cast " + tp1 + " to " + tp2 + ".") {}
CastException::CastException(Values tp1, Values tp2) : CastException(getValueName(tp1), getValueName(tp2)) {}

LexerException::LexerException(std::string text) { setText(text); }
LexerException::LexerException(std::string text, int row, int col) {
    std::ostringstream os;
    os << "[" << row << ", " << col << "] " << text;
    setText(os.str());
}


LogicException::LogicException(std::string text) : Exception("LogicError : " + text) {}


MathException::MathException(std::string text) : Exception("MathError : " + text) {}


ParseException::ParseException(std::string text) : Exception(text) {}


TypeException::TypeException(std::string info) : Exception(info + ".") {}
TypeException::TypeException(std::string tp1, std::string tp2) : Exception("Expected " + tp1 + " got " + tp2 + ".") {}
TypeException::TypeException(std::string tp1, std::string tp2, std::string info) : Exception("Expected " + tp1 + " got " + tp2 + "." + (info != "" ? " " + info + "." : "")) {}


UnknownClassException::UnknownClassException(std::string text) : Exception("Unknown class " + text) {}


UnknownFunctionException::UnknownFunctionException(std::string text) : Exception("Unknown function " + text) {}


UnknownModuleException::UnknownModuleException(std::string text) : Exception("Unknown module " + text) {}


UnknownOperationException::UnknownOperationException(std::string op, std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
    std::string txt = "Unknown operation " + op;
    if (left != nullptr) txt += " for " + left -> stringType();
    if (right != nullptr) txt += " and " + right -> stringType();
    setText(txt);
}

UnknownOperationException::UnknownOperationException(std::string op, const Value* left, const Value* right) {
    std::string txt = "Unknown operation " + op;
    if (left != nullptr) txt += " for " + left -> stringType();
    if (right != nullptr) txt += " and " + right -> stringType();
    setText(txt);
}


UnknownPropertyException::UnknownPropertyException(std::string text) : Exception("Unknown property " + text) {}


UnknownVariableException::UnknownVariableException(std::string text) : Exception("Unknown variable " + text) {}

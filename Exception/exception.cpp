#include <Exception/exception.h>


using SlavaScript::exceptions::Exception;


Exception::Exception(std::string text) : text(text) {}

void Exception::setText(std::string text) {
    this -> text = text;
}

std::string Exception::msg() const noexcept {
    return text;
}

const char* Exception::what() const noexcept {
    return text.c_str();
}

Exception::~Exception() noexcept {}

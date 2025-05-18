#include <Exception/exceptions.h>
#include <Lib/function.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;

Function::operator std::string() {
    throw CastException(Values::FUNCTION, Values::STRING);
}

std::shared_ptr<Value> Function::operator()(std::vector<std::shared_ptr<Value>> args) {
    return execute(args);
}

Function::~Function() {}

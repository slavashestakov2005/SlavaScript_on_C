#include <Exception/exceptions.h>
#include <Lib/modulefunction.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;


ModuleFunction::ModuleFunction(function_type f) : f(f) {}

std::shared_ptr<Value> ModuleFunction::execute(std::vector<std::shared_ptr<Value>> values) {
    return f(values);
}

ModuleFunction::operator std::string() {
    throw CastException(Values::FUNCTION, Values::STRING);
}

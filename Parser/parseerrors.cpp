#include "parseerrors.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ParseException;

ParseErrors::ParseErrors() {}

void ParseErrors::clear(){
    errors.clear();
}

void ParseErrors::add(ParseException ex, int line){
    errors.push_back(ParseError(line, ex));
}

bool ParseErrors::hasError(){
    return !errors.empty();
}

ParseErrors::operator std::string(){
    std::string result;
    for(int i = 0; i < errors.size(); ++i) result += std::string(errors[i]) + "\n";
    return result;
}

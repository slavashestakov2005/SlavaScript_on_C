#include "parseerrors.h"

using namespace SlavaScript::lang;

void ParseErrors::clear(){
    errors.clear();
}

void ParseErrors::add(std::exception* ex, int line){
    errors.push_back(new ParseError(line, ex));
}

bool ParseErrors::hasError(){
    return !errors.empty();
}

ParseErrors::operator std::string(){
    std::string result;
    for(int i = 0; i < errors.size(); ++i) result += std::string(*(errors[i])) + "\n";
    return result;
}

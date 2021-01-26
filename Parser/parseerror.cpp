#include <sstream>
#include "parseerror.h"

using namespace SlavaScript::lang;

int ParseError::getLine(){
    return line;
}

std::exception* ParseError::getException(){
    return exception;
}

ParseError::operator std::string(){
    std::ostringstream os;
    os << "ParseError on line " << line << ": " << exception -> what();
    return os.str();
}

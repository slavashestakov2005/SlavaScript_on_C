#include "parseerror.h"
#include <sstream>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ParseException;

ParseError::ParseError(int line, ParseException exception) : line(line), exception(exception) {}

int ParseError::getLine(){
    return line;
}

ParseException ParseError::getException(){
    return exception;
}

ParseError::operator std::string(){
    std::ostringstream os;
    os << "ParseError on line " << line << ": " << exception.msg();
    return os.str();
}

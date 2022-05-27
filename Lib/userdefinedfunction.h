#ifndef USERDEFINEDFUNCTION_H_INCLUDED
#define USERDEFINEDFUNCTION_H_INCLUDED

#include "arguments.h"
#include "function.h"
#include "../Statement/statement.h"

namespace SlavaScript::lang{
    class UserDefinedFunction : public Function{
    protected:
        Statement* body;
    public:
        Arguments arguments;
        UserDefinedFunction(Arguments arguments, Statement* body) : arguments(arguments), body(body) { type = true; }
        int getArgsCount();
        std::string getArgsName(int index);
        operator std::string();
        /** @return  throw: ArgumentsMismatchException*. */
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values);
    };
}

#endif // USERDEFINEDFUNCTION_H_INCLUDED

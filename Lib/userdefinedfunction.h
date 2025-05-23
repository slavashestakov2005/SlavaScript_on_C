#pragma once

#include <Lib/arguments.h>
#include <Lib/function.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class UserDefinedFunction : public Function {
    protected:
        Statement* body;
        Arguments arguments;
    public:
        UserDefinedFunction(Arguments arguments, Statement* body);
        int getArgsCount();
        std::string getArgsName(int index);
        operator std::string();
        /** @return  throw: ArgumentsMismatchException*. */
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values);
    };
}

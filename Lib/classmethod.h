#ifndef CLASSMETHOD_H_INCLUDED
#define CLASSMETHOD_H_INCLUDED

#include "userdefinedfunction.h"

namespace SlavaScript::lang{
    class ClassValue;

    class ClassMethod : public UserDefinedFunction{
    private:
        std::shared_ptr<ClassValue> classInstance;
    public:
        ClassMethod(Arguments args, Statement* body, std::shared_ptr<ClassValue> classInstance);
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values);
    };
}

#endif // CLASSMETHOD_H_INCLUDED

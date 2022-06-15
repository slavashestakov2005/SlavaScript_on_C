#ifndef CLASSMETHOD_H_INCLUDED
#define CLASSMETHOD_H_INCLUDED

#include "userdefinedfunction.h"

namespace SlavaScript::lang{
    class ObjectValue;

    class ClassMethod : public UserDefinedFunction{
    public:
        static std::shared_ptr<Value> execute(std::shared_ptr<Function> func, std::vector<std::shared_ptr<Value>> values, std::shared_ptr<Value> classInstance);
        ClassMethod(Arguments args, Statement* body);
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values, std::shared_ptr<ObjectValue> classInstance);
        virtual bool isClassMethod() const { return true; }
    };
}

#endif // CLASSMETHOD_H_INCLUDED

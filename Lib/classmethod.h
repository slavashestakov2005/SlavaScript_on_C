#ifndef CLASSMETHOD_H_INCLUDED
#define CLASSMETHOD_H_INCLUDED

#include "userdefinedfunction.h"

namespace SlavaScript{ namespace lang{
    class ClassValue;

    class ClassMethod : public UserDefinedFunction{
    private:
        ClassValue* classInstance;
    public:
        ClassMethod(Arguments args, Statement* body, ClassValue* classInstance);
        Value* execute(std::vector<Value*> values);
    };
}}

#endif // CLASSMETHOD_H_INCLUDED

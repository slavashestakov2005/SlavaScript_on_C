#ifndef CLASSMETHOD_IMPL_H_INCLUDED
#define CLASSMETHOD_IMPL_H_INCLUDED

#include "names.h"
#include "variables.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"

namespace SlavaScript::lang{
    template<typename T>
    ClassMethod<T>::ClassMethod(std::shared_ptr<Function> function, T instance) : function(function), instance(instance) {}

    template<typename T>
    std::shared_ptr<Value> ClassMethod<T>::execute(std::vector<std::shared_ptr<Value>> values){
        NamedValue name = Names::getNamed("this");
        Variables::push();
        Variables::set("this", instance);
        std::shared_ptr<Value> result = NullValue::NULL_;
        try{
            result = function -> execute(values);
        } catch(...){
            Variables::pop();
            Names::restore(name);
            throw;
        }
        Variables::pop();
        Names::restore(name);
        return result;
    }

    template<typename T>
    ModuleClassMethod<T>::ModuleClassMethod(T instance) : instance(instance) {}

    template<typename T>
    std::shared_ptr<Value> ModuleClassMethod<T>::execute(std::vector<std::shared_ptr<Value>> values){
        Variables::push();
        std::shared_ptr<Value> result = NullValue::NULL_;
        try{
            result = eval(values);
        } catch(...){
            Variables::pop();
            throw;
        }
        Variables::pop();
        return result;
    }
}

#endif // CLASSMETHOD_IMPL_H_INCLUDED

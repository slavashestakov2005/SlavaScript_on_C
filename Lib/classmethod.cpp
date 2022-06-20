#include "classmethod.h"
#include "variables.h"
#include "../Value/objectvalue.h"

using namespace SlavaScript::lang;

template<typename T>
ClassMethod<T>::ClassMethod(std::shared_ptr<Function> function, T instance) : function(function), instance(instance) {}

template<typename T>
std::shared_ptr<Value> ClassMethod<T>::execute(std::vector<std::shared_ptr<Value>> values){
    Variables::push();
    Variables::set("this", instance);
    std::shared_ptr<Value> result = nullptr;
    try{
        result = function -> execute(values);
    } catch(std::exception* ex){
        Variables::pop();
        throw ex;
    } catch(std::exception& ex){
        Variables::pop();
        throw ex;
    }
    Variables::pop();
    return result;
}

template class ClassMethod<std::shared_ptr<ObjectValue>>;

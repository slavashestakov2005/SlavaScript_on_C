#include "classmethod.h"
#include "variables.h"
#include "../Value/objectvalue.h"

using namespace SlavaScript::lang;

std::shared_ptr<Value> ClassMethod::execute(std::shared_ptr<Function> func, std::vector<std::shared_ptr<Value>> values, std::shared_ptr<Value> classInstance){
    return CAST(ClassMethod, func) -> execute(values, CAST(ObjectValue, classInstance));
}

ClassMethod::ClassMethod(Arguments args, Statement* body) : UserDefinedFunction(args, body) { }

std::shared_ptr<Value> ClassMethod::execute(std::vector<std::shared_ptr<Value>> values, std::shared_ptr<ObjectValue> classInstance){
    Variables::push();
    Variables::set("this", classInstance);
    std::shared_ptr<Value> result = nullptr;
    try{
        result = UserDefinedFunction::execute(values);
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

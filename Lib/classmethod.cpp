#include "classmethod.h"
#include "variables.h"
#include "../Value/classvalue.h"

using namespace SlavaScript::lang;

ClassMethod::ClassMethod(Arguments args, Statement* body, std::shared_ptr<ClassValue> classInstance)
    : UserDefinedFunction(args, body), classInstance(classInstance) { }

std::shared_ptr<Value> ClassMethod::execute(std::vector<std::shared_ptr<Value>> values){
    Variables::push();
    Variables::set("this", classInstance -> getThisMap());
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

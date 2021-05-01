#include <sstream>
#include "variables.h"
#include "userdefinedfunction.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Statement/returnstatement.h"
#include "../Value/arrayvalue.h"
#include "../Value/nullvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ArgumentsMismatchException;

int UserDefinedFunction::getArgsCount(){
    return arguments.size();
}

std::string UserDefinedFunction::getArgsName(int index){
    if (index < 0 || index >= getArgsCount()) return "";
    else return arguments.get(index).getName();
}

std::shared_ptr<Value> UserDefinedFunction::execute(std::vector<std::shared_ptr<Value>> values){
    int siz = values.size();
    int requiredArgsCount = arguments.getRequiredCount();
    int total = getArgsCount();
    int positionArguments = total - arguments.getArrayCount();
    int minimal = std::min(positionArguments, siz);
    if (siz < requiredArgsCount){
        std::string result = "Arguments count mismatch. ";
        std::ostringstream is;
        is << siz << " < " << requiredArgsCount;
        result += is.str();
        throw new ArgumentsMismatchException(result);
    }
    if (siz > total && arguments.getArrayCount() == 0){
        std::string result = "Arguments count mismatch. ";
        std::ostringstream is;
        is << siz << " > " << total;
        result += is.str();
        throw new ArgumentsMismatchException(result);
    }
    try{
        Variables::push();
        for(int i = 0; i < minimal; ++i){
            Variables::set(getArgsName(i), values[i]);
        }
        std::shared_ptr<ArrayValue> array = SHARE(ArrayValue, siz - minimal);
        for(int i = minimal; i < siz; ++i){
            array -> set(i - minimal, values[i]);
        }
        /// add optional
        for(int i = minimal; i < total; ++i){
            Argument arg = arguments.get(i);
            if (arg.isArrayArgument()) Variables::set(arg.getName(), array);
            else Variables::set(arg.getName(), arg.getExpression() -> eval());
        }
        body -> execute();
    }
    catch(ReturnStatement* rs){
        Variables::pop();
        return rs -> getResult();
    }
    Variables::pop();
    return NullValue::NULL_;
}

UserDefinedFunction::operator std::string(){
    std::string result = "def (";
    for(int i = 0; i < arguments.size(); ++i){
        result += std::string(arguments.get(i));
        if (i < arguments.size() - 1) result += ", ";
    }
    result += ") ";
    if(body -> type() == Statements::ReturnStatement) result += "= ";
    result += std::string(*body);
    return result;
}

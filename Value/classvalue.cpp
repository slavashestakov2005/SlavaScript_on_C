#include "classvalue.h"
#include "objectvalue.h"
#include "../Statement/functiondefinestatement.h"
#include "../Statement/classdeclarationsstatement.h"

using namespace SlavaScript::lang;

ClassValue::ClassValue(ClassDeclarationsStatement* statement) : statement(statement) {
    name = statement -> get_name();
}

std::shared_ptr<Value> ClassValue::copy(){
    SH_RET(ClassValue, this -> statement);
}

std::shared_ptr<Value> ClassValue::construct(std::vector<std::shared_ptr<Value>> values){
    std::shared_ptr<ObjectValue> instance = SHARE(ObjectValue, name);
    for(auto now : statement -> fields){
        auto value = now.second -> eval();
        for(std::string fieldName : now.first) instance -> addField(fieldName, value);
    }
    for(auto function : statement -> methods){
        instance -> addMethod(function -> name, SHARE_3(ClassMethod, function -> arguments, function -> body, instance));
    }
    instance -> callConstructor(values);
    return instance;
}

std::string ClassValue::get_name(){
    return name;
}

double ClassValue::asDouble(){
    throw new TypeException("Cannot cast class to double");
}

std::string ClassValue::asString(){
    return "class Value for " + std::string(*statement);
}

bool ClassValue::asBool(){
    throw new TypeException("Cannot cast class to bool");
}

Bignum ClassValue::asBignum(){
    throw new TypeException("Cannot cast class to number");
}

Values ClassValue::type() const{
    return Values::CLASS;
}

std::string ClassValue::string_type() const{
    return "UserClass " + name;
}

ClassValue::operator std::string(){
    return asString();
}

namespace SlavaScript::lang{
    bool operator==(ClassValue const& a, ClassValue const& b){
        return a.name == b.name;
    }

    bool operator<(ClassValue const& a, ClassValue const& b){
        return a.name < b.name;
    }

    COND_OPS(ClassValue)
}

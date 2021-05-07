#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED

#include <string>
#include "values.h"
#include "bignumbers/bignum.h"

namespace SlavaScript{ namespace lang{
    #define CREATE_FUNCTION(name) \
        std::shared_ptr<Function> name = std::make_shared<FunctionModule>([](std::vector<std::shared_ptr<Value>> values) -> std::shared_ptr<Value>{

    #define CREATE_MEMBER_FUNCTION \
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values){

    #define CAST(type, value) \
        (std::static_pointer_cast<type>(value))

    #define SHARE(type, value) \
        std::make_shared<type>(value)

    #define SH_RET(type, value) \
        return std::make_shared<type>(value)

    class Value{
    public:
        virtual double asDouble() = 0;
        virtual std::string asString() = 0;
        virtual bool asBool() = 0;
        virtual Bignum asBignum() = 0;
        virtual Values type() const = 0;
        virtual operator std::string() = 0;
        virtual bool isClassFromModule(){ return false; }
        virtual ~Value(){}
        friend bool operator==(Value const& a, Value const& b);
        friend bool operator!=(Value const& a, Value const& b);
        friend bool operator<(Value const& a, Value const& b);
        friend bool operator<=(Value const& a, Value const& b);
        friend bool operator>(Value const& a, Value const& b);
        friend bool operator>=(Value const& a, Value const& b);
    };
}}

#endif // VALUE_H_INCLUDED

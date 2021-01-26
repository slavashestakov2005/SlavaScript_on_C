#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED

#include <string>
#include "values.h"
#include "bignumbers/bignum.h"

namespace SlavaScript{ namespace lang{
    class Value{
    public:
        virtual double asDouble() = 0;
        virtual std::string asString() = 0;
        virtual bool asBool() = 0;
        virtual Bignum asBignum() = 0;
        virtual Values type() const = 0;
        virtual operator std::string() = 0;
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

#ifndef NULLVALUE_H_INCLUDED
#define NULLVALUE_H_INCLUDED

#include "value.h"

namespace SlavaScript{ namespace lang{
    class NullValue : public Value{
    public:
        static NullValue* NULL_;
        NullValue(){}
        /** @return  throw: TypeException*. */
        double asDouble();
        /** @return  throw: TypeException*. */
        std::string asString();
        /** @return  throw: TypeException*. */
        bool asBool();
        /** @return  throw: TypeException*. */
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~NullValue(){}
        friend bool operator==(NullValue const& a, NullValue const& b);
        friend bool operator!=(NullValue const& a, NullValue const& b);
        friend bool operator<(NullValue const& a, NullValue const& b);
        friend bool operator<=(NullValue const& a, NullValue const& b);
        friend bool operator>(NullValue const& a, NullValue const& b);
        friend bool operator>=(NullValue const& a, NullValue const& b);
    };
}}

#endif // NULLVALUE_H_INCLUDED

#ifndef BOOLVALUE_H_INCLUDED
#define BOOLVALUE_H_INCLUDED

#include "value.h"
#include <iostream>
#include <memory>

namespace SlavaScript{ namespace lang{
    class BoolValue : public Value{
    private:
        bool value;
    public:
        static std::shared_ptr<BoolValue> TRUE_, FALSE_;

        BoolValue(bool value) : value(value) {}

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        virtual Values type() const;
        operator std::string();
        ~BoolValue(){ std::cout << "BOOL VALUE destr\n"; }

        friend bool operator==(BoolValue const& a, BoolValue const& b);
        friend bool operator!=(BoolValue const& a, BoolValue const& b);
        friend bool operator<(BoolValue const& a, BoolValue const& b);
        friend bool operator<=(BoolValue const& a, BoolValue const& b);
        friend bool operator>(BoolValue const& a, BoolValue const& b);
        friend bool operator>=(BoolValue const& a, BoolValue const& b);
    };
}}

#endif // BOOLVALUE_H_INCLUDED

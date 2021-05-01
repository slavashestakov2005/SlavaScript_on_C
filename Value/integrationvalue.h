#ifndef INTEGRATIONVALUE_H_INCLUDED
#define INTEGRATIONVALUE_H_INCLUDED

#include "classvalue.h"

namespace SlavaScript{ namespace lang{
    class IntegrationValue : public Value{
    private:
        std::string fileNameBegin, fileNameEnd;
    public:
        IntegrationValue(std::string fileNameBegin, std::string fileNameEnd) : fileNameBegin(fileNameBegin), fileNameEnd(fileNameEnd) {}

        std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property);

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~IntegrationValue(){}

        friend bool operator==(IntegrationValue const& a, IntegrationValue const& b);
        friend bool operator!=(IntegrationValue const& a, IntegrationValue const& b);
        friend bool operator<(IntegrationValue const& a, IntegrationValue const& b);
        friend bool operator<=(IntegrationValue const& a, IntegrationValue const& b);
        friend bool operator>(IntegrationValue const& a, IntegrationValue const& b);
        friend bool operator>=(IntegrationValue const& a, IntegrationValue const& b);
    };
}}

#endif // INTEGRATIONVALUE_H_INCLUDED

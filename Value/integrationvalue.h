#ifndef INTEGRATIONVALUE_H_INCLUDED
#define INTEGRATIONVALUE_H_INCLUDED

#include "value.h"

namespace SlavaScript::lang{
    class IntegrationValue : public Value{
    private:
        std::string fileNameBegin, fileNameEnd;
    public:
        IntegrationValue(std::string fileNameBegin, std::string fileNameEnd);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;
        std::shared_ptr<Value> getDot(std::shared_ptr<Value> property) override;

        friend CMP(IntegrationValue);
    };

    DEC_CMP(IntegrationValue)
}

#endif // INTEGRATIONVALUE_H_INCLUDED

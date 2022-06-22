#ifndef STRINGVALUE_H_INCLUDED
#define STRINGVALUE_H_INCLUDED

#include "container.h"
#include "value.h"

namespace SlavaScript::lang{
    class StringValue : public Value, public Container<std::string>{
    private:
        container_type value;
    public:
        StringValue(container_type value);

        void set(int index, std::shared_ptr<Value> val);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;
        std::shared_ptr<Value> getDot(std::shared_ptr<Value> property) override;
        std::shared_ptr<Value> getBracket(std::shared_ptr<Value> property) override;
        void setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value) override;

        int size() const override;
        container_type::iterator begin() override;
        container_type::iterator end() override;

        friend CMP(StringValue);
    };

    DEC_CMP(StringValue)
}

#endif // STRINGVALUE_H_INCLUDED

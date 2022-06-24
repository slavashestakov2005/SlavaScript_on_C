#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "../Lib/class.h"
#include "value.h"

namespace SlavaScript::lang{
    class ClassValue : public Value{
    private:
        std::shared_ptr<Class> cls;
    public:
        ClassValue(std::shared_ptr<Class> cls);

        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values);
        std::string getName() const;
        std::shared_ptr<Function> getFunction(std::string func);
        bool isExists(std::string name);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;
        std::string stringType() const override;

        friend CMP(ClassValue);
    };

    DEC_CMP(ClassValue)
}

#endif // CLASSVALUE_H_INCLUDED

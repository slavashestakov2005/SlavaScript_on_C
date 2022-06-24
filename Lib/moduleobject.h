#ifndef MODULEOBJECT_H_INCLUDED
#define MODULEOBJECT_H_INCLUDED

#include "../Value/value.h"

namespace SlavaScript::lang{
    class ModuleObject : public Value{
    public:
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;
    };

    template<typename T>
    class ModuleObjectT : public ModuleObject{
    public:
        static bool is_instance(std::shared_ptr<Value> v);
        static std::string correct_class_name();

        std::string stringType() const override;
    };
}

#include "moduleobject_impl.h"

#endif // MODULEOBJECT_H_INCLUDED

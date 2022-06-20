#ifndef MODULECLASS_H_INCLUDED
#define MODULECLASS_H_INCLUDED

#include "../Lib/class.h"

namespace SlavaScript::lang{
    template<typename T>
    class ModuleClass : public Class{
    public:
        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values) override final{
            if constexpr(std::is_constructible_v<T, std::vector<std::shared_ptr<Value>>>) return SHARE(T, values);
            else throw new TypeException("Cannot use constructor for " + correct_class_name());
        };
        static std::string correct_class_name() { return "ModuleClass " + T::__class_name__; }
        std::string stringType() const override final { return correct_class_name(); }
        operator std::string() override { return "std::string for " + T::__class_name__; }
    };
}

#endif // MODULECLASS_H_INCLUDED

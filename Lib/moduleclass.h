#pragma once

#include <Lib/class.h>


namespace SlavaScript::lang {
    template<typename T>
    class ModuleClass : public Class {
    private:
        static std::string correct_class_name();
    public:
        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values) override final;
        std::string stringType() const override final;
        operator std::string() override;
    };
}


#include <Lib/moduleclass_impl.h>

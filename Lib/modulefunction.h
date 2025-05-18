#pragma once

#include <functional>

#include <Lib/function.h>


namespace SlavaScript::lang {
    using function_type = std::function<std::shared_ptr<Value>(std::vector<std::shared_ptr<Value>>)>;

    class ModuleFunction : public Function {
    private:
        function_type f;
    public:
        ModuleFunction(function_type f);

        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values) override;
        operator std::string() override;
    };
}

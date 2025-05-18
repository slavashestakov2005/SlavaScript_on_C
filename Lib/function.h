#pragma once

#include <vector>

#include <Value/value.h>


namespace SlavaScript::lang {
    class Function {
    public:
        virtual std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>>) = 0;
        virtual operator std::string();

        virtual std::shared_ptr<Value> operator()(std::vector<std::shared_ptr<Value>> args) final;

        virtual ~Function();
    };
}

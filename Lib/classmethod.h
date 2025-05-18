#pragma once

#include <Lib/function.h>


namespace SlavaScript::lang {
    class ObjectValue;

    template<typename T>
    class ClassMethod : public Function {
    private:
        std::shared_ptr<Function> function;
        T instance;
    public:
        ClassMethod(std::shared_ptr<Function> function, T instance);

        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values) override final;
    };

    template<typename T>
    class ModuleClassMethod : public Function, public std::enable_shared_from_this<T> {
    protected:
        T instance;
        virtual std::shared_ptr<Value> eval(std::vector<std::shared_ptr<Value>> values) = 0;
    public:
        ModuleClassMethod(T instance);

        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values) override final;
    };

    using ClassMethodObject = ClassMethod<std::shared_ptr<ObjectValue>>;
}


#include <Lib/classmethod_impl.h>

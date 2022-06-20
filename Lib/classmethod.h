#ifndef CLASSMETHOD_H_INCLUDED
#define CLASSMETHOD_H_INCLUDED

#include "userdefinedfunction.h"
#include "variables.h"

namespace SlavaScript::lang{
    class ObjectValue;

    template<typename T>
    class ClassMethod : public Function{
    private:
        std::shared_ptr<Function> function;
        T instance;
    public:
        ClassMethod(std::shared_ptr<Function> function, T instance);
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values) override;
    };

    template<typename T>
    class ModuleClassMethod : public Function{
    protected:
        T instance;
        virtual std::shared_ptr<Value> eval(std::vector<std::shared_ptr<Value>> values) = 0;
    public:
        ModuleClassMethod(T instance) : instance(instance) {}
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values) override final{
            Variables::push();
            std::shared_ptr<Value> result = nullptr;
            try{
                result = eval(values);
            } catch(std::exception* ex){
                Variables::pop();
                throw ex;
            } catch(std::exception& ex){
                Variables::pop();
                throw ex;
            }
            Variables::pop();
            return result;
        }
    };

    using ClassMethodObject = ClassMethod<std::shared_ptr<ObjectValue>>;
}

#endif // CLASSMETHOD_H_INCLUDED

#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include <memory>
#include <map>
#include "../Value/value.h"
#include "function.h"

namespace SlavaScript::lang{
    class Class{
    protected:
        std::string name;
        std::map<std::string, std::shared_ptr<Function>> methods;
    public:
        std::string getName() const;
        void addMethod(std::string name, std::shared_ptr<Function> method);
        std::shared_ptr<Function> getFunction(std::string name);
        bool isExists(std::string name);

        virtual std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values) = 0;
        virtual std::string stringType() const = 0;
        virtual operator std::string() = 0;
    };
}

#endif // CLASS_H_INCLUDED

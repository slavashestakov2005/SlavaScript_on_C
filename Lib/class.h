#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include <memory>
#include <vector>
#include <map>
#include "../Value/value.h"
#include "classmethod.h"
#include "../Exception/typeexception.h"

namespace SlavaScript::lang{
    class Class{
    protected:
        std::string name;
        std::map<std::string, std::shared_ptr<Function>> methods;
    public:
        virtual std::string getName() const final{ return name; }
        virtual void addMethod(std::string name, std::shared_ptr<Function> method) final{
            methods[name] = method;
        }
        virtual std::shared_ptr<Function> getFunction(std::string name) final{
            if (!isExists(name)) throw new exceptions::TypeException("Cannot get method " + name + " from class");
            return methods[name];
        };
        virtual bool isExists(std::string name) final{
            return methods.find(name) != methods.end();
        }
        virtual std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values) = 0;
        virtual std::string stringType() const = 0;
        virtual operator std::string() = 0;
    };
}

#endif // CLASS_H_INCLUDED

#ifndef USERDEFINEDCLASS_H_INCLUDED
#define USERDEFINEDCLASS_H_INCLUDED

#include "../Lib/class.h"
#include "../Statement/classdeclarationsstatement.h"

namespace SlavaScript::lang{
    class UserDefinedClass : public Class{
    private:
        ClassDeclarationsStatement* statement;
    public:
        UserDefinedClass(ClassDeclarationsStatement* statement);

        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values);

        std::string string_type() const;
        operator std::string();
        ~UserDefinedClass(){}
    };
}

#endif // USERDEFINEDCLASS_H_INCLUDED

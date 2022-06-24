#ifndef USERDEFINEDCLASS_H_INCLUDED
#define USERDEFINEDCLASS_H_INCLUDED

#include "../Lib/class.h"
#include "../Statement/classdeclarationsstatement.h"

namespace SlavaScript::lang{
    class UserDefinedClass final : public Class{
    private:
        ClassDeclarationsStatement* statement;
    public:
        UserDefinedClass(ClassDeclarationsStatement* statement);

        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values) override;
        std::string stringType() const override;
        operator std::string() override;
    };
}

#endif // USERDEFINEDCLASS_H_INCLUDED

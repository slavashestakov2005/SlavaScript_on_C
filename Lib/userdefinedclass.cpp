#include <Lib/userdefinedclass.h>
#include <Lib/userdefinedfunction.h>
#include <Lib/utils.h>
#include <Statement/functiondefinestatement.h>
#include <Value/objectvalue.h>


using namespace SlavaScript::lang;


UserDefinedClass::UserDefinedClass(ClassDeclarationsStatement* statement) : statement(statement) {
    name = statement -> get_name();
    for (auto function : statement -> methods) {
        addMethod(function -> name, SHARE(UserDefinedFunction, function -> arguments, function -> body));
    }
}

std::shared_ptr<Value> UserDefinedClass::construct(std::vector<std::shared_ptr<Value>> values) {
    std::shared_ptr<ObjectValue> instance = SHARE(ObjectValue, name);
    for (auto now : statement -> fields) {
        auto value = now.second -> eval();
        for (std::string fieldName : now.first) instance -> addField(fieldName, value);
    }
    std::shared_ptr<Value> value = instance -> getConstructor();
    if (!value) return instance;
    argType(Values::FUNCTION, value);
    std::shared_ptr<Function> function = CAST(FunctionValue, value) -> getFunction();
    function -> execute(values);
    return instance;
}

std::string UserDefinedClass::stringType() const {
    return "UserClass " + name;
}

UserDefinedClass::operator std::string() {
    return "class Value for " + std::string(*statement);
}

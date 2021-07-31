#include "objectcreationexpression.h"
#include "../Lib/classdeclarations.h"
#include "../Value/classvalue.h"
#include "assignmentexpression.h"
#include "../Statement/functiondefinestatement.h"

using namespace SlavaScript::lang;

std::shared_ptr<Value> ObjectCreationExpression::eval(){
    ClassDeclarationsStatement* ds = ClassDeclarations::get(name);
    std::shared_ptr<ClassValue> instance = SHARE(ClassValue, name);
    for(auto now : ds -> fields){
        auto value = now.second -> eval();
        for(std::string fieldName : now.first) instance -> addField(fieldName, value);
    }
    for(FunctionDefineStatement* function : ds -> methods){
        instance -> addMethod(function -> name, SHARE_3(ClassMethod, function -> arguments, function -> body, instance));
    }
    int size = constructorArguments.size();
    std::vector<std::shared_ptr<Value>> vec;
    for(int i = 0; i < size; ++i) vec.push_back(constructorArguments[i] -> eval());
    instance -> callConstructor(vec);
    return instance;
}

ObjectCreationExpression::operator std::string(){
    std::string result = "new " + name + "(";
    for(int i = 0; i < constructorArguments.size(); ++i){
        result += std::string(*(constructorArguments[i]));
        if (i < constructorArguments.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}

ObjectCreationExpression::~ObjectCreationExpression(){
    for(int i = 0; i < constructorArguments.size(); ++i){
        delete constructorArguments[i];
        constructorArguments[i] = nullptr;
    }
}

void ObjectCreationExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

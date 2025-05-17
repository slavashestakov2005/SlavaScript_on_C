#ifndef MODULECLASS_IMPL_H_INCLUDED
#define MODULECLASS_IMPL_H_INCLUDED

namespace SlavaScript::lang{
    template<typename T>
    std::string ModuleClass<T>::correct_class_name(){
        return "ModuleClass " + T::__class_name__;
    }

    template<typename T>
    std::shared_ptr<Value> ModuleClass<T>::construct(std::vector<std::shared_ptr<Value>> values){
        if constexpr (std::is_constructible_v<T, std::vector<std::shared_ptr<Value>>>) SH_RET(T, values);
        else throw exceptions::TypeException("Cannot use constructor for " + correct_class_name());
    };

    template<typename T>
    std::string ModuleClass<T>::stringType() const{
        return correct_class_name();
    }

    template<typename T>
    ModuleClass<T>::operator std::string(){
        return "std::string for " + T::__class_name__;
    }
}

#endif // MODULECLASS_IMPL_H_INCLUDED

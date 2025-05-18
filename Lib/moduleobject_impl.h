#pragma once


namespace SlavaScript::lang {
    template<typename T>
    bool ModuleObjectT<T>::is_instance(std::shared_ptr<Value> v) {
        return v -> stringType() == correct_class_name();
    }

    template<typename T>
    std::string ModuleObjectT<T>::correct_class_name() {
        return "ModuleObject " + T::__class_name__;
    }

    template<typename T>
    std::string ModuleObjectT<T>::stringType() const {
        return correct_class_name();
    }
}

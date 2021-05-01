#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include "../Lib/function.h"
#include "../Lib/functionmodule.h"

namespace SlavaScript{ namespace modules{
    #define CREATE_TEMPLATE(name) \
        template<typename T, typename = void> struct Has##name: std::false_type{}; \
        template<typename T> struct Has##name<T, std::enable_if_t<std::is_same<decltype(std::declval<T>().init##name()), void>::value>>: std::true_type{}; \
        template<typename T> constexpr bool Has##name##_v = Has##name<T>::value; \
        template<class T, bool b = Has##name##_v<T>> struct Init##name; \
        template<class T> struct Init##name<T, true>{ static void init(){ T::init##name(); } }; \
        template<class T> struct Init##name<T, false>{ static void init(){} };

    #define CREATE_FUNCTION(name) \
        std::shared_ptr<Function> name = std::make_shared<FunctionModule>([](std::vector<std::shared_ptr<Value>> values) -> std::shared_ptr<Value>{

    #define CAST(type, value) \
        (std::static_pointer_cast<type>(value))

    #define SHARE(type, value) \
        std::make_shared<type>(value)

    #define SH_RET(type, value) \
        return std::make_shared<type>(value)

    CREATE_TEMPLATE(Constants)
    CREATE_TEMPLATE(Functions)
    CREATE_TEMPLATE(Classes)

    template<class ModuleName>
    class Module{
    public:
        static void init(){
            InitConstants<ModuleName>::init();
            InitFunctions<ModuleName>::init();
            InitClasses<ModuleName>::init();
        }
    };
}}

#endif // MODULE_H_INCLUDED

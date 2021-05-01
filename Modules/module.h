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

#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

namespace SlavaScript{ namespace modules{
    /** included by module.h **/
    #define CREATE_TEMPLATE(name) \
        template<typename T, typename = void> struct Has##name: std::false_type{}; \
        template<typename T> struct Has##name<T, std::enable_if_t<std::is_same<decltype(std::declval<T>().init##name()), void>::value>>: std::true_type{}; \
        template<typename T> constexpr bool Has##name##_v = Has##name<T>::value; \
        template<class T, bool b = Has##name##_v<T>> struct Init##name; \
        template<class T> struct Init##name<T, true>{ static void init(){ T::init##name(); } }; \
        template<class T> struct Init##name<T, false>{ static void init(){} };
}}

namespace SlavaScript{ namespace lang{
    /** included by value.h **/
    #define CREATE_FUNCTION(name) \
        std::shared_ptr<Function> name = std::make_shared<FunctionModule>([](std::vector<std::shared_ptr<Value>> values) -> std::shared_ptr<Value>{

    #define FE });

    #define CREATE_MEMBER_FUNCTION \
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values){

    #define MFE }

    #define CAST(type, value) \
        (std::static_pointer_cast<type>(value))

    #define SHARE(type, value) \
        std::make_shared<type>(value)

    #define SHARE_2(type, arg1, arg2) \
        std::make_shared<type>(arg1, arg2)

    #define SHARE_3(type, arg1, arg2, arg3) \
        std::make_shared<type>(arg1, arg2, arg3)

    #define SH_RET(type, value) \
        return SHARE(type, value)

    #define SH_RET_2(type, arg1, arg2) \
        return SHARE_2(type, arg1, arg2)

     #define SH_RET_3(type, arg1, arg2, arg3) \
        return SHARE_3(type, arg1, arg2, arg3)

    /** included by classmodulevalue.h and container.h **/
    #define CLASS_MODULE_FUNCTION_(className, fieldType, fieldName) \
        class className : public Function { \
        private: \
            fieldType fieldName; \
        public: \
            className(fieldType fieldName) : fieldName(fieldName) {} \
            CREATE_MEMBER_FUNCTION

    #define CLASS_MODULE_FUNCTION(className, fieldType, fieldName) CLASS_MODULE_FUNCTION_(className, fieldType*, fieldName)

    #define CMFE }};
}}

#endif // MACROS_H_INCLUDED

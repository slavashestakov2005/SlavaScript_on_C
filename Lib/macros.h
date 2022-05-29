#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

namespace SlavaScript::modules{
    /** using by module.h **/
    #define CREATE_TEMPLATE(name) \
        template<typename T, typename = void> struct Has##name: std::false_type{}; \
        template<typename T> struct Has##name<T, std::enable_if_t<std::is_same<decltype(std::declval<T>().init##name()), void>::value>>: std::true_type{}; \
        template<typename T> struct Init##name { static void init(){ if constexpr(Has##name<T>::value) T::init##name(); } };
}

namespace SlavaScript::lang{
    /** using by Value **/
    #define COND_OP(cls, op, exp) bool operator op(cls const& a, cls const& b){ return exp; }
    #define COND_OPS(cls) COND_OP(cls, !=, !(a == b)) COND_OP(cls, >, b < a) COND_OP(cls, <=, !(b < a)) COND_OP(cls, >=, !(a < b))
    #define BINARY_OP(cls, op) cls& operator op(cls a, cls const& b){ return a op##= b; }
    #define BINARY_OPS(cls) BINARY_OP(cls, +) BINARY_OP(cls, -) BINARY_OP(cls, *) BINARY_OP(cls, /) BINARY_OP(cls, %)
    #define CLS_OPS(cls) BINARY_OPS(cls) COND_OPS(cls)

    #define DEC_1(cls, op) cls& operator op(cls const& temp);
    #define DECS_1(cls) DEC_1(cls, +=) DEC_1(cls, -=) DEC_1(cls, *=) DEC_1(cls, /=) DEC_1(cls, %=)
    #define DEC_2(cls, op) cls& operator op(cls a, cls const& b);
    #define DECS_2(cls) DEC_2(cls, +) DEC_2(cls, -) DEC_2(cls, *) DEC_2(cls, /) DEC_2(cls, %)
    #define DEC_COND(cls, op) friend bool operator op(cls const& a, cls const& b);
    #define DECS_COND(cls) DEC_COND(cls, ==) DEC_COND(cls, !=) DEC_COND(cls, <) DEC_COND(cls, >) DEC_COND(cls, <=) DEC_COND(cls, >=)

    /** using by value.h **/
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

    /** using by classmodulevalue.h and container.h **/
    #define CLASS_MODULE_FUNCTION_(className, fieldType, fieldName) \
        class className : public Function { \
        private: \
            fieldType fieldName; \
        public: \
            className(fieldType fieldName) : fieldName(fieldName) {} \
            CREATE_MEMBER_FUNCTION

    #define CLASS_MODULE_FUNCTION(className, fieldType, fieldName) CLASS_MODULE_FUNCTION_(className, fieldType*, fieldName)

    #define CMFE }};

    #define CLASS_IN_MODULE_1(cls) class cls : public ClassModuleValueT<cls> { public: static const std::string __class_name__;
    #define CLASS_IN_MODULE_2(cls) }; inline const std::string cls::__class_name__ = #cls;

    /** using by Modules/... **/
    #define _INFO_F(oldName, newName, info) Functions::set(newName, oldName, info);
    #define INFO_F_(space, text, info) Functions::set(#text, space::text, info);
    #define INFO_F(text, info) Functions::set(#text, text, info);

    #define WITHOUT_F_(space, text) INFO_F_(space, text, ArgumentsInfo::without)
    #define WITHOUT_F(text) INFO_F(text, ArgumentsInfo::without)

    #define UNARY_F_(space, text) INFO_F_(space, text, ArgumentsInfo::unary)
    #define UNARY_F(text) INFO_F(text, ArgumentsInfo::unary)

    #define BINARY_F_(space, text) INFO_F_(space, text, ArgumentsInfo::binary)
    #define BINARY_F(text) INFO_F(text, ArgumentsInfo::binary)

    #define TERNARY_F_(space, text) INFO_F_(space, text, ArgumentsInfo::ternary)
    #define TERNARY_F(text) INFO_F(text, ArgumentsInfo::ternary)

    #define QUATERNARY_F_(space, text) INFO_F_(space, text, ArgumentsInfo::quaternary)
    #define QUATERNARY_F(text) INFO_F(text, ArgumentsInfo::quaternary)

    #define INF_F_(space, text) INFO_F_(space, text, ArgumentsInfo::inf)
    #define INF_F(text) INFO_F(text, ArgumentsInfo::inf)

    #define INF1_F_(space, text) INFO_F_(space, text, ArgumentsInfo::inf1)
    #define INF1_F(text) INFO_F(text, ArgumentsInfo::inf1)
}

#endif // MACROS_H_INCLUDED

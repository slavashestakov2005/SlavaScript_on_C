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
    /** binary operators **/
    #define DEC_OP_IN(cls, op) cls& operator op(cls const& temp)
    #define DEC_OP_OUT(cls, op) cls& operator op(cls a, cls const& b)
    #define DEF_OP_OUT(cls, op) cls& operator op(cls a, cls const& b){ return a op##= b; }

    /** conditional operators **/
    #define CMP(cls) int compare(cls const& a, cls const& b)
    #define DEC_CMP_(cls, op) bool operator op(cls const& a, cls const& b);
    #define DEC_CMP(cls) DEC_CMP_(cls, ==) DEC_CMP_(cls, !=) DEC_CMP_(cls, <) DEC_CMP_(cls, >) DEC_CMP_(cls, <=) DEC_CMP_(cls, >=)
    #define DEF_CMP_(cls, op) bool operator op(cls const& a, cls const& b){ return compare(a, b) op 0; }
    #define DEF_CMP(cls) DEF_CMP_(cls, ==) DEF_CMP_(cls, !=) DEF_CMP_(cls, <) DEF_CMP_(cls, >) DEF_CMP_(cls, <=) DEF_CMP_(cls, >=)

    /** short expressions **/
    #define CHECK(x, y) {int r = compare(x, y); if(r) return r; }
    #define RCHECK(x, y) return compare(x, y)
    #define CAST(type, value) (std::static_pointer_cast<type>(value))

    /** shared_ptr **/
    #define SHARE(type, value) std::make_shared<type>(value)
    #define SHARE_2(type, arg1, arg2) std::make_shared<type>(arg1, arg2)
    #define SHARE_3(type, arg1, arg2, arg3) std::make_shared<type>(arg1, arg2, arg3)
    #define SH_RET(type, value) return SHARE(type, value)
    #define SH_RET_2(type, arg1, arg2) return SHARE_2(type, arg1, arg2)
    #define SH_RET_3(type, arg1, arg2, arg3) return SHARE_3(type, arg1, arg2, arg3)

    /** short declarations **/
    #define CREATE_FUNCTION(name) std::shared_ptr<Function> name = std::make_shared<ModuleFunction>([](std::vector<std::shared_ptr<Value>> values) -> std::shared_ptr<Value>{
    #define FE });

    #define CLASS_METHOD(className, fieldType) \
        class className : public ModuleClassMethod<fieldType>{ \
        public: \
            className(fieldType instance) : ModuleClassMethod<fieldType>(instance) {} \
        private: \
            virtual std::shared_ptr<Value> eval(std::vector<std::shared_ptr<Value>> values){
    #define CLASS_METHOD_PTR(className, fieldType) CLASS_METHOD(className, std::shared_ptr<fieldType>)
    #define CME }};

    #define CLASS_IN_MODULE_1(cls) \
        class cls : public ModuleObjectT<cls>, public std::enable_shared_from_this<cls>{ \
        public: \
            static const std::string __class_name__;
    #define CLASS_IN_MODULE_2(cls) }; inline const std::string cls::__class_name__ = #cls;

    #define ADD_METHOD(str, cls, value) if (prop == str) SH_RET(FunctionValue, new cls(value))
    #define ADD_METHOD_PTR(str, cls) ADD_METHOD(str, cls, shared_from_this())

    /** ArgumentsInfo **/
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

    /** Classes **/
    #define DEF_CLASS(space, cls) class cls##Class : public ModuleClass<space::cls> {};
    #define SET_CLASS(space, cls) Classes::set(#cls, SHARE(ClassValue, std::make_shared<space::cls##Class>()));
}

#endif // MACROS_H_INCLUDED

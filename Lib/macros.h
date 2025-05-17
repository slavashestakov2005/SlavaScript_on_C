#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

namespace SlavaScript::lang{
    /** binary operators **/
    #define DEC_OP_IN(cls, op) cls& operator op(cls const& temp)
    #define DEC_OP_OUT(cls, op) cls& operator op(cls a, cls const& b)
    #define DEF_OP_OUT(cls, op) cls& operator op(cls a, cls const& b){ return a op##= b; }

    /** conditional operators **/
    #define CMP(cls) std::strong_ordering operator<=>(cls const& a, cls const& b)
    #define EQ(cls) bool operator==(cls const& a, cls const& b)
    #define DEF_EQ(cls) bool operator==(cls const& a, cls const& b){ return (a <=> b) == std::strong_ordering::equal; }

    /** short expressions **/
    #define CHECK(x, y) { std::strong_ordering r = (x) <=> (y); if (r != std::strong_ordering::equal) return r; }
    #define RCHECK(x, y) return x <=> y
    #define CAST(type, value) (std::static_pointer_cast<type>(value))

    /** shared_ptr **/
    #define SHARE(type, ...) std::make_shared<type>(__VA_ARGS__)
    #define SH_RET(type, ...) return SHARE(type, __VA_ARGS__)

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
    #define MFUNC_RENAME(oldName, newName, info) Functions::set(newName, oldName, info);
    #define DISPATCH3(a, b, c, d, ...) d
    #define MFUNC_INFO3(space, func, info) MFUNC_RENAME(space::func, #func, info)
    #define MFUNC_INFO2(func, info) MFUNC_RENAME(func, #func, info)
    #define MFUNC_INFO(...) DISPATCH3(__VA_ARGS__, MFUNC_INFO3, MFUNC_INFO2)(__VA_ARGS__)

    #define MFUNC_WITHOUT(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::without)
    #define MFUNC_UNARY(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::unary)
    #define MFUNC_BINARY(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::binary)
    #define MFUNC_TERNARY(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::ternary)
    #define MFUNC_QUATERNARY(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::quaternary)
    #define MFUNC_INF(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::inf)
    #define MFUNC_INF1(...) MFUNC_INFO(__VA_ARGS__, ArgumentsInfo::inf1)

    /** Classes **/
    #define MCLASS_DEF(space, cls) class cls##Class : public ModuleClass<space::cls> {};
    #define MCLASS_SET(space, cls) Classes::set(#cls, SHARE(ClassValue, std::make_shared<space::cls##Class>()));
}

#endif // MACROS_H_INCLUDED

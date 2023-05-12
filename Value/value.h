#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED

#include "bignumbers/bignum.h"
#include "values.h"
#include <memory>
#include <string>

namespace SlavaScript::lang{
    class Value{
    public:
        virtual std::shared_ptr<Value> copy() = 0;
        virtual double asDouble() = 0;
        virtual std::string asString() = 0;
        virtual bool asBool() = 0;
        virtual Bignum asBignum() = 0;
        virtual Values type() const = 0;
        virtual operator std::string() = 0;
        virtual std::shared_ptr<Value> getDot(std::shared_ptr<Value> property);
        virtual std::shared_ptr<Value> getBracket(std::shared_ptr<Value> property);
        virtual void setDot(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
        virtual void setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
        virtual std::string stringType() const;

        virtual ~Value();
        friend CMP(Value);
        friend EQ(Value);
    };


    bool comparator(std::shared_ptr<Value> const& a, std::shared_ptr<Value> const& b);
    bool equals(std::shared_ptr<Value> const& a, std::shared_ptr<Value> const& b);

    class Comparator{
    public:
        bool operator()(std::shared_ptr<Value> const& a, std::shared_ptr<Value> const& b) const;
    };
}

#endif // VALUE_H_INCLUDED

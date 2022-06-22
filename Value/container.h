#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

namespace SlavaScript::lang{
    template<typename T>
    class Container{
    public:
        using container_type = T;
        virtual int size() const = 0;
        virtual typename T::iterator begin() = 0;
        virtual typename T::iterator end() = 0;
    };
}

#endif // CONTAINER_H_INCLUDED

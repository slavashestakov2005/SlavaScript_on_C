#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include "../Lib/function.h"
#include "../Lib/macros.h"
#include "../Lib/modulefunction.h"

namespace SlavaScript::modules{
    template<class ModuleName>
    class Module{
    public:
        static void init(){
            if constexpr(requires{ ModuleName::initConstants(); }) ModuleName::initConstants();
            if constexpr(requires{ ModuleName::initFunctions(); }) ModuleName::initFunctions();
            if constexpr(requires{ ModuleName::initClasses(); }) ModuleName::initClasses();
        }
    };
}

#endif // MODULE_H_INCLUDED

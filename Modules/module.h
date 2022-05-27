#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include "../Lib/function.h"
#include "../Lib/functionmodule.h"
#include "../Lib/macros.h"

namespace SlavaScript::modules{
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
}

#endif // MODULE_H_INCLUDED

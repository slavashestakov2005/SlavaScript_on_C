#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "module.h"

namespace SlavaScript::modules{
    namespace global_f{
        extern std::shared_ptr<SlavaScript::lang::Function> input, max, min, set_color;
    }

    class Global : public Module<Global> {
    public:
        static void initConstants();
        static void initFunctions();
        static void initClasses(){}
    };
}

#endif // GLOBAL_H_INCLUDED

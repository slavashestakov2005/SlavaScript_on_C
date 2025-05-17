#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "module.h"

namespace SlavaScript::modules{
    namespace types_f{
        extern std::shared_ptr<SlavaScript::lang::Function> float_, int_, string, type_to_string, typeof_;
    }

    class Types : public Module<Types> {
    public:
        static void initConstants();
        static void initFunctions();
    };
}

#endif // TYPES_H_INCLUDED

#ifndef FUNCTIONAL_H_INCLUDED
#define FUNCTIONAL_H_INCLUDED

#include "module.h"

namespace SlavaScript::modules{
    namespace functional_f{
        extern std::shared_ptr<SlavaScript::lang::Function> chain, combine, drop_while, filter, flat_map, foreach, map,
                                                            reduce, sortby, take_while;
    }

    class Functional : public Module<Functional> {
    public:
        static void initFunctions();
    };
}

#endif // FUNCTIONAL_H_INCLUDED

#pragma once

#include <Modules/module.h>


namespace SlavaScript::modules {
    namespace functional_f {
        extern std::shared_ptr<SlavaScript::lang::Function> chain, combine, drop_while, filter, flat_map, foreach,
                                            map, reduce, take_while;
    }

    class Functional : public Module<Functional> {
    public:
        static void initFunctions();
    };
}

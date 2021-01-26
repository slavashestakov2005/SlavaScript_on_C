#ifndef FUNCTIONAL_H_INCLUDED
#define FUNCTIONAL_H_INCLUDED

#include "module.h"

namespace SlavaScript{ namespace modules{
    namespace functional_f{
        extern SlavaScript::lang::Function *chain, *combine, *drop_while, *filter, *flat_map, *foreach, *map, *reduce, *sortby,
                                            *take_while;
    }

    class Functional : public Module<Functional> {
    public:
        static void initConstants(){}
        static void initFunctions();
    };
}}

#endif // FUNCTIONAL_H_INCLUDED

#ifndef CHEMISTRY_H_INCLUDED
#define CHEMISTRY_H_INCLUDED

#include "module.h"

namespace SlavaScript{ namespace modules{
    namespace chemistry_f{
        extern SlavaScript::lang::Function *electron, *latin_read, *mr, *neutron, *omega, *russian_read, *write;
    }

    class Chemistry : public Module<Chemistry> {
    public:
        static void initFunctions();
    };
}}

#endif // CHEMISTRY_H_INCLUDED

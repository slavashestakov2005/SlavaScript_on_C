#pragma once

#include <Modules/module.h>


namespace SlavaScript::modules {
    namespace chemistry_f {
        extern std::shared_ptr<SlavaScript::lang::Function> electron, proton, latin_read, mr, neutron, omega, russian_read, write;
    }

    class Chemistry : public Module<Chemistry> {
    public:
        static void initFunctions();
    };
}

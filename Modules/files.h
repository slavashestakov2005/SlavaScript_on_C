#pragma once

#include <Modules/module.h>


namespace SlavaScript::modules {
    namespace files_f {
        extern std::shared_ptr<SlavaScript::lang::Function> open;
    }

    class Files : public Module<Files> {
    public:
        static void initFunctions();
        static void initClasses();
    };
}

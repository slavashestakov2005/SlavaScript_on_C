#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include "module.h"

namespace SlavaScript{ namespace modules{
    namespace files_f{
        extern SlavaScript::lang::Function *fopen, *fclose, *readline, *writeline;
    }

    class Files : public Module<Files> {
    public:
        static void initConstants(){}
        static void initFunctions();
    };
}}

#endif // FILES_H_INCLUDED

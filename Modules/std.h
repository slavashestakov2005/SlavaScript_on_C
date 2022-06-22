#ifndef STD_H_INCLUDED
#define STD_H_INCLUDED

#include "module.h"

namespace SlavaScript::modules{
    namespace std_f{
        extern std::shared_ptr<SlavaScript::lang::Function> array_combine, echo, len, new_array, parse_number, rand,
                                            sleep, time, to_char, to_hex_string;
    }

    class Std : public Module<Std> {
    public:
        static void initConstants();
        static void initFunctions();
    };
}

#endif // STD_H_INCLUDED

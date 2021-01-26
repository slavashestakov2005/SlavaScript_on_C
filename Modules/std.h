#ifndef STD_H_INCLUDED
#define STD_H_INCLUDED

#include "module.h"

namespace SlavaScript{ namespace modules{
    namespace std_f{
        extern SlavaScript::lang::Function *array_combine, *char_at, *echo, *find, *join, *len, *map_key_exists, *map_keys,
                                            *map_values, *new_array, *parse_number, *rand, *replace, *replace_first, *rfind,
                                            *sleep, *sort, *split, *substring, *time, *to_char, *to_hex_string, *to_lower,
                                            *to_upper, *trim;
    }

    class Std : public Module<Std> {
    public:
        static void initConstants();
        static void initFunctions();
    };
}}

#endif // STD_H_INCLUDED

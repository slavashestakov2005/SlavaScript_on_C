#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include "module.h"

namespace SlavaScript{ namespace modules{
    namespace math_f{
        extern std::shared_ptr<SlavaScript::lang::Function> abs, acos, asin, atan, atan2, cbrt, ceil, copy_sign, cos, cosh, exp, expm1,
                                            factorial, floor, hypot, log, log10, log1p, pow, round, signum, sin, sinh,
                                            sqrt, tan, tanh, to_degress, to_radians;
    }

    class Math : public Module<Math> {
    public:
        static void initConstants();
        static void initFunctions();
    };
}};

#endif // MATH_H_INCLUDED

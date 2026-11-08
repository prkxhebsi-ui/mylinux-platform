#include <mylinux/math/advanced.h>
#include <math.h>

double mylinux_alog(double base, double exponent)
{
    if (base <= 0.0)
        return NAN;

    return pow(base, exponent);
}

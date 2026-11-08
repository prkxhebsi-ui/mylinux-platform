#include <mylinux/math/advanced.h>
#include <math.h>

double mylinux_log(double base, double value)
{
    if (base <= 0.0 || base == 1.0 || value <= 0.0)
        return NAN;

    return log(value) / log(base);
}

double mylinux_log10(double value)
{
    return log10(value);
}

double mylinux_ln(double value)
{
    return log(value);
}

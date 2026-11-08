#include <mylinux/math.h>

#include <math.h>

double
mylinux_math_sqrt(double value)
{
    return sqrt(value);
}

double
mylinux_math_pow(double base, double exponent)
{
    return pow(base, exponent);
}

double
mylinux_math_log(double value)
{
    return log(value);
}

double
mylinux_math_exp(double value)
{
    return exp(value);
}

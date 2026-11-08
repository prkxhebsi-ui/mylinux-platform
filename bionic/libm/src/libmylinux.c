#include "libmylinux.h"

#include <errno.h>
#include <math.h>

double mylinux_add(double a, double b)
{
    return a + b;
}

double mylinux_sub(double a, double b)
{
    return a - b;
}

double mylinux_mul(double a, double b)
{
    return a * b;
}

double mylinux_div(double a, double b)
{
    if (b == 0.0) {
        errno = EDOM;
        return NAN;
    }

    return a / b;
}

int mylinux_equal(double a, double b)
{
    return a == b;
}

int mylinux_greater(double a, double b)
{
    return a > b;
}

int mylinux_less(double a, double b)
{
    return a < b;
}

int mylinux_greater_equal(double a, double b)
{
    return a >= b;
}

int mylinux_less_equal(double a, double b)
{
    return a <= b;
}

double mylinux_abs(double value)
{
    return fabs(value);
}

double mylinux_min(double a, double b)
{
    return fmin(a, b);
}

double mylinux_max(double a, double b)
{
    return fmax(a, b);
}

double mylinux_clamp(double value, double low, double high)
{
    if (low > high) {
        errno = EINVAL;
        return NAN;
    }

    if (value < low)
        return low;

    if (value > high)
        return high;

    return value;
}

double mylinux_sqrt(double value)
{
    return sqrt(value);
}

double mylinux_pow(double base, double exponent)
{
    return pow(base, exponent);
}

double mylinux_exp(double value)
{
    return exp(value);
}

double mylinux_log(double value)
{
    return log(value);
}

double mylinux_angular_frequency(double frequency_hz)
{
    return MYLINUX_TAU * frequency_hz;
}

double mylinux_photon_energy(double frequency_hz)
{
    return MYLINUX_PLANCK_H * frequency_hz;
}

int mylinux_is_finite(double value)
{
    return isfinite(value);
}

int mylinux_is_infinite(double value)
{
    return isinf(value);
}

int mylinux_is_nan(double value)
{
    return isnan(value);
}

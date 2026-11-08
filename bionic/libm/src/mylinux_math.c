#include "mylinux_math.h"

#include <math.h>

#define MYMATH_PI 3.14159265358979323846

double mymath_abs(double value)
{
    return fabs(value);
}

double mymath_min(double a, double b)
{
    if (isnan(a))
        return a;
    if (isnan(b))
        return b;
    return a < b ? a : b;
}

double mymath_max(double a, double b)
{
    if (isnan(a))
        return a;
    if (isnan(b))
        return b;
    return a > b ? a : b;
}

double mymath_clamp(double value, double low, double high)
{
    if (isnan(value) || isnan(low) || isnan(high))
        return NAN;
    if (low > high)
        return NAN;
    if (value < low)
        return low;
    if (value > high)
        return high;
    return value;
}

double mymath_lerp(double a, double b, double amount)
{
    return a + (b - a) * amount;
}

double mymath_degrees_to_radians(double degrees)
{
    return degrees * (MYMATH_PI / 180.0);
}

double mymath_radians_to_degrees(double radians)
{
    return radians * (180.0 / MYMATH_PI);
}

int mymath_is_finite(double value)
{
    return isfinite(value) != 0;
}

int mymath_is_nan(double value)
{
    return isnan(value) != 0;
}

double mymath_sign(double value)
{
    if (isnan(value))
        return NAN;
    if (value > 0.0)
        return 1.0;
    if (value < 0.0)
        return -1.0;
    return value;
}

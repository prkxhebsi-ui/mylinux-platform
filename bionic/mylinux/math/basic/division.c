#include <mylinux/math/arithmetic.h>
#include <errno.h>
#include <math.h>

double mylinux_divide(double a, double b)
{
    if (b == 0.0) {
        errno = EDOM;
        return NAN;
    }

    return a / b;
}

#include <mylinux/math/advanced.h>
#include <math.h>

double mylinux_omega(double x)
{
    double value = 0.5;

    for (unsigned int i = 0; i < 100; ++i) {
        double e = exp(value);
        double denominator = e * (value + 1.0);

        if (denominator == 0.0)
            return NAN;

        double next = value -
            (value * e - x) / denominator;

        if (fabs(next - value) < 1e-14)
            return next;

        value = next;
    }

    return value;
}

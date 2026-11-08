#include "libmylinux.h"

int mylinux_libm_selftest(void)
{
    if (mylinux_add(2.0, 3.0) != 5.0)
        return 1;

    if (mylinux_sub(9.0, 4.0) != 5.0)
        return 2;

    if (mylinux_mul(3.0, 4.0) != 12.0)
        return 3;

    if (mylinux_div(8.0, 2.0) != 4.0)
        return 4;

    if (!mylinux_greater(4.0, 2.0))
        return 5;

    if (!mylinux_less(2.0, 4.0))
        return 6;

    if (mylinux_clamp(12.0, 0.0, 10.0) != 10.0)
        return 7;

    if (mylinux_photon_energy(0.0) != 0.0)
        return 8;

    if (!mylinux_is_infinite(MYLINUX_INFINITY))
        return 9;

    if (!mylinux_is_finite(42.0))
        return 10;

    return 0;
}

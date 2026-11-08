#ifndef LIBMYLINUX_H
#define LIBMYLINUX_H

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Physical and mathematical constants. */
#define MYLINUX_PLANCK_H       6.62607015e-34
#define MYLINUX_PI             3.14159265358979323846
#define MYLINUX_TAU            (2.0 * MYLINUX_PI)
#define MYLINUX_INFINITY       INFINITY

/* Basic arithmetic. */
double mylinux_add(double a, double b);
double mylinux_sub(double a, double b);
double mylinux_mul(double a, double b);
double mylinux_div(double a, double b);

/* Comparisons: return 1 for true and 0 for false. */
int mylinux_equal(double a, double b);
int mylinux_greater(double a, double b);
int mylinux_less(double a, double b);
int mylinux_greater_equal(double a, double b);
int mylinux_less_equal(double a, double b);

/* Useful numeric operations. */
double mylinux_abs(double value);
double mylinux_min(double a, double b);
double mylinux_max(double a, double b);
double mylinux_clamp(double value, double low, double high);
double mylinux_sqrt(double value);
double mylinux_pow(double base, double exponent);
double mylinux_exp(double value);
double mylinux_log(double value);

/* Physics helpers. */
double mylinux_angular_frequency(double frequency_hz);
double mylinux_photon_energy(double frequency_hz);

/* The remembered "underscore" idea: finite-value checking. */
int mylinux_is_finite(double value);
int mylinux_is_infinite(double value);
int mylinux_is_nan(double value);

#ifdef __cplusplus
}
#endif

#endif

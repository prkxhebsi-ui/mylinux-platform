#ifndef MYLINUX_MATH_H
#define MYLINUX_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

double mymath_abs(double value);
double mymath_min(double a, double b);
double mymath_max(double a, double b);
double mymath_clamp(double value, double low, double high);
double mymath_lerp(double a, double b, double amount);
double mymath_degrees_to_radians(double degrees);
double mymath_radians_to_degrees(double radians);
int mymath_is_finite(double value);
int mymath_is_nan(double value);
double mymath_sign(double value);

#ifdef __cplusplus
}
#endif

#endif

/**
 * \file
 * \brief Complex numbers interface and implementation
 */
#ifndef MANDELBROTSET_COMPLEX_H
#define MANDELBROTSET_COMPLEX_H

#include <math.h>

/**
 * \brief Complex number: (x + yi)
 */
struct CMPLX_Complex
{
    double real; /**< The real part (x) of the complex number */
    double imag; /**< The imaginary part (y) of the complex number */
};

/**
 * \brief Add two complex numbers
 *
 * \param[in] x First complex number
 * \param[in] y Second complex number
 *
 * \return x + y
 */
static inline struct CMPLX_Complex CMPLX_add(
    const struct CMPLX_Complex x,
    const struct CMPLX_Complex y)
{
    const struct CMPLX_Complex output = {
        .real = x.real + y.real,
        .imag = x.imag + y.imag
    };

    return output;
}

/**
 * \brief Square a complex number
 *
 * \param[in] x Complex number to square
 *
 * \return x^2
 */
static inline struct CMPLX_Complex CMPLX_square(
    const struct CMPLX_Complex x)
{
    const struct CMPLX_Complex output = {
        .real = (x.real * x.real) - (x.imag * x.imag),
        .imag = 2.0 * (x.real * x.imag)
    };

    return output;
}

/**
 * \brief Absolute value of a complex number
 *
 * \param[in] x Complex number to compute the absolute value for
 *
 * \return |x|
 */
static inline double CMPLX_abs(
    const struct CMPLX_Complex x)
{
    const double output = sqrt((x.real * x.real) + (x.imag * x.imag));

    return output;
}

#endif /* MANDELBROTSET_COMPLEX_H */

/**
 * \file
 * \brief Mandelbrot interface
 */
#ifndef MANDELBROTSET_MANDELBROT_H
#define MANDELBROTSET_MANDELBROT_H

#include <MandelbrotSet/complex.h>

#include <stdint.h>

/**
 * \brief The Mandelbrot function
 *
 * Defined as
 *     f(z) = z^2 + c,
 * with z initialized as
 *     z = 0.
 *
 * This function is iterated as
 *     f(f(f(0)))
 * until divergence is confirmed.
 *
 * \param[in] c The c value of the Mandelbrot function
 * \param[in] max_iterations The maximum iterations to determine whether the function diverges or not
 *
 * \return Number of iterations needed until divergence is confirmed, max_iterations if no divergence
 */
uint8_t MBROT_mandelbrot(
    const struct CMPLX_Complex c,
    const uint8_t max_iterations)
{
    struct CMPLX_Complex f = c;

    for (uint8_t i = 0U; i < max_iterations; ++i)
    {
        if (CMPLX_abs(f) > 2.0)
        {
            return i;
        }

        f = CMPLX_add(CMPLX_square(f), c);
    }

    return max_iterations;
}

#endif /* MANDELBROTSET_MANDELBROT_H */

/**
 * \file
 * \brief Mandelbrot set implementation
 */
#include <MandelbrotSet/complex.h>
#include <MandelbrotSet/image.h>
#include <MandelbrotSet/mandelbrot_set.h>

#include <assert.h>
#include <stdint.h>

/**
 * \brief The Mandelbrot set function
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
static uint16_t mandelbrot(
    const struct CMPLX_Complex c,
    const uint16_t max_iterations)
{
    struct CMPLX_Complex f = c;

    for (uint16_t i = 0U; i < max_iterations; ++i)
    {
        if (CMPLX_abs(f) > 2.0)
        {
            return i;
        }

        f = CMPLX_add(CMPLX_square(f), c);
    }

    return max_iterations;
}

void MBROT_generate_mandelbrot_set(
    struct IMG_Image *const image,
    const struct MBROT_Range *const range,
    const uint16_t max_iterations)
{
    assert(image->width > 0);
    assert(image->height > 0);
    assert(range->max.real > range->min.real);
    assert(range->max.imag > range->min.imag);

    const double x_step = (range->max.real - range->min.real) / image->width;
    const double y_step = (range->max.imag - range->min.imag) / image->height;

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            const struct CMPLX_Complex c = {
                .real = range->min.real + (x * x_step),
                .imag = range->min.imag + (y * y_step)
            };

            const uint16_t pixel = mandelbrot(c, max_iterations);

            IMG_set_pixel(image, x, y, pixel);
        }
    }
}

/**
 * \file
 * \brief Mandelbrot interface
 */
#ifndef MANDELBROTSET_MANDELBROT_H
#define MANDELBROTSET_MANDELBROT_H

#include <MandelbrotSet/complex.h>
#include <MandelbrotSet/image.h>

#include <stdint.h>

__device__
double m_min(
    const double a,
    const double b)
{
    return a < b ? a : b;
}

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
__device__
uint8_t MBROT_mandelbrot(
    const struct CMPLX_Complex c,
    const uint8_t max_iterations)
{
    struct CMPLX_Complex f = c;

    for (uint8_t i = 0U; i < max_iterations; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
        if (CMPLX_abs(f) > 2.0)
        {
            return i;
        }

        f = CMPLX_add(CMPLX_square(f), c);
    }

    return max_iterations;
}

/**
 * \brief Colorize a pixel in a Mandelbrot set image
 *
 * Uses a variant of the variant of the Bernstein polynomials.
 *
 * \param[in] image The Mandelbrot set image
 * \param[in] x The x-coordinate of the pixel
 * \param[in] y The y-coordinate of the pixel
 * \param[in] max_iterations The maximum number of iterations used to generate the Mandelbrot set
 * \param[in] color_image The color image to write to, the width must be 3x (red, green, blue) of the input image
 */
__device__
void MBROT_colorize_pixel(
    const struct IMG_Image *const image,
    const int x,
    const int y,
    const int max_iterations,
    struct IMG_Image *const color_image)
{
    const double norm_factor = 1.0 / max_iterations;
    const uint8_t pixel = IMG_get_pixel(image, x, y);

    const double normalized_pixel = pixel * norm_factor;
    const double inverse = 1.0 - normalized_pixel;
    const double red = 9.0 * inverse * normalized_pixel * normalized_pixel * normalized_pixel;
    const double green = 15.0 * inverse * inverse * normalized_pixel * normalized_pixel;
    const double blue = 8.5 * inverse * inverse * inverse * normalized_pixel;

    IMG_set_pixel(color_image, x * 3 + 0, y, (uint8_t)m_min(red * max_iterations, max_iterations));
    IMG_set_pixel(color_image, x * 3 + 1, y, (uint8_t)m_min(green * max_iterations, max_iterations));
    IMG_set_pixel(color_image, x * 3 + 2, y, (uint8_t)m_min(blue * max_iterations, max_iterations));
}

#endif /* MANDELBROTSET_MANDELBROT_H */

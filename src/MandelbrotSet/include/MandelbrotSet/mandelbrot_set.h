/**
 * \file
 * \brief Mandelbrot set interface
 */
#ifndef MANDELBROTSET_MANDELBROTSET_H
#define MANDELBROTSET_MANDELBROTSET_H

#include <MandelbrotSet/complex.h>

#include <stdint.h>

struct IMG_Image;

/**
 * \brief The complex number range (min and max values) of a Mandelbrot set
 */
struct MBROT_Range
{
    struct CMPLX_Complex min; /**< The min value of the Mandelbrot set */
    struct CMPLX_Complex max; /**< The max value of the Mandelbrot set */
};

/**
 * \brief Allocate a Mandelbrot set image
 *
 * \param[in] width The width of the image [pixels]
 * \param[in] height The height of the image [pixels]
 *
 * \return The allocated image
 */
struct IMG_Image * MBROT_alloc_mandebrot_set_image(
    int width,
    int height);

/**
 * \brief Free a Mandelbrot set image
 *
 * \param[in,out] image The image to free
 */
void MBROT_free_mandebrot_set_image(
    struct IMG_Image *image);

/**
 * \brief Generate a Mandelbrot set
 *
 * All pixels in the image that is equal to max_iterations is part of the Mandelbrot set. All other
 * pixels are not part of the set. Any other value than max_iterations represents the number of
 * iterations needed to confirm divergence for that particular pixel.
 *
 * A pixel represents a complex number and the actual value is determine by the range and the image
 * size.
 *
 * \param[in,out] image The image to generate the Mandelbrot set to, the user allocates the pixels
 * \param[in] range The range (or "zoom level") of the Mandelbrot set
 * \param[in] max_iterations The maximum number of iterations to determine whether a particular
 *                           value diverges or not
 */
void MBROT_generate_mandelbrot_set(
    struct IMG_Image *image,
    const struct MBROT_Range *range,
    uint8_t max_iterations);

#endif /* MANDELBROTSET_MANDELBROTSET_H */

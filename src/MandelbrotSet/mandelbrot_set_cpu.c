/**
 * \file
 * \brief Mandelbrot set CPU implementation
 */
#include <MandelbrotSet/complex.h>
#include <MandelbrotSet/image.h>
#include <MandelbrotSet/mandelbrot.h>
#include <MandelbrotSet/mandelbrot_set.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

struct IMG_Image * MBROT_alloc_mandebrot_set_image(
    const int width,
    const int height)
{
    const int number_of_pixels = width * height;

    struct IMG_Image *const image = calloc(1, sizeof(*image));
    assert(image != NULL);

    image->width = width;
    image->height = height;
    image->pixels = calloc((size_t)number_of_pixels, sizeof(*image->pixels));
    assert(image->pixels != NULL);

    return image;
}

void MBROT_free_mandebrot_set_image(
    struct IMG_Image *const image)
{
    free(image->pixels);
    free(image);
}

void MBROT_generate_mandelbrot_set(
    struct IMG_Image *const image,
    const struct MBROT_Range *const range,
    const uint8_t max_iterations)
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

            const uint8_t pixel = MBROT_mandelbrot(c, max_iterations);

            IMG_set_pixel(image, x, y, pixel);
        }
    }
}

void MBROT_colorize_mandelbrot_set(
    const struct IMG_Image *const image,
    const int max_iterations,
    struct IMG_Image *const color_image)
{
    assert(image->width > 0);
    assert(image->height > 0);
    assert(color_image->width == image->width * 3);
    assert(color_image->height == image->height);
    assert(max_iterations > 0);

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            MBROT_colorize_pixel(image, x, y, max_iterations, color_image);
        }
    }
}

#include <MandelbrotSet/mandelbrot_set.h>

#include <stdint.h>

#define RESOLUTION_X (128)
#define RESOLUTION_Y (128)
#define DIVERGE_THRESHOLD (UINT8_MAX)

int main(int argv, char *argc[])
{
    (void)argv;
    (void)argc;

    struct IMG_Image *const image = MBROT_alloc_mandebrot_set_image(RESOLUTION_X, RESOLUTION_Y);
    struct IMG_Image *const color_image = MBROT_alloc_mandebrot_set_image(RESOLUTION_X * 3, RESOLUTION_Y);

    const struct MBROT_Range range = {
        .min = {
            .real = -2.0,
            .imag = -2.0
        },
        .max = {
            .real = 2.0,
            .imag = 2.0
        }
    };

    MBROT_generate_mandelbrot_set(image, &range, DIVERGE_THRESHOLD);
    MBROT_colorize_mandelbrot_set(image, DIVERGE_THRESHOLD, color_image);

    MBROT_free_mandebrot_set_image(image);
    MBROT_free_mandebrot_set_image(color_image);

    return 0;
}

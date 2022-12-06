#include <MandelbrotSet/image.h>
#include <MandelbrotSet/mandelbrot_set.h>

#include <stdint.h>
#include <stdlib.h>

#define RESOLUTION_X (128)
#define RESOLUTION_Y (128)
#define DIVERGE_THRESHOLD (255u)

int main(int argv, char *argc[])
{
    (void)argv;
    (void)argc;

    struct IMG_Image image = {
        .width = RESOLUTION_X,
        .height = RESOLUTION_Y,
        .pixels = calloc(RESOLUTION_X * RESOLUTION_Y, sizeof(*image.pixels))
    };
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

    MBROT_generate_mandelbrot_set(&image, &range, DIVERGE_THRESHOLD);

    free(image.pixels);

    return 0;
}

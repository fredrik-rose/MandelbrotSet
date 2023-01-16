#include <MandelbrotSet/mandelbrot_set.h>
#include <MandelbrotSet/pgm.h>

#include <stdint.h>

#define RESOLUTION_X (7680)
#define RESOLUTION_Y (7680)
#define DIVERGE_THRESHOLD (UINT8_MAX)
#define MANDELBROT_IMAGE_PATH ("mandelbrot.pgm")

int main(int argv, char *argc[])
{
    (void)argv;
    (void)argc;

    struct IMG_Image *const image = MBROT_alloc_mandebrot_set_image(RESOLUTION_X, RESOLUTION_Y);

    const struct MBROT_Range range = {
        .min = {
            .real = -2.0,
            .imag = -1.5
        },
        .max = {
            .real = 1.0,
            .imag = 1.5
        }
    };

    MBROT_generate_mandelbrot_set(image, &range, DIVERGE_THRESHOLD);
    PGM_save(image, DIVERGE_THRESHOLD, MANDELBROT_IMAGE_PATH);

    MBROT_free_mandebrot_set_image(image);
}

#include <MandelbrotSet/complex.h>
#include <MandelbrotSet/image.h>
#include <MandelbrotSet/pgm.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    (void)argv;
    (void)argc;

    const struct CMPLX_Complex a = {
        .real = 1.0,
        .imag = 2.0
    };

    const struct CMPLX_Complex b = {
        .real = 3.0,
        .imag = 4.0
    };

    struct CMPLX_Complex c = CMPLX_add(a, b);
    c = CMPLX_square(c);
    const double d = CMPLX_abs(c);

    printf("(%.2lf + %.2lfi), %.2lf\n", c.real, c.imag, d);

    struct IMG_Image image = {
        .width = 10,
        .height = 10,
        .pixels = calloc(10 * 10, sizeof(*image.pixels))
    };

    IMG_set_pixel(&image, 1, 2, 3U);
    const uint16_t pixel = IMG_get_pixel(&image, 1, 2);

    printf("pixel: %u\n", pixel);

    PGM_save(&image, 255U, "mandelbrot.pgm");

    free(image.pixels);
}

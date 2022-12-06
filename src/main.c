#include <MandelbrotSet/complex.h>

#include <stdio.h>

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
}

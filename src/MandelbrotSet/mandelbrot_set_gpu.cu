/**
 * \file
 * \brief Mandelbrot set GPU implementation
 */
extern "C"
{
#include <MandelbrotSet/complex.h>
#include <MandelbrotSet/image.h>
#include <MandelbrotSet/mandelbrot.h>
#include <MandelbrotSet/mandelbrot_set.h>
}

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define THREADS_PER_BLOCK_X (16)
#define THREADS_PER_BLOCK_Y (16)
#define NUMBER_OF_BLOCKS (4096)

__global__
static void generate_mandelbrot_set_kernel(
    struct IMG_Image *const image,
    const struct MBROT_Range range,
    const uint8_t max_iterations)
{
    const double x_step = (range.max.real - range.min.real) / image->width;
    const double y_step = (range.max.imag - range.min.imag) / image->height;
    const int x_start = (blockIdx.x * blockDim.x) + threadIdx.x;
    const int y_start = (blockIdx.y * blockDim.y + threadIdx.y);
    const int x_stride = blockDim.x * gridDim.x;
    const int y_stride = blockDim.y * gridDim.y;

    for (int y = y_start; y < image->height; y += y_stride)
    {
        for (int x = x_start; x < image->width; x += x_stride)
        {
            const struct CMPLX_Complex c = {
                .real = range.min.real + (x * x_step),
                .imag = range.min.imag + (y * y_step)
            };

            const uint8_t pixel = MBROT_mandelbrot(c, max_iterations);

            IMG_set_pixel(image, x, y, pixel);
        }
    }
}

struct IMG_Image * MBROT_alloc_mandebrot_set_image(
    int width,
    int height)
{
    struct IMG_Image *image;
    const int image_malloc_result = cudaMallocManaged(&image, sizeof(*image));
    assert(image_malloc_result == 0);
    assert(image != NULL);

    image->width = width;
    image->height = height;
    const int pixel_malloc_result = cudaMallocManaged(&image->pixels, width * height * sizeof(*image->pixels));
    assert(pixel_malloc_result == 0);
    assert(image->pixels != NULL);

    return image;
}

void MBROT_free_mandebrot_set_image(
    struct IMG_Image *const image)
{
    cudaFree(image->pixels);
    cudaFree(image);
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

    const dim3 threadsPerBlock(THREADS_PER_BLOCK_X, THREADS_PER_BLOCK_Y);
    generate_mandelbrot_set_kernel<<<NUMBER_OF_BLOCKS, threadsPerBlock>>>(image, *range, max_iterations);
    cudaDeviceSynchronize();
}

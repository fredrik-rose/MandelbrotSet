/**
 * \file
 * \brief PGM image implementation
 */
#include <MandelbrotSet/image.h>
#include <MandelbrotSet/pgm.h>

#include <stdint.h>
#include <stdio.h>

void PGM_save(
    const struct IMG_Image *const image,
    const uint8_t max_value,
    const char *const file_path)
{
    FILE *const output = fopen(file_path, "wbe");

    fprintf(output, "P2\n");
    fprintf(output, "%d %d\n", image->width, image->height);
    fprintf(output, "%d\n", max_value);

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            const uint8_t pixel = IMG_get_pixel(image, x, y);

            fprintf(output, "%d ", pixel);
        }
        fprintf(output, "\n");
    }
    fclose(output);
}

void PPM_save(
    const struct IMG_Image *const color_image,
    const uint8_t max_value,
    const char *const file_path)
{
    FILE *const output = fopen(file_path, "wbe");

    fprintf(output, "P3\n");
    fprintf(output, "%d %d\n", color_image->width / 3, color_image->height);
    fprintf(output, "%d\n", max_value);

    for (int y = 0; y < color_image->height; ++y)
    {
        for (int x = 0; x < color_image->width; ++x)
        {
            const uint8_t pixel = IMG_get_pixel(color_image, x, y);

            fprintf(output, "%d ", pixel);
        }
        fprintf(output, "\n");
    }

    fclose(output);
}

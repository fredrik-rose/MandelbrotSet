/**
 * \file
 * \brief PGM image interface
 */
#ifndef MANDELBROTSET_PGM_H
#define MANDELBROTSET_PGM_H

struct IMG_Image;

#include <stdint.h>

/**
 * \brief Save an image to a PGM file
 *
 * \param[in] image The image to save
 * \param[in] max_value The max value of the image (the theoretical max, not necessarily the actual max)
 * \param[in] file_path The file path to save the image to
 */
void PGM_save(
    const struct IMG_Image *image,
    uint16_t max_value,
    const char *file_path);

#endif /* MANDELBROTSET_PGM_H */

/**
 * \file
 * \brief Image interface and implementation
 */
#ifndef MANDELBROTSET_IMAGE_H
#define MANDELBROTSET_IMAGE_H

#include <assert.h>
#include <stdint.h>

/**
 * \brief Image
 */
struct IMG_Image
{
    int width; /**< The width of the image [pixels] */
    int height; /**< The height of the image [pixels] */
    uint8_t *pixels; /**< The pixels of the image, must be of length width * height */
};

/**
 * \brief Update the value of a pixel in an image
 *
 * \param[in,out] image The image
 * \param[in] x The x position (column) to update
 * \param[in] y The y position (row) to update
 * \param[in] value The new value
 */
__device__
static inline void IMG_set_pixel(
    struct IMG_Image *const image,
    const int x,
    const int y,
    const uint8_t value)
{
    assert(x < image->width);
    assert(y < image->height);

    image->pixels[(image->width * y) + x] = value;
}

/**
 * \brief Get a certain pixel from an image
 *
 * \param[in] image The image
 * \param[in] x The x position (column) to extract the pixel from
 * \param[in] y The y position (row) to extract the pixel from
 *
 * \return The pixel
 */
static inline uint8_t IMG_get_pixel(
    const struct IMG_Image *const image,
    const int x,
    const int y)
{
    assert(x < image->width);
    assert(y < image->height);

    return image->pixels[(image->width * y) + x];
}

#endif /* MANDELBROTSET_IMAGE_H */

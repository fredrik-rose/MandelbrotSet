#include <MandelbrotSet/complex.h>
#include <MandelbrotSet/image.h>
#include <MandelbrotSet/mandelbrot_set.h>
#include <MandelbrotSet/pgm.h>

#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define SAVE_PGM_IMAGE (true)
#define RESOLUTION_X (1080)
#define RESOLUTION_Y (1080)
#define MIN_REAL (-2.0)
#define MAX_REAL (1.0)
#define MIN_IMAG (-1.5)
#define MAX_IMAG (1.5)
#define ZOOM_FACTOR (0.8)
#define DIVERGE_THRESHOLD (UINT8_MAX)
#define MANDELBROT_IMAGE_PATH ("mandelbrot.pgm")
#define MANDELBROT_COLOR_IMAGE_PATH ("mandelbrot_color.ppm")

static void update_range_pan(
    struct MBROT_Range *const range,
    const int dx,
    const int dy)
{
    const double width = range->max.real - range->min.real;
    const double height = range->max.imag - range->min.imag;

    const double move_real = (dx / (double)RESOLUTION_X) * width;
    const double move_imag = (dy / (double)RESOLUTION_Y) * height;

    range->min.real -= move_real;
    range->max.real -= move_real;

    range->min.imag -= move_imag;
    range->max.imag -= move_imag;
}

static void update_range_zoom(
    struct MBROT_Range *const range,
    const int mouse_x,
    const int mouse_y,
    const double zoom_factor)
{
    const double min_real = range->min.real;
    const double max_real = range->max.real;

    const double min_imag = range->min.imag;
    const double max_imag = range->max.imag;

    const double width  = max_real - min_real;
    const double height = max_imag - min_imag;

    const double mouse_real = min_real + (mouse_x / (double)RESOLUTION_X) * width;
    const double mouse_imag = min_imag + (mouse_y / (double)RESOLUTION_Y) * height;

    const double new_width = width * zoom_factor;
    const double new_height = height * zoom_factor;

    range->min.real = mouse_real - (mouse_real - min_real) * zoom_factor;
    range->max.real = range->min.real + new_width;

    range->min.imag = mouse_imag - (mouse_imag - min_imag) * zoom_factor;
    range->max.imag = range->min.imag + new_height;
}

static void update_texture_from_image(
    SDL_Texture *const texture,
    const struct IMG_Image *const color_image)
{
    const size_t size = (size_t)(color_image->width * color_image->height) * sizeof(*color_image->pixels);
    uint8_t *pixels = NULL;
    int pitch = 0;

    SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);
    memcpy(pixels, color_image->pixels, size);
    SDL_UnlockTexture(texture);
}

int main(int argv, char *argc[])
{
    (void)argv;
    (void)argc;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *const window = SDL_CreateWindow(
        "Mandelbrot Set Explorer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        RESOLUTION_X, RESOLUTION_Y,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *const texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        RESOLUTION_X, RESOLUTION_Y
    );

    struct IMG_Image *const image = MBROT_alloc_mandebrot_set_image(RESOLUTION_X, RESOLUTION_Y);
    struct IMG_Image *const color_image = MBROT_alloc_mandebrot_set_image(RESOLUTION_X * 3, RESOLUTION_Y);

    struct MBROT_Range range = {
        .min = {
            .real = MIN_REAL,
            .imag = MIN_IMAG
        },
        .max = {
            .real = MAX_REAL,
            .imag = MAX_IMAG
        }
    };

    bool running = true;
    bool dragging = false;
    int last_x = 0;
    int last_y = 0;

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEWHEEL:
                    {
                        const double zoom_factor = (event.wheel.y > 0) ? ZOOM_FACTOR : 1.0 / ZOOM_FACTOR;
                        int mouse_x = 0;
                        int mouse_y = 0;

                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        update_range_zoom(&range, mouse_x, mouse_y, zoom_factor);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        dragging = true;
                        last_x = event.button.x;
                        last_y = event.button.y;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        dragging = false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (dragging)
                    {
                        const int dx = event.motion.x - last_x;
                        const int dy = event.motion.y - last_y;

                        update_range_pan(&range, dx, dy);
                        last_x = event.motion.x;
                        last_y = event.motion.y;
                    }
                    break;
                default:
                    break;
            }
        }

        MBROT_generate_mandelbrot_set(image, &range, DIVERGE_THRESHOLD);
        MBROT_colorize_mandelbrot_set(image, DIVERGE_THRESHOLD, color_image);
        update_texture_from_image(texture, color_image);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    if (SAVE_PGM_IMAGE)
    {
        PGM_save(image, DIVERGE_THRESHOLD, MANDELBROT_IMAGE_PATH);
        PPM_save(color_image, DIVERGE_THRESHOLD, MANDELBROT_COLOR_IMAGE_PATH);
    }

    MBROT_free_mandebrot_set_image(image);
    MBROT_free_mandebrot_set_image(color_image);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

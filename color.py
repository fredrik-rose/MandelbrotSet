import argparse
import pathlib

import cv2
import numpy as np

from PIL import Image


UINT8_MAX = 255


def color_mandelbrot_set_image(input_image_path, output_image_path):
    assert input_image_path.suffix == ".pgm", input_image_path.suffix
    assert output_image_path.suffix == ".png", output_image_path.suffix
    image = cv2.imread(str(input_image_path), -1)
    color_array = np.zeros(image.shape + (3, ))
    normalized_image = image / UINT8_MAX
    color_array[:, :, 0] = 9.00 * np.power(1 - normalized_image, 1) * np.power(normalized_image, 3)  # Red
    color_array[:, :, 1] = 15.0 * np.power(1 - normalized_image, 2) * np.power(normalized_image, 2)  # Green
    color_array[:, :, 2] = 8.50 * np.power(1 - normalized_image, 3) * np.power(normalized_image, 1)  # Blue
    color_array *= UINT8_MAX
    color_image = Image.fromarray(color_array.astype(np.uint8), "RGB")
    color_image.save(output_image_path, "PNG")


def main():
    parser = argparse.ArgumentParser(description="Color a single channel gray scale Mandelbrot set image")
    parser.add_argument("--input", type=pathlib.Path,
                        help="the gray scale Mandelbrot set image in PGM format")
    parser.add_argument("--output", type=pathlib.Path,
                        help="the colored Mandelbrot set image in PNG format")
    args = parser.parse_args()
    color_mandelbrot_set_image(input_image_path=args.input, output_image_path=args.output)


if __name__ == "__main__":
    main()

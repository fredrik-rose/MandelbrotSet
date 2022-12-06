# Mandelbrot Set

<img src="img/mandelbrot.png" width="1000"/>

A C implementation of the Mandelbrot set. The Mandelbrot set is the set of complex numbers `c` for
which the function

```
f(z) = z^2 + c,
```

with z initialized as

```
z = 0,
```

does not diverge when iterated as

```
...f(f(f(0)))
```

The values `c` inside the set (i.e. the function does not diverge) and the values `c` far from the
set (i.e. the function diverges quickly) are not very interesting. What makes the Mandelbrot set
look cool are the values that are not part of the set but very close to the border of the set. These
will diverge slowly with many iterations required to determine that the values are actually not
part of the set. By using the number of iterations required to determine if a value is part of the
Mandelbrot set or not as pixels in an image we get the Mandelbrot set image.

A famous aspect of the Mandelbrot set is that you can "zoom" into the image indefinitely at the
border of the set to see various cool looking geometrical structures. This simple application does
not support this but it is possible to do a static zooming by changing the range parameters in the
main file.

The color map used for the colored Mandelbrot set image is a variant of the
[Bernstein polynomials](https://mathworld.wolfram.com/BernsteinPolynomial.html), with inspiration
from the [Solarian Programmer](https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/).

## Usage

To build and run the application run the following commands.

```
cmake -G Ninja -S <path to MandelbrotSet> -B build -DCMAKE_BUILD_TYPE=Release
cd build
ninja
./MandelbrotSet
```

This will generate the Mandelbrot set as an image named `mandelbrot.pgm`. This can be displayed in
e.g. IrfanView (or any other image tool that supports .pgm images).

The gray scale Mandelbrot set image produced by the MandelbrotSet application is quite nice but to
really make it beautiful we need to add some colors. This can be done with the following command:

```
python color.py --input mandelbrot.pgm --output mandelbrot.png
```

### Documentation

To build the documentation run the following commands.

```
cmake -G Ninja -S <path to MandelbrotSet> -B build -DCMAKE_BUILD_TYPE=Release
cd build
ninja doc
```

The generated documentation can be found in `html/index.html`.

### Test

To build and run the tests run the following commands.

```
cmake -G Ninja -S <path to MandelbrotSet> -B build -DCMAKE_BUILD_TYPE=Debug
cd build
ninja
ctest --verbose
```

Note that is is built using the `Debug` configuration. This includes address sanitizer (asan) and
undefined behavior sanitizer (ubsan). These are runtime instrumentations that will detect memory
errors and undefined behavior. Asserts are also enabled in this configuration. The `Debug`
configuration also includes debug information which makes it easier to find where a particular
problem occurred as it will contain a detailed call stack.

#### Test under valgrind

To build and run the tests under valgrind run the following commands.

```
cmake -G Ninja -S <path to MandelbrotSet> -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cd build
ninja
ctest -T memcheck --verbose
```

Note that the `RelWithDebInfo` configurations is used here. This configuration includes debug
information which makes it easier to find where a particular problem occurred as it will contain a
detailed call stack. Unfortunately valgrind is not compatible with the sanitizers used in the
`Debug` configuration. To get full coverage of the dynamic code analyzers it is therefore required
to run the test under two configurations (`Debug` and `RelWithDebInfo` with valgrind).

### Requirements

The following are required

* gcc
* cmake
* ninja
* doxygen
* graphviz
* cppcheck
* clang-tidy
* valgrind
* include-what-you-use

On an Ubuntu system these can be installed with the following commands.

```
sudo apt-get update && sudo apt-get upgrade -y
sudo apt autoremove -y
sudo apt-get install gcc -y
sudo apt-get install cmake -y
sudo apt install ninja-build -y
sudo apt-get install doxygen -y
sudo apt install graphviz -y
sudo apt-get install cppcheck -y
sudo apt-get install clang-tidy -y
sudo apt install valgrind -y
sudo apt install iwyu -y
```

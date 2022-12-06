# Mandelbrot Set

A C implementation of the Mandelbrot set.

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

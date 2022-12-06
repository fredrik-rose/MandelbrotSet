add_executable(MandelbrotSetLibTests mandelbrot_set_tests.c)

target_link_libraries(MandelbrotSetLibTests PRIVATE
    MandelbrotSetLib
)

add_test(NAME MandelbrotSetLibTests COMMAND MandelbrotSetLibTests)

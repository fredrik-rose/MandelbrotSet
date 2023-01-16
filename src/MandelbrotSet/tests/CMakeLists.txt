add_executable(MandelbrotSetCpuLibTests mandelbrot_set_tests.c)

target_link_libraries(MandelbrotSetCpuLibTests PRIVATE
    MandelbrotSetCpuLib
)

add_test(NAME MandelbrotSetCpuLibTests COMMAND MandelbrotSetCpuLibTests)

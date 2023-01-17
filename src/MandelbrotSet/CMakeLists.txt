add_library(MandelbrotSetLib
    pgm.c)

add_library(MandelbrotSetCpuLib
    mandelbrot_set_cpu.c)

add_library(MandelbrotSetGpuLib
    mandelbrot_set_gpu.cu)

target_link_libraries(MandelbrotSetLib PUBLIC
    m
)

target_link_libraries(MandelbrotSetCpuLib PUBLIC
    MandelbrotSetLib
)

target_link_libraries(MandelbrotSetGpuLib PUBLIC
    MandelbrotSetLib
)

target_include_directories(MandelbrotSetLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)

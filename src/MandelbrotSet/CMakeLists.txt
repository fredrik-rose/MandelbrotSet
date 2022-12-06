add_library(MandelbrotSetLib
    pgm.c)

target_link_libraries(MandelbrotSetLib PUBLIC
    m
)

target_include_directories(MandelbrotSetLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

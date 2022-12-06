add_library(MandelbrotSetLib INTERFACE)

target_link_libraries(MandelbrotSetLib INTERFACE
    m
)

target_include_directories(MandelbrotSetLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

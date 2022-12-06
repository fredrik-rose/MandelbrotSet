add_library(Complex INTERFACE)

target_link_libraries(Complex INTERFACE
    m
)

target_include_directories(Complex INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

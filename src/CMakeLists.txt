add_subdirectory(MandelbrotSet)

target_link_libraries(${PROJECT_NAME} PRIVATE
    MandelbrotSetLib
)

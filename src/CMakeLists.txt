add_subdirectory(MandelbrotSet)

target_link_libraries(${PROJECT_NAME}Cpu PRIVATE
    MandelbrotSetCpuLib
)

target_link_libraries(${PROJECT_NAME}Gpu PRIVATE
    MandelbrotSetGpuLib
)

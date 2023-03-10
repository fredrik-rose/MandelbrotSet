cmake_minimum_required(VERSION 3.16)

project(MandelbrotSet VERSION 1.0 LANGUAGES C CUDA)

find_program(IWYU_PATH NAMES include-what-you-use iwyu)
if (NOT IWYU_PATH)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()
# Include what you use seems to have a bug, therefore we need to add the ugly include path.
set(CMAKE_C_INCLUDE_WHAT_YOU_USE "${IWYU_PATH};-I/usr/lib/llvm-10/lib/clang/10.0.0/include")

set(CMAKE_C_STANDARD 11)

list(
    APPEND  _gcc_compile_options
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wfloat-equal
    -Wundef
    -Wshadow
    -Wpointer-arith
    -Wcast-align
    -Wstrict-prototypes
    -Wstrict-overflow=5
    -Wwrite-strings
    -Wcast-qual
    -Wswitch-default
    -Wswitch-enum
    -Wconversion
    -Wunreachable-code
)

list(
    APPEND _gcc_relwithdebug_compile_options
    -fno-omit-frame-pointer
)

list(
    APPEND _gcc_debug_compile_options
    -fno-omit-frame-pointer
    -fsanitize=address  # Address sanitizer
    -fsanitize=undefined  # Undefined behavior sanitizer
)

list(
    APPEND _debug_link_options
    -fsanitize=address  # Address sanitizer
    -fsanitize=undefined  # Undefined behavior sanitize
)

# To be able to compile device functions for both C and CUDA.
add_compile_definitions("$<$<COMPILE_LANGUAGE:C>:__device__=>")

add_compile_options(
    "$<$<COMPILE_LANGUAGE:C>:${_gcc_compile_options}>"
    "$<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:RELWITHDEBINFO>>:${_gcc_relwithdebug_compile_options}>"
    "$<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:DEBUG>>:${_gcc_debug_compile_options}>"
)

add_link_options(
    "$<$<CONFIG:DEBUG>:${_debug_link_options}>"
)

find_program(CMAKE_C_CPPCHECK NAMES cppcheck)
if (CMAKE_C_CPPCHECK)
    list(
        APPEND CMAKE_C_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
            "--error-exitcode=-1"
    )
endif()

set(CMAKE_C_CLANG_TIDY clang-tidy
    -checks=*,-llvm-header-guard,readability-*,-readability-magic-numbers,-cppcoreguidelines-avoid-magic-numbers,
    -warnings-as-errors=* -header-filter=.*)

set(MEMORYCHECK_COMMAND_OPTIONS
    "--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1")

include(CTest)

add_executable(${PROJECT_NAME}Cpu src/main.c)

add_executable(${PROJECT_NAME}Gpu src/main.c)

add_subdirectory(src)

find_package(Doxygen REQUIRED doxygen dot)
set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_PACKAGE YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_EXTRACT_ANON_NSPACES YES)
set(DOXYGEN_WARN_NO_PARAMDOC YES)
set(DOXYGEN_EXCLUDE "LICENSE.txt")
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_INLINE_SOURCES YES)
set(DOXYGEN_REFERENCED_BY_RELATION YES)
set(DOXYGEN_REFERENCES_RELATION YES)
set(DOXYGEN_REFERENCES_LINK_SOURCE NO)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CALLER_GRAPH YES)
set(DOXYGEN_FILE_PATTERNS "*.c,*.h,*.cu,*.md")
set(DOXYGEN_EXTENSION_MAPPING "cu=c++")
doxygen_add_docs(doc)

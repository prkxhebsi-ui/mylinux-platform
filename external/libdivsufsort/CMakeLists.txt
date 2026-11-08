cmake_minimum_required(VERSION 3.16)
project(mylinux_libdivsufsort C)

add_library(divsufsort STATIC
    src/divsufsort.c
)

target_include_directories(divsufsort PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test_divsufsort tests/test.c)
target_link_libraries(test_divsufsort PRIVATE divsufsort)

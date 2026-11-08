cmake_minimum_required(VERSION 3.16)
project(mylinux_libconfig C)

add_library(config STATIC src/config.c)

target_include_directories(config PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test_config tests/test.c)
target_link_libraries(test_config PRIVATE config)

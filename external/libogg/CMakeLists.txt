cmake_minimum_required(VERSION 3.16)
project(mylinux_libogg C)

add_library(ogg STATIC src/ogg.c)

target_include_directories(ogg PUBLIC include)

add_executable(test_ogg tests/test.c)
target_link_libraries(test_ogg PRIVATE ogg)

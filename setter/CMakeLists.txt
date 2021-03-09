cmake_minimum_required(VERSION 2.20)
project(setter C)

set(CMAKE_C_STANDARD 90)

add_subdirectory(src)

message(${CMAKE_C_COMPILER_VERSION})

add_subdirectory(src/unix)
add_subdirectory(src/linux)



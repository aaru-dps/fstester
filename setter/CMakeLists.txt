cmake_minimum_required(VERSION 2.20)

project(setter C)

set(CMAKE_C_STANDARD 90)

add_subdirectory(src)

add_subdirectory(src/dos)
add_subdirectory(src/unix)
add_subdirectory(src/linux)



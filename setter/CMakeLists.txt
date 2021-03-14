cmake_minimum_required(VERSION 2.20)

project(setter C)

set(CMAKE_C_STANDARD 90)

message("Detected system name: ${CMAKE_SYSTEM_NAME}")
message("Detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory(src)

add_subdirectory(src/dos)
add_subdirectory(src/unix)
add_subdirectory(src/linux)
add_subdirectory(src/win32)
add_subdirectory(src/macos)


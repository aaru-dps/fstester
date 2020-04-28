cmake_minimum_required(VERSION 3.10)
project(setter C)

set(CMAKE_C_STANDARD 90)

add_executable(setter src/consts.h src/defs.h src/main.h src/dosos2.h src/os2_16.h src/os2_32.h src/main.c src/dos.c src/os2_16.c src/os2_32.c src/win32.c src/win32.h src/unix.c src/macos.c src/macos.h src/unix.h src/linux.c src/linux.h)
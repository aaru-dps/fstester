if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    return()
endif()

project(
        fssetter-win32
        DESCRIPTION "Filesystem test creator for 32-bit and 64-bit Windows"
        LANGUAGES C)

set(PLATFORM_SOURCES win32.c)

set(EXECUTABLE_NAME "fssetter-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

add_executable(${EXECUTABLE_NAME} ${PLATFORM_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} core)
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    return()
endif()

project(
        fssetter-linux
        DESCRIPTION "Filesystem test creator for Linux"
        LANGUAGES C)

set(PLATFORM_SOURCES attr.c sparse.c xattr.c)

set(EXECUTABLE_NAME "fssetter-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

add_executable(${EXECUTABLE_NAME} ${PLATFORM_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} core unix)
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    return()
endif()

project(
        fssetter-win32
        DESCRIPTION "Filesystem test creator for 32-bit and 64-bit Windows"
        LANGUAGES C)

set(PLATFORM_SOURCES attr.c deleted.c dirdepth.c filename.c files.c frag.c links.c os.c perms.c rsrcfork.c sparse.c time.c volume.c xattr.c attr.h rsrcfork.h xattr.h links.h volume.h time.h os.h sparse.h)

set(EXECUTABLE_NAME "fssetter-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

add_executable(${EXECUTABLE_NAME} ${PLATFORM_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} core)
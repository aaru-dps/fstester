if(NOT DOS)
    return()
endif()

project(fssetter-dos
        DESCRIPTION "Filesystem test creator for DOS"
        LANGUAGES C)

set(PLATFORM_SOURCES attr.c deleted.c dirdepth.c filename.c files.c frag.c links.c os.c perms.c rsrcfork.c sparse.c time.h time.c volume.c xattr.c dos.c attr.h dosuname.c dosuname.h)

set(EXECUTABLE_NAME "fssetter")

add_executable(${EXECUTABLE_NAME} ${PLATFORM_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} core)
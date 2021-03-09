if(NOT "${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    return()
endif()

set(UNIX_SOURCES attr.c deleted.c dirdepth.c filename.c files.c frag.c links.c os.c perms.c rsrcfork.c sparse.c time.c volume.c xattr.c)

add_library(unix ${UNIX_SOURCES})

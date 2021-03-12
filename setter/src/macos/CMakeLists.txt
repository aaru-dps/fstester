if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Retro68" AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "RetroPPC")
    return()
endif()

include(CheckIncludeFiles)

project(
        fssetter-macos
        DESCRIPTION "Filesystem test creator for MacOS"
        LANGUAGES C)

add_definitions(-Dmacintosh)
add_definitions(-DRetro68)

CHECK_INCLUDE_FILES("Aliases.h" HAVE_ALIASES_H)
CHECK_INCLUDE_FILES("Multiverse.h" HAVE_MULTIVERSE_H)

if(HAVE_ALIASES_H)
    add_definitions(-DHAVE_ALIASES_H)
endif()

if(HAVE_MULTIVERSE_H)
    add_definitions(-DHAVE_MULTIVERSE_H)
endif()

set(PLATFORM_SOURCES attr.c deleted.c dirdepth.c filename.c files.c frag.c links.c os.c perms.c rsrcfork.c sparse.c time.c volume.c xattr.c macos.h macos.r)

if(${CMAKE_SYSTEM_NAME} MATCHES "Retro68")
    set(PROCESSOR "m68k")
else()
    set(PROCESSOR "ppc")
endif()

set(EXECUTABLE_NAME "fssetter-macos-${PROCESSOR}")

#add_application(${EXECUTABLE_NAME} ${PLATFORM_SOURCES})

#target_link_libraries(${EXECUTABLE_NAME} core)

add_application(${EXECUTABLE_NAME} ../main.c ${PLATFORM_SOURCES})
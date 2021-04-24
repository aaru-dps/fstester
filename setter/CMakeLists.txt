# /****************************************************************************
# Aaru Data Preservation Suite
# -----------------------------------------------------------------------------
#
# Author(s)      : Natalia Portillo
#
# --[ License ] ---------------------------------------------------------------
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# -----------------------------------------------------------------------------
# Copyright (C) 2011-2021 Natalia Portillo
# *****************************************************************************/

cmake_minimum_required(VERSION 2.8)

project(fssetter-test
        DESCRIPTION "Filesystem test creator"
        LANGUAGES C)

set(CMAKE_C_STANDARD 90)

message("Detected system name: ${CMAKE_SYSTEM_NAME}")
message("Detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")

# It's best to hide all the details of setting up the variable SRCS in a CMake
# macro. The macro can then be called in all the project CMake list files to add
# sources.
#
# The macro first computes the path of the source file relative to the project
# root for each argument. If the macro is invoked from inside a project sub
# directory the new value of the variable SRCS needs to be propagated to the
# parent folder by using the PARENT_SCOPE option.
#
# Source: http://stackoverflow.com/questions/7046956/populating-srcs-from-cmakelists-txt-in-subdirectories
macro(add_sources)
    file(RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(_src ${ARGN})
        if(_relPath)
            list(APPEND SRCS "${_relPath}/${_src}")
        else()
            list(APPEND SRCS "${_src}")
        endif()
    endforeach()
    if(_relPath)
        # propagate to parent directory
        set(SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()

# Based on add_sources() but to add compiler definitions
macro(add_sub_definitions)
    file(RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(_def ${ARGN})
        list(APPEND PRJ_DEFINITIONS "${_def}")
    endforeach()
    if(_relPath)
        # propagate to parent directory
        set(PRJ_DEFINITIONS ${PRJ_DEFINITIONS} PARENT_SCOPE)
    endif()
endmacro()

# Based on add_sources() but to add libraries
macro(add_sub_libraries)
    file(RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(_lib ${ARGN})
        list(APPEND PRJ_LIBRARIES "${_lib}")
    endforeach()
    if(_relPath)
        # propagate to parent directory
        set(PRJ_LIBRARIES ${PRJ_LIBRARIES} PARENT_SCOPE)
    endif()
endmacro()

set(EXECUTABLE_NAME "fssetter-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory(src)

add_compile_definitions(${PRJ_DEFINITIONS})

if(${CMAKE_SYSTEM_NAME} MATCHES "Retro68|RetroPPC")
    add_application(${EXECUTABLE_NAME} ${SRCS})
else()
    add_executable(${EXECUTABLE_NAME} ${SRCS})
endif()

target_link_libraries(${EXECUTABLE_NAME} ${PRJ_LIBRARIES})


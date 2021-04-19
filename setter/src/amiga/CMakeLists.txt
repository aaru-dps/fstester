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

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "AmigaOS|MorphOS" AND NOT AROS)
    message("Ignoring Amiga")
    return()
endif()

project(
        fssetter-amiga
        DESCRIPTION "Filesystem test creator for AmigaOS and compatibles"
        LANGUAGES C)

add_definitions(-D__USE_INLINE__)

set(PLATFORM_SOURCES attr.c deleted.c dirdepth.c filename.c files.c frag.c links.c os.c perms.c perms.h rsrcfork.c sparse.c time.c time.h volume.c xattr.c)

set(EXECUTABLE_NAME "fssetter-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

add_executable(${EXECUTABLE_NAME} ${PLATFORM_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} core)
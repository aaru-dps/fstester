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

if(NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES "i386")
    return()
endif()

project(fssetter-os2
        DESCRIPTION "Filesystem test creator for 32-bit OS/2"
        LANGUAGES C)

set(SUBPLATFORM_SOURCES os.c xattr.c)

set(EXECUTABLE_NAME "fssetter32")

find_library(OS2LIB "os2386")

add_executable(${EXECUTABLE_NAME} ${SUBPLATFORM_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} core platform)
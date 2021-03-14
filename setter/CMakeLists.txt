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

cmake_minimum_required(VERSION 2.20)

project(setter C)

set(CMAKE_C_STANDARD 90)

message("Detected system name: ${CMAKE_SYSTEM_NAME}")
message("Detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")

add_subdirectory(src)

add_subdirectory(src/dos)
add_subdirectory(src/unix)
add_subdirectory(src/linux)
add_subdirectory(src/win32)
add_subdirectory(src/macos)


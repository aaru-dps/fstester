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

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    return()
endif()

find_library(CARBON_LIBRARY NAMES Carbon)

add_sources(os.c darwin.h volume.c volume.h attr.c attr.h rsrcfork.c rsrcfork.h sparse.c xattr.c xattr.h)

if(CARBON_LIBRARY)
    add_sub_definitions(HAVE_CARBON)
    add_sources(carbon.c carbon.h)
endif()

if(CARBON_LIBRARY)
    add_sub_libraries(${CARBON_LIBRARY})
endif()

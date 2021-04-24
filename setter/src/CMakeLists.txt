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

add_subdirectory(macos)
add_subdirectory(dos)
add_subdirectory(win32)
add_subdirectory(unix)
add_subdirectory(beos)
add_subdirectory(amiga)
add_subdirectory(os2)

# This must be after all directories
add_sources(main.c main.h log.c log.h)

# Even if empty it needs to be present
add_sub_definitions()

# Even if empty it needs to be present
add_sub_libraries()

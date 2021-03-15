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

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    return()
endif()

include(CheckSymbolExists)
include(CheckStructHasMember)

CHECK_SYMBOL_EXISTS(statfs "sys/statfs.h" HAVE_SYS_STATFS)
CHECK_SYMBOL_EXISTS(statfs "sys/mount.h" HAVE_SYS_MOUNT)

# Linux and FreeBSD
if(HAVE_SYS_STATFS)
    message("-- Found statfs in sys/statfs.h")
    add_definitions(-DHAVE_SYS_STATFS_H)
    CHECK_STRUCT_HAS_MEMBER(statfs "f_namelen" "sys/statfs.h" HAVE_STATFS_FNAMELEN)
endif()

# Darwin and most other BSDs
if(HAVE_SYS_MOUNT)
    message("-- Found statfs in sys/mount.h")
    add_definitions(-DHAVE_SYS_MOUNT_H)
    CHECK_STRUCT_HAS_MEMBER(statfs "f_namelen" "sys/statfs.h" HAVE_STATFS_FNAMELEN)
endif()

if(HAVE_STATFS_FNAMELEN)
    message("-- statfs has f_namelen member")
    add_definitions(-DUSE_STATFS_FNAMELEN)
    CHECK_STRUCT_HAS_MEMBER(statfs "f_namelen" "sys/statfs.h" HAVE_STATFS_FNAMELEN)
endif()

set(UNIX_SOURCES attr.c deleted.c dirdepth.c filename.c files.c frag.c links.c os.c perms.c rsrcfork.c sparse.c time.c volume.c xattr.c)

add_library(unix ${UNIX_SOURCES})
/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

    Author(s)      : Natalia Portillo

--[ License ] ---------------------------------------------------------------
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as
     published by the Free Software Foundation, either version 3 of the
     License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
Copyright (C) 2011-2021 Natalia Portillo
*****************************************************************************/

#ifndef AARU_FSTESTER_SETTER_SRC_BEOS_VOLUME_H_
#define AARU_FSTESTER_SETTER_SRC_BEOS_VOLUME_H_

#include <fs_info.h>

#ifndef B_FS_IS_READONLY
#define B_FS_IS_READONLY 0x00000001
#endif

#ifndef B_FS_IS_REMOVABLE
#define B_FS_IS_REMOVABLE 0x00000002
#endif

#ifndef B_FS_IS_PERSISTENT
#define B_FS_IS_PERSISTENT 0x00000004
#endif

#ifndef B_FS_IS_SHARED
#define B_FS_IS_SHARED 0x00000008
#endif

#ifndef B_FS_HAS_MIME
#define B_FS_HAS_MIME 0x00010000
#endif

#ifndef B_FS_HAS_ATTR
#define B_FS_HAS_ATTR 0x00020000
#endif

#ifndef B_FS_HAS_QUERY
#define B_FS_HAS_QUERY 0x00040000
#endif

#ifndef B_FS_HAS_SELF_HEALING_LINKS
#define B_FS_HAS_SELF_HEALING_LINKS 0x00080000
#endif

#ifndef B_FS_HAS_ALIASES
#define B_FS_HAS_ALIASES 0x00100000
#endif

#ifndef B_FS_SUPPORTS_NODE_MONITORING
#define B_FS_SUPPORTS_NODE_MONITORING 0x00200000
#endif

#ifndef B_FS_SUPPORTS_MONITOR_CHILDREN
#define B_FS_SUPPORTS_MONITOR_CHILDREN 0x00400000
#endif

#endif // AARU_FSTESTER_SETTER_SRC_BEOS_VOLUME_H_

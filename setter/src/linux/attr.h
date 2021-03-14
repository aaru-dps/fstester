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

#ifndef AARU_FSTESTER_SETTER_SRC_LINUX_ATTR_H_
#define AARU_FSTESTER_SETTER_SRC_LINUX_ATTR_H_

typedef struct
{
    char filename[16];
    char contents[256];
    char description[256];
    int  attr;
} linux_attr_tests_t;

#define KNOWN_LINUX_ATTRS 12

#ifndef FS_SECRM_FL
#define FS_SECRM_FL 0x00000001 /* Secure deletion */
#endif
#ifndef FS_UNRM_FL
#define FS_UNRM_FL 0x00000002 /* Undelete */
#endif

#ifndef FS_COMPR_FL
#define FS_COMPR_FL 0x00000004 /* Compress file */
#endif

#ifndef FS_SYNC_FL
#define FS_SYNC_FL 0x00000008 /* Synchronous updates */
#endif

#ifndef FS_IMMUTABLE_FL
#define FS_IMMUTABLE_FL 0x00000010 /* Immutable file */
#endif

#ifndef FS_APPEND_FL
#define FS_APPEND_FL 0x00000020 /* writes to file may only append */
#endif

#ifndef FS_NODUMP_FL
#define FS_NODUMP_FL 0x00000040 /* do not dump file */
#endif

#ifndef FS_NOATIME_FL
#define FS_NOATIME_FL 0x00000080 /* do not update atime */
#endif

#ifndef FS_JOURNAL_DATA_FL
#define FS_JOURNAL_DATA_FL 0x00004000 /* Reserved for ext3 */
#endif

#ifndef FS_NOTAIL_FL
#define FS_NOTAIL_FL 0x00008000 /* file tail should not be merged */
#endif

#ifndef FS_NOCOW_FL
#define FS_NOCOW_FL 0x00800000 /* Do not cow file */
#endif

#ifndef FS_PROJINHERIT_FL
#define FS_PROJINHERIT_FL 0x20000000 /* Create with parents projid */
#endif

static const linux_attr_tests_t linux_attrs[KNOWN_LINUX_ATTRS] = {
    {"APPEND", "This file is now append only", "File with append only flag", FS_APPEND_FL},
    {"COMPRESS", "This file is now compressed", "File with compressed flag", FS_COMPR_FL},
    {"IMMUTABLE", "This file is now immutable", "File with immutable flag", FS_IMMUTABLE_FL},
    {"JOURNALED", "This file is now journaled", "File with journaled flag", FS_JOURNAL_DATA_FL},
    {"NOATIME", "This file is now noatime", "File with noatime flag", FS_NOATIME_FL},
    {"NOCOW", "This file is now not copy on write", "File with no copy on write flag", FS_NOCOW_FL},
    {"NODUMP", "This file is now not dumpable", "File with no dump flag", FS_NODUMP_FL},
    {"NOTAIL", "This file is now not tailed", "File with no tail flag", FS_NOTAIL_FL},
    {"PROJECTINHERIT", "This file is now inheriting project id", "File with project inherit flag", FS_PROJINHERIT_FL},
    {"SECUREDELETION", "This file is now secure deletable", "File with secure delete flag", FS_SECRM_FL},
    {"SYNC", "This file is now synchronous", "File with synchronous flag", FS_SYNC_FL},
    {"UNREMOVABLE", "This file is now marked for undeletion", "File with undeletion flag", FS_UNRM_FL},
};

#endif // AARU_FSTESTER_SETTER_SRC_LINUX_ATTR_H_

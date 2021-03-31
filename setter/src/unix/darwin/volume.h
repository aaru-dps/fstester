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

#ifndef AARU_FSTESTER_SETTER_SRC_DARWIN_VOLUME_H_
#define AARU_FSTESTER_SETTER_SRC_DARWIN_VOLUME_H_

#include <sys/mount.h>

#ifndef MNT_RDONLY
#define MNT_RDONLY 0x00000001
#endif

#ifndef MNT_SYNCHRONOUS
#define MNT_SYNCHRONOUS 0x00000002
#endif

#ifndef MNT_NOEXEC
#define MNT_NOEXEC 0x00000004
#endif

#ifndef MNT_NOSUID
#define MNT_NOSUID 0x00000008
#endif

#ifndef MNT_NODEV
#define MNT_NODEV 0x00000010
#endif

#ifndef MNT_UNION
#define MNT_UNION 0x00000020
#endif

#ifndef MNT_ASYNC
#define MNT_ASYNC 0x00000040
#endif

#ifndef MNT_CPROTECT
#define MNT_CPROTECT 0x00000080
#endif

#ifndef MNT_EXPORTED
#define MNT_EXPORTED 0x00000100
#endif

#ifndef MNT_REMOVABLE
#define MNT_REMOVABLE 0x00000200
#endif

#ifndef MNT_QUARANTINE
#define MNT_QUARANTINE 0x00000400
#endif

#ifndef MNT_LOCAL
#define MNT_LOCAL 0x00001000
#endif

#ifndef MNT_QUOTA
#define MNT_QUOTA 0x00002000
#endif

#ifndef MNT_ROOTFS
#define MNT_ROOTFS 0x00004000
#endif

#ifndef MNT_DOVOLFS
#define MNT_DOVOLFS 0x00008000
#endif

#ifndef MNT_DONTBROWSE
#define MNT_DONTBROWSE 0x00100000
#endif

#ifndef MNT_IGNORE_OWNERSHIP
#define MNT_IGNORE_OWNERSHIP 0x00200000
#endif

#ifndef MNT_AUTOMOUNTED
#define MNT_AUTOMOUNTED 0x00400000
#endif

#ifndef MNT_JOURNALED
#define MNT_JOURNALED 0x00800000
#endif

#ifndef MNT_NOUSERXATTR
#define MNT_NOUSERXATTR 0x01000000
#endif

#ifndef MNT_DEFWRITE
#define MNT_DEFWRITE 0x02000000
#endif

#ifndef MNT_MULTILABEL
#define MNT_MULTILABEL 0x04000000
#endif

#ifndef MNT_NOATIME
#define MNT_NOATIME 0x10000000
#endif

#ifndef MNT_SNAPSHOT
#define MNT_SNAPSHOT 0x40000000
#endif

#ifndef MNT_STRICTATIME
#define MNT_STRICTATIME 0x80000000
#endif

#ifndef VOL_CAPABILITIES_FORMAT
#define VOL_CAPABILITIES_FORMAT 0
#endif

#ifndef VOL_CAP_FMT_PERSISTENTOBJECTIDS
#define VOL_CAP_FMT_PERSISTENTOBJECTIDS 0x00000001
#endif

#ifndef VOL_CAP_FMT_SYMBOLICLINKS
#define VOL_CAP_FMT_SYMBOLICLINKS 0x00000002
#endif

#ifndef VOL_CAP_FMT_HARDLINKS
#define VOL_CAP_FMT_HARDLINKS 0x00000004
#endif

#ifndef VOL_CAP_FMT_JOURNAL
#define VOL_CAP_FMT_JOURNAL 0x00000008
#endif

#ifndef VOL_CAP_FMT_JOURNAL_ACTIVE
#define VOL_CAP_FMT_JOURNAL_ACTIVE 0x00000010
#endif

#ifndef VOL_CAP_FMT_NO_ROOT_TIMES
#define VOL_CAP_FMT_NO_ROOT_TIMES 0x00000020
#endif

#ifndef VOL_CAP_FMT_SPARSE_FILES
#define VOL_CAP_FMT_SPARSE_FILES 0x00000040
#endif

#ifndef VOL_CAP_FMT_ZERO_RUNS
#define VOL_CAP_FMT_ZERO_RUNS 0x00000080
#endif

#ifndef VOL_CAP_FMT_CASE_SENSITIVE
#define VOL_CAP_FMT_CASE_SENSITIVE 0x00000100
#endif

#ifndef VOL_CAP_FMT_CASE_PRESERVING
#define VOL_CAP_FMT_CASE_PRESERVING 0x00000200
#endif

#ifndef VOL_CAP_FMT_FAST_STATFS
#define VOL_CAP_FMT_FAST_STATFS 0x00000400
#endif

#ifndef VOL_CAP_FMT_2TB_FILESIZE
#define VOL_CAP_FMT_2TB_FILESIZE 0x00000800
#endif

#ifndef VOL_CAP_FMT_OPENDENYMODES
#define VOL_CAP_FMT_OPENDENYMODES 0x00001000
#endif

#ifndef VOL_CAP_FMT_HIDDEN_FILES
#define VOL_CAP_FMT_HIDDEN_FILES 0x00002000
#endif

#ifndef VOL_CAP_FMT_PATH_FROM_ID
#define VOL_CAP_FMT_PATH_FROM_ID 0x00004000
#endif

#ifndef VOL_CAP_FMT_NO_VOLUME_SIZES
#define VOL_CAP_FMT_NO_VOLUME_SIZES 0x00008000
#endif

#ifndef VOL_CAP_FMT_DECMPFS_COMPRESSION
#define VOL_CAP_FMT_DECMPFS_COMPRESSION 0x00010000
#endif

#ifndef VOL_CAP_FMT_64BIT_OBJECT_IDS
#define VOL_CAP_FMT_64BIT_OBJECT_IDS 0x00020000
#endif

#ifndef VOL_CAP_FMT_DIR_HARDLINKS
#define VOL_CAP_FMT_DIR_HARDLINKS 0x00040000
#endif

#ifndef VOL_CAP_FMT_DOCUMENT_ID
#define VOL_CAP_FMT_DOCUMENT_ID 0x00080000
#endif

#ifndef VOL_CAP_FMT_WRITE_GENERATION_COUNT
#define VOL_CAP_FMT_WRITE_GENERATION_COUNT 0x00100000
#endif

#ifndef VOL_CAP_FMT_NO_IMMUTABLE_FILES
#define VOL_CAP_FMT_NO_IMMUTABLE_FILES 0x00200000
#endif

#ifndef VOL_CAP_FMT_NO_PERMISSIONS
#define VOL_CAP_FMT_NO_PERMISSIONS 0x00400000
#endif

#ifndef VOL_CAP_FMT_SHARED_SPACE
#define VOL_CAP_FMT_SHARED_SPACE 0x00800000
#endif

#ifndef VOL_CAP_FMT_VOL_GROUPS
#define VOL_CAP_FMT_VOL_GROUPS 0x01000000
#endif

#ifndef VOL_CAP_FMT_SEALED
#define VOL_CAP_FMT_SEALED 0x02000000
#endif

#endif // AARU_FSTESTER_SETTER_SRC_DARWIN_VOLUME_H_

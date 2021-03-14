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

#ifndef AARU_FSTESTER_SETTER_SRC_WIN32_VOLUME_H_
#define AARU_FSTESTER_SETTER_SRC_WIN32_VOLUME_H_

#include <windows.h>

#include "win32.h"

BOOL(WINAPI* WinGetDiskFreeSpaceExA)(LPCSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);

#ifndef FILE_CASE_PRESERVED_NAMES
#define FILE_CASE_PRESERVED_NAMES 0x00000002
#endif

#ifndef FILE_CASE_SENSITIVE_SEARCH
#define FILE_CASE_SENSITIVE_SEARCH 0x00000001
#endif

#ifndef FILE_DAX_VOLUME
#define FILE_DAX_VOLUME 0x20000000
#endif

#ifndef FILE_FILE_COMPRESSION
#define FILE_FILE_COMPRESSION 0x00000010
#endif

#ifndef FILE_NAMED_STREAMS
#define FILE_NAMED_STREAMS 0x00040000
#endif

#ifndef FILE_PERSISTENT_ACLS
#define FILE_PERSISTENT_ACLS 0x00000008
#endif

#ifndef FILE_READ_ONLY_VOLUME
#define FILE_READ_ONLY_VOLUME 0x00080000
#endif

#ifndef FILE_SEQUENTIAL_WRITE_ONCE
#define FILE_SEQUENTIAL_WRITE_ONCE 0x00100000
#endif

#ifndef FILE_SUPPORTS_ENCRYPTION
#define FILE_SUPPORTS_ENCRYPTION 0x00020000
#endif

#ifndef FILE_SUPPORTS_EXTENDED_ATTRIBUTES
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES 0x00800000
#endif

#ifndef FILE_SUPPORTS_HARD_LINKS
#define FILE_SUPPORTS_HARD_LINKS 0x00400000
#endif

#ifndef FILE_SUPPORTS_OBJECT_IDS
#define FILE_SUPPORTS_OBJECT_IDS 0x00010000
#endif

#ifndef FILE_SUPPORTS_OPEN_BY_FILE_ID
#define FILE_SUPPORTS_OPEN_BY_FILE_ID 0x01000000
#endif

#ifndef FILE_SUPPORTS_REPARSE_POINTS
#define FILE_SUPPORTS_REPARSE_POINTS 0x00000080
#endif

#ifndef FILE_SUPPORTS_SPARSE_FILES
#define FILE_SUPPORTS_SPARSE_FILES 0x00000040
#endif

#ifndef FILE_SUPPORTS_TRANSACTIONS
#define FILE_SUPPORTS_TRANSACTIONS 0x00200000
#endif

#ifndef FILE_SUPPORTS_USN_JOURNAL
#define FILE_SUPPORTS_USN_JOURNAL 0x02000000
#endif

#ifndef FILE_UNICODE_ON_DISK
#define FILE_UNICODE_ON_DISK 0x00000004
#endif

#ifndef FILE_VOLUME_IS_COMPRESSED
#define FILE_VOLUME_IS_COMPRESSED 0x00008000
#endif

#ifndef FILE_VOLUME_QUOTAS
#define FILE_VOLUME_QUOTAS 0x00000020
#endif

#ifndef FILE_ATTRIBUTE_ARCHIVE
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#endif

#ifndef FILE_ATTRIBUTE_ENCRYPTED
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000
#endif

#ifndef FILE_ATTRIBUTE_HIDDEN
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#endif

#ifndef FILE_ATTRIBUTE_NORMAL
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#endif

#ifndef FILE_ATTRIBUTE_OFFLINE
#define FILE_ATTRIBUTE_OFFLINE 0x00001000
#endif

#ifndef FILE_ATTRIBUTE_READONLY
#define FILE_ATTRIBUTE_READONLY 0x00000001
#endif

#ifndef FILE_ATTRIBUTE_SYSTEM
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#endif

#ifndef FILE_ATTRIBUTE_TEMPORARY
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#endif

#ifndef FILE_ATTRIBUTE_COMPRESSED
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800
#endif

#ifndef FILE_RETURNS_CLEANUP_RESULT_INFO
#define FILE_RETURNS_CLEANUP_RESULT_INFO 0x00000200
#endif

#ifndef FILE_SUPPORTS_POSIX_UNLINK_RENAME
#define FILE_SUPPORTS_POSIX_UNLINK_RENAME 0x00000400
#endif

#ifndef FS_LFN_APIS
#define FS_LFN_APIS 0x00004000
#endif

#endif // AARU_FSTESTER_SETTER_SRC_WIN32_VOLUME_H_

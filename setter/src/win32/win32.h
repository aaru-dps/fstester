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

#pragma clang diagnostic push
#pragma ide diagnostic   ignored "bugprone-reserved-identifier"

#ifndef AARU_FSTESTER_SETTER_SRC_WIN32_H
#define AARU_FSTESTER_SETTER_SRC_WIN32_H

#include <windows.h>

#ifndef VER_PLATFORM_WIN32_WINDOWS
#define VER_PLATFORM_WIN32_WINDOWS 0x0001
#endif

#ifndef VER_PLATFORM_WIN32_NT
#define VER_PLATFORM_WIN32_NT 0x0002
#endif

typedef LONG NTSTATUS;

#ifndef NTAPI
#define NTAPI __stdcall
#endif

typedef struct _WIN_OSVERSIONINFOA
{
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR  szCSDVersion[128]; // Maintenance string for PSS usage
} WIN_OSVERSIONINFOA, *WIN_POSVERSIONINFOA, *WIN_LPOSVERSIONINFOA;

typedef WIN_OSVERSIONINFOA   WIN_OSVERSIONINFO;
typedef WIN_POSVERSIONINFOA  WIN_POSVERSIONINFO;
typedef WIN_LPOSVERSIONINFOA WIN_LPOSVERSIONINFO;

static BOOL(WINAPI* WinGetVersionExA)(WIN_LPOSVERSIONINFOA);

static DWORD dwMaxNameSize     = MAX_PATH + 1;
static DWORD dwFilePermissions = GENERIC_READ | GENERIC_WRITE;

#if defined(__aarch64__) || defined(_M_ARM64) || defined(__ia64__) || defined(_M_IA64) || defined(__x86_64__) ||       \
    defined(__amd64) || defined(_M_AMD64) || defined(_M_X64)
#define SIZE_T_FORMAT "%llu"
#else
#define SIZE_T_FORMAT "%u"
#endif

#endif

#pragma clang diagnostic pop

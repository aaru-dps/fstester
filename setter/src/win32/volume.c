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

// ReSharper disable CppJoinDeclarationAndAssignment
// ReSharper disable CppDeprecatedEntity
#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win32.h"

#include "volume.h"

#include "../include/defs.h"
#include "../log.h"

extern DWORD oldVersion;

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    BOOL              ret;
    DWORD             error;
    LPSTR             lpVolumeNameBuffer;
    DWORD             dwMaximumComponentLength;
    DWORD             dwFileSystemFlags;
    LPSTR             lpFileSystemNameBuffer;
    LPSTR             lpRootPathName;
    const size_t      pathSize = strlen(path);
    DWORD             dwSectorsPerCluster;
    DWORD             dwBytesPerSector;
    DWORD             dwNumberOfFreeClusters;
    DWORD             dwTotalNumberOfClusters;
    WIN_OSVERSIONINFO verInfo;
    ULARGE_INTEGER    qwFreeBytesAvailableToCaller;
    ULARGE_INTEGER    qwTotalNumberOfBytes;
    ULARGE_INTEGER    qwTotalNumberOfFreeBytes;
    void*             func;
    HINSTANCE         kernel32;

    *clusterSize = 0;

    log_write("Volume information:\n");
    log_write("\tPath: %s\n", path);

    lpVolumeNameBuffer = malloc(dwMaxNameSize);

    if(lpVolumeNameBuffer == NULL)
    {
        log_write("Could not allocate memory.\n");
        return;
    }

    lpFileSystemNameBuffer = malloc(dwMaxNameSize);

    if(lpFileSystemNameBuffer == NULL)
    {
        log_write("Could not allocate memory.\n");
        free(lpVolumeNameBuffer);
        return;
    }

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        log_write("Could not allocate memory.\n");
        free(lpVolumeNameBuffer);
        free(lpFileSystemNameBuffer);
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = GetVolumeInformationA(lpRootPathName,
                                lpVolumeNameBuffer,
                                dwMaxNameSize,
                                NULL,
                                &dwMaximumComponentLength,
                                &dwFileSystemFlags,
                                lpFileSystemNameBuffer,
                                dwMaxNameSize);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu querying volume information.\n", error);
        free(lpVolumeNameBuffer);
        free(lpFileSystemNameBuffer);
        free(lpRootPathName);
        return;
    }

    log_write("\tFilesystem: %s\n", lpFileSystemNameBuffer);
    log_write("\tVolume name: %s\n", lpVolumeNameBuffer);
    log_write("\tMaximum component size: %lu\n", dwMaximumComponentLength);

    if(dwFileSystemFlags > 0)
    {
        log_write("\tFlags:\n");

        if(dwFileSystemFlags & (DWORD)FILE_CASE_PRESERVED_NAMES)
        {
            log_write("\t\tVolume preserves file name case.\n");
            dwFileSystemFlags -= FILE_CASE_PRESERVED_NAMES;
        }

        if(dwFileSystemFlags & (DWORD)FILE_CASE_SENSITIVE_SEARCH)
        {
            log_write("\t\tVolume supports case sensitiveness.\n");
            dwFileSystemFlags -= FILE_CASE_SENSITIVE_SEARCH;
        }

        if(dwFileSystemFlags & (DWORD)FILE_DAX_VOLUME)
        {
            log_write("\t\tDirect access volume.\n");
            dwFileSystemFlags -= FILE_DAX_VOLUME;
        }

        if(dwFileSystemFlags & (DWORD)FILE_FILE_COMPRESSION)
        {
            log_write("\t\tVolume supports per-file compression.\n");
            dwFileSystemFlags -= FILE_FILE_COMPRESSION;
        }

        if(dwFileSystemFlags & (DWORD)FILE_NAMED_STREAMS)
        {
            log_write("\t\tVolume supports Alternate Data Streams.\n");
            dwFileSystemFlags -= FILE_NAMED_STREAMS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_PERSISTENT_ACLS)
        {
            log_write("\t\tVolume supports persistent Access Control Lists.\n");
            dwFileSystemFlags -= FILE_PERSISTENT_ACLS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_READ_ONLY_VOLUME)
        {
            log_write("\t\tVolume is read-only.\n");
            dwFileSystemFlags -= FILE_READ_ONLY_VOLUME;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SEQUENTIAL_WRITE_ONCE)
        {
            log_write("\t\tVolume supports a single sequential write.\n");
            dwFileSystemFlags -= FILE_SEQUENTIAL_WRITE_ONCE;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_ENCRYPTION)
        {
            log_write("\t\tVolume supports per-file encryption.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_ENCRYPTION;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
        {
            log_write("\t\tVolume supports extended attributes.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_EXTENDED_ATTRIBUTES;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_HARD_LINKS)
        {
            log_write("\t\tVolume supports hard links.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_HARD_LINKS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_OBJECT_IDS)
        {
            log_write("\t\tVolume supports object IDs.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_OBJECT_IDS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_OPEN_BY_FILE_ID)
        {
            log_write("\t\tVolume can open files by ID.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_OPEN_BY_FILE_ID;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_REPARSE_POINTS)
        {
            log_write("\t\tVolume supports reparse points.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_REPARSE_POINTS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_SPARSE_FILES)
        {
            log_write("\t\tVolume supports sparse files.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_SPARSE_FILES;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_TRANSACTIONS)
        {
            log_write("\t\tVolume supports transactions.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_TRANSACTIONS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_USN_JOURNAL)
        {
            log_write("\t\tVolume has an USN journal.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_USN_JOURNAL;
        }

        if(dwFileSystemFlags & (DWORD)FILE_UNICODE_ON_DISK)
        {
            log_write("\t\tVolume stores filenames as Unicode.\n");
            dwFileSystemFlags -= FILE_UNICODE_ON_DISK;
        }

        if(dwFileSystemFlags & (DWORD)FILE_VOLUME_IS_COMPRESSED)
        {
            log_write("\t\tVolume is compressed.\n");
            dwFileSystemFlags -= FILE_VOLUME_IS_COMPRESSED;
        }

        if(dwFileSystemFlags & (DWORD)FILE_VOLUME_QUOTAS)
        {
            log_write("\t\tVolume supports user quotas.\n");
            dwFileSystemFlags -= FILE_VOLUME_QUOTAS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_RETURNS_CLEANUP_RESULT_INFO)
        {
            log_write("\t\tOn a clean operation, volume returns additional information.\n");
            dwFileSystemFlags -= FILE_RETURNS_CLEANUP_RESULT_INFO;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_POSIX_UNLINK_RENAME)
        {
            log_write("\t\tVolume supports POSIX-style delete and rename operations.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_POSIX_UNLINK_RENAME;
        }

        if(dwFileSystemFlags & (DWORD)FS_LFN_APIS)
        {
            log_write("\t\tVolume supports LFN API.\n");
            dwFileSystemFlags -= FS_LFN_APIS;
        }

        if(dwFileSystemFlags > 0) log_write("Unknown flags: 0x%08lx.\n", dwFileSystemFlags);
    }

    free(lpVolumeNameBuffer);
    free(lpFileSystemNameBuffer);

    ret = GetDiskFreeSpaceA(
        lpRootPathName, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu querying volume space.\n", error);
        free(lpRootPathName);
        return;
    }

    *clusterSize = dwSectorsPerCluster * dwBytesPerSector;
    log_write("\tBytes per sector: %lu\n", dwBytesPerSector);
    log_write("\tSectors per cluster: %lu (" SIZE_T_FORMAT " bytes)\n", dwSectorsPerCluster, *clusterSize);

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            log_write("Error %lu querying Windows version.\n", error);
            free(lpRootPathName);
            return;
        }
    }
    else if(oldVersion == 0)
        verInfo.dwPlatformId = VER_PLATFORM_WIN32_NT;

    if(verInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && verInfo.dwBuildNumber >= 1000 ||
       verInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && kernel32)
    {
        kernel32 = LoadLibraryA("kernel32.dll");

        if(kernel32)
        {
            func = GetProcAddress(kernel32, "GetDiskFreeSpaceExA");
            if(func) WinGetDiskFreeSpaceExA = func;
        }
    }

    if(WinGetDiskFreeSpaceExA)
    {
        ret = WinGetDiskFreeSpaceExA(
            lpRootPathName, &qwFreeBytesAvailableToCaller, &qwTotalNumberOfBytes, &qwTotalNumberOfFreeBytes);

        if(!ret)
        {
            error = GetLastError();
            log_write("Error %lu querying extended volume space.\n", error);
            free(lpRootPathName);
            return;
        }

        log_write("\tVolume size: %I64d bytes\n", qwTotalNumberOfBytes.QuadPart);
        log_write("\tVolume free: %I64d bytes\n", qwTotalNumberOfFreeBytes.QuadPart);
    }
    else
    {
        qwTotalNumberOfBytes.QuadPart     = dwTotalNumberOfClusters;
        qwTotalNumberOfFreeBytes.QuadPart = dwNumberOfFreeClusters;
        qwTotalNumberOfBytes.QuadPart *= *clusterSize;
        qwTotalNumberOfFreeBytes.QuadPart *= *clusterSize;

        log_write("\tClusters: %lu (%I64d bytes)\n", dwTotalNumberOfClusters, qwTotalNumberOfBytes.QuadPart);
        log_write("\tFree clusters: %lu (%I64d bytes)\n", dwNumberOfFreeClusters, qwTotalNumberOfFreeBytes.QuadPart);
    }

    free(lpRootPathName);

    if(func) FreeLibrary(kernel32);
}

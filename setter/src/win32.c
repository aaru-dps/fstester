/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : win32.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains 32-bit and 64-bit Windows code

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
#if defined(__WINDOWS__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(_WIN64) || defined(_WIN32) ||        \
    defined(__NT__)

#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win32.h"

#include "include/consts.h"
#include "include/defs.h"

static DWORD     dwMaxNameSize     = MAX_PATH + 1;
static DWORD     dwFilePermissions = GENERIC_READ | GENERIC_WRITE;
static DWORD     oldVersion;
static HINSTANCE kernel32;

void GetOsInfo()
{
    WIN_OSVERSIONINFO verInfo;
    BOOL              ret;
    DWORD             error;
    void*             func;
    kernel32 = LoadLibraryA("KERNEL32.DLL");

    memset(&verInfo, 0, sizeof(WIN_OSVERSIONINFO));

    if(!kernel32)
    {
        oldVersion = GetVersion();

        verInfo.dwMajorVersion = (oldVersion & 0xFF00) >> 8;
        verInfo.dwMinorVersion = oldVersion & 0xFF;
        oldVersion &= 0x80000000;

        if(oldVersion == 0)
            printf("\tRunning under Windows %lu.%lu using Win32s.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);
        else
            printf("\tRunning under Windows NT %lu.%lu.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);

        return;
    }

    func = GetProcAddress(kernel32, "GetVersionExA");

    if(!func)
    {
        oldVersion = GetVersion();

        verInfo.dwMajorVersion = (oldVersion & 0xFF00) >> 8;
        verInfo.dwMinorVersion = oldVersion & 0xFF;
        oldVersion &= 0x80000000;

        if(oldVersion == 0)
            printf("\tRunning under Windows %lu.%lu using Win32s.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);
        else
            printf("\tRunning under Windows NT %lu.%lu.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);

        return;
    }

    WinGetVersionExA = func;

    verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
    ret                         = WinGetVersionExA(&verInfo);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu querying Windows version.\n", error);
        return;
    }

    printf("OS information:\n");

    if(verInfo.dwPlatformId == VER_PLATFORM_WIN32s)
        printf("\tRunning under Windows %lu.%lu using Win32s.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);
    else if(verInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
        if(verInfo.dwMinorVersion == 10)
        {
            if(verInfo.dwBuildNumber == 2222) printf("\tRunning under Windows 98 SE");
            else
                printf("\tRunning under Windows 98");
        }
        else if(verInfo.dwMinorVersion == 90)
            printf("\tRunning under Windows Me");
        else if(verInfo.dwMinorVersion < 10)
            printf("\tRunning under Windows 95");
        else
            printf("\tRunning under Windows");

        if(verInfo.dwBuildNumber > 0)
        {
            if(strlen(verInfo.szCSDVersion) > 0)
                printf(" version %lu.%02lu.%lu%ss.\n",
                       verInfo.dwMajorVersion,
                       verInfo.dwMinorVersion,
                       verInfo.dwBuildNumber,
                       verInfo.szCSDVersion);
            else
                printf(
                    " version %lu.%02lu%lud.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion, verInfo.dwBuildNumber);
        }
        else
        {
            if(strlen(verInfo.szCSDVersion) > 0)
                printf(
                    " version %lu.%02lu %s.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion, verInfo.szCSDVersion);
            else
                printf(" version %lu.%02lu.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);
        }
    }
    else if(verInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        switch(verInfo.dwMajorVersion)
        {
            case 5:
                switch(verInfo.dwMinorVersion)
                {
                    case 0: printf("\tRunning under Windows 2000"); break;
                    case 1: printf("\tRunning under Windows XP"); break;
                    case 2: printf("\tRunning under Windows Server 2003"); break;
                    default: printf("\tRunning under Windows NT");
                }
                break;
            case 6:
                switch(verInfo.dwMinorVersion)
                {
                    case 0: printf("\tRunning under Windows Vista"); break;
                    case 1: printf("\tRunning under Windows 7"); break;
                    case 2: printf("\tRunning under Windows 8"); break;
                    case 3: printf("\tRunning under Windows 8.1"); break;
                    default: printf("\tRunning under Windows NT"); break;
                }
                break;
            case 10: printf("\tRunning under Windows 10"); break;
            default: printf("\tRunning under Windows NT"); break;
        }

        if(verInfo.dwMinorVersion < 10) verInfo.dwMinorVersion = verInfo.dwMinorVersion * 10;

        if(verInfo.dwBuildNumber > 0)
        {
            if(strlen(verInfo.szCSDVersion) > 0)
                printf(" version %lu.%02lu.%lu %s.\n",
                       verInfo.dwMajorVersion,
                       verInfo.dwMinorVersion,
                       verInfo.dwBuildNumber,
                       verInfo.szCSDVersion);
            else
                printf(
                    " version %lu.%02lu.%lu.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion, verInfo.dwBuildNumber);
        }
        else
        {
            if(strlen(verInfo.szCSDVersion) > 0)
                printf(
                    " version %lu.%02lu %s.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion, verInfo.szCSDVersion);
            else
                printf(" version %lu%02lud.\n", verInfo.dwMajorVersion, verInfo.dwMinorVersion);
        }
    }
}

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

    *clusterSize = 0;

    printf("Volume information:\n");
    printf("\tPath: %s\n", path);

    lpVolumeNameBuffer = malloc(dwMaxNameSize);

    if(lpVolumeNameBuffer == NULL)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    lpFileSystemNameBuffer = malloc(dwMaxNameSize);

    if(lpFileSystemNameBuffer == NULL)
    {
        printf("Could not allocate memory.\n");
        free(lpVolumeNameBuffer);
        return;
    }

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
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
        printf("Error %lu querying volume information.\n", error);
        free(lpVolumeNameBuffer);
        free(lpFileSystemNameBuffer);
        free(lpRootPathName);
        return;
    }

    printf("\tFilesystem: %s\n", lpFileSystemNameBuffer);
    printf("\tVolume name: %s\n", lpVolumeNameBuffer);
    printf("\tMaximum component size: %lu\n", dwMaximumComponentLength);

    if(dwFileSystemFlags > 0)
    {
        printf("\tFlags:\n");

        if(dwFileSystemFlags & (DWORD)FILE_CASE_PRESERVED_NAMES)
        {
            printf("\t\tVolume preserves file name case.\n");
            dwFileSystemFlags -= FILE_CASE_PRESERVED_NAMES;
        }

        if(dwFileSystemFlags & (DWORD)FILE_CASE_SENSITIVE_SEARCH)
        {
            printf("\t\tVolume supports case sensitiveness.\n");
            dwFileSystemFlags -= FILE_CASE_SENSITIVE_SEARCH;
        }

        if(dwFileSystemFlags & (DWORD)FILE_DAX_VOLUME)
        {
            printf("\t\tDirect access volume.\n");
            dwFileSystemFlags -= FILE_DAX_VOLUME;
        }

        if(dwFileSystemFlags & (DWORD)FILE_FILE_COMPRESSION)
        {
            printf("\t\tVolume supports per-file compression.\n");
            dwFileSystemFlags -= FILE_FILE_COMPRESSION;
        }

        if(dwFileSystemFlags & (DWORD)FILE_NAMED_STREAMS)
        {
            printf("\t\tVolume supports Alternate Data Streams.\n");
            dwFileSystemFlags -= FILE_NAMED_STREAMS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_PERSISTENT_ACLS)
        {
            printf("\t\tVolume supports persistent Access Control Lists.\n");
            dwFileSystemFlags -= FILE_PERSISTENT_ACLS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_READ_ONLY_VOLUME)
        {
            printf("\t\tVolume is read-only.\n");
            dwFileSystemFlags -= FILE_READ_ONLY_VOLUME;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SEQUENTIAL_WRITE_ONCE)
        {
            printf("\t\tVolume supports a single sequential write.\n");
            dwFileSystemFlags -= FILE_SEQUENTIAL_WRITE_ONCE;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_ENCRYPTION)
        {
            printf("\t\tVolume supports per-file encryption.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_ENCRYPTION;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
        {
            printf("\t\tVolume supports extended attributes.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_EXTENDED_ATTRIBUTES;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_HARD_LINKS)
        {
            printf("\t\tVolume supports hard links.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_HARD_LINKS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_OBJECT_IDS)
        {
            printf("\t\tVolume supports object IDs.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_OBJECT_IDS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_OPEN_BY_FILE_ID)
        {
            printf("\t\tVolume can open files by ID.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_OPEN_BY_FILE_ID;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_REPARSE_POINTS)
        {
            printf("\t\tVolume supports reparse points.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_REPARSE_POINTS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_SPARSE_FILES)
        {
            printf("\t\tVolume supports sparse files.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_SPARSE_FILES;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_TRANSACTIONS)
        {
            printf("\t\tVolume supports transactions.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_TRANSACTIONS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_USN_JOURNAL)
        {
            printf("\t\tVolume has an USN journal.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_USN_JOURNAL;
        }

        if(dwFileSystemFlags & (DWORD)FILE_UNICODE_ON_DISK)
        {
            printf("\t\tVolume stores filenames as Unicode.\n");
            dwFileSystemFlags -= FILE_UNICODE_ON_DISK;
        }

        if(dwFileSystemFlags & (DWORD)FILE_VOLUME_IS_COMPRESSED)
        {
            printf("\t\tVolume is compressed.\n");
            dwFileSystemFlags -= FILE_VOLUME_IS_COMPRESSED;
        }

        if(dwFileSystemFlags & (DWORD)FILE_VOLUME_QUOTAS)
        {
            printf("\t\tVolume supports user quotas.\n");
            dwFileSystemFlags -= FILE_VOLUME_QUOTAS;
        }

        if(dwFileSystemFlags & (DWORD)FILE_RETURNS_CLEANUP_RESULT_INFO)
        {
            printf("\t\tOn a clean operation, volume returns additional information.\n");
            dwFileSystemFlags -= FILE_RETURNS_CLEANUP_RESULT_INFO;
        }

        if(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_POSIX_UNLINK_RENAME)
        {
            printf("\t\tVolume supports POSIX-style delete and rename operations.\n");
            dwFileSystemFlags -= FILE_SUPPORTS_POSIX_UNLINK_RENAME;
        }

        if(dwFileSystemFlags & (DWORD)FS_LFN_APIS)
        {
            printf("\t\tVolume supports LFN API.\n");
            dwFileSystemFlags -= FS_LFN_APIS;
        }

        if(dwFileSystemFlags > 0) printf("Unknown flags: 0x%08lx.\n", dwFileSystemFlags);
    }

    free(lpVolumeNameBuffer);
    free(lpFileSystemNameBuffer);

    ret = GetDiskFreeSpaceA(
        lpRootPathName, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu querying volume space.\n", error);
        free(lpRootPathName);
        return;
    }

    *clusterSize = dwSectorsPerCluster * dwBytesPerSector;
    printf("\tBytes per sector: %lu\n", dwBytesPerSector);
    printf("\tSectors per cluster: %lu (%u bytes)\n", dwSectorsPerCluster, *clusterSize);

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            printf("Error %lu querying Windows version.\n", error);
            free(lpRootPathName);
            return;
        }
    }
    else if(oldVersion == 0)
        verInfo.dwPlatformId = VER_PLATFORM_WIN32_NT;

    if(verInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && verInfo.dwBuildNumber >= 1000 ||
       verInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && kernel32)
    {
        func = GetProcAddress(kernel32, "GetDiskFreeSpaceExA");
        if(func) WinGetDiskFreeSpaceExA = func;
    }

    if(WinGetDiskFreeSpaceExA)
    {
        ret = WinGetDiskFreeSpaceExA(
            lpRootPathName, &qwFreeBytesAvailableToCaller, &qwTotalNumberOfBytes, &qwTotalNumberOfFreeBytes);

        if(!ret)
        {
            error = GetLastError();
            printf("Error %lu querying extended volume space.\n", error);
            free(lpRootPathName);
            return;
        }

        printf("\tVolume size: %I64d bytes\n", qwTotalNumberOfBytes.QuadPart);
        printf("\tVolume free: %I64d bytes\n", qwTotalNumberOfFreeBytes.QuadPart);
    }
    else
    {
        qwTotalNumberOfBytes.QuadPart     = dwTotalNumberOfClusters;
        qwTotalNumberOfFreeBytes.QuadPart = dwNumberOfFreeClusters;
        qwTotalNumberOfBytes.QuadPart *= *clusterSize;
        qwTotalNumberOfFreeBytes.QuadPart *= *clusterSize;

        printf("\tClusters: %lu (%I64d bytes)\n", dwTotalNumberOfClusters, qwTotalNumberOfBytes.QuadPart);
        printf("\tFree clusters: %lu (%I64d bytes)\n", dwNumberOfFreeClusters, qwTotalNumberOfFreeBytes.QuadPart);
    }

    free(lpRootPathName);
}

void FileAttributes(const char* path)
{
    BOOL              ret;
    DWORD             error;
    LPSTR             lpRootPathName;
    size_t            pathSize = strlen(path);
    HANDLE            h;
    DWORD             dwNumberOfBytesWritten;
    DWORD             rc, wRc, cRc, aRc, eRc;
    WIN_OSVERSIONINFO verInfo;
    DWORD             defaultCompression = COMPRESSION_FORMAT_DEFAULT;
    void*             func;
    HMODULE           advapi32;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("ATTRS", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("ATTRS");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating attributes files.\n");

    h   = CreateFileA("NONE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)noAttributeText, strlen(noAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with no attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "NONE", rc, wRc, cRc);

    h   = CreateFileA("ARCHIVE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with archived attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "ARCHIVE", rc, wRc, cRc);

    h   = CreateFileA("HIDDEN", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with hidden attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "HIDDEN", rc, wRc, cRc);

    h   = CreateFileA("OFFLINE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_OFFLINE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "OFFLINE", rc, wRc, cRc);

    h   = CreateFileA("READONLY", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tFile with read-only attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "READONLY", rc, wRc, cRc);

    h   = CreateFileA("SYSTEM", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "SYSTEM", rc, wRc, cRc);

    h   = CreateFileA("TEMPORAR", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "TEMPORAR", rc, wRc, cRc);

    h = CreateFileA(
        "HA", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with hidden and archived attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "HA",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "OA", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_ARCHIVE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with archived attribute is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "OA",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "RA", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with read-only and archived attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "RA",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "SA", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system and archived attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "SA",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "TA", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file with archived attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TA",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "OH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_HIDDEN, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with hidden attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "OH",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "RH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system and read-only attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "RH",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "SH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system and hidden attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "SH",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "TH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_HIDDEN, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tTemporary file with hidden attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "TH", rc, wRc, cRc);

    h = CreateFileA(
        "RO", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_OFFLINE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with read-only attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "RO",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "SO", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_OFFLINE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "SO",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "TO", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_OFFLINE, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TO",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "SR", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system and read-only attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "SR",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "TR", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_READONLY, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file with read-only attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TR",
           rc,
           wRc,
           cRc);

    h = CreateFileA(
        "ST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_TEMPORARY, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tTemporary file with system attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "ST", rc, wRc, cRc);

    h   = CreateFileA("OAH",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tFile with archive and hidden attributes that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc "
        "= %d\n",
        "OAH",
        rc,
        wRc,
        cRc);

    h   = CreateFileA("RAH",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with read-only, hidden and archive attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "RAH",
           rc,
           wRc,
           cRc);

    h   = CreateFileA("SAH",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with system, archive and hidden attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "SAH",
           rc,
           wRc,
           cRc);

    h   = CreateFileA("TAH",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file with archive and hidden attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TAH",
           rc,
           wRc,
           cRc);

    h   = CreateFileA("RAO",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_OFFLINE,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tFile with read-only and archive attributes that is available offline: name = \"%s\", rc = %lu, wRc = %lu, "
        "cRc = %lu\n",
        "RAO",
        rc,
        wRc,
        cRc);

    h   = CreateFileA("SAO",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_OFFLINE,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tFile with system and archive attributes that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc "
        "= %d\n",
        "SAO",
        rc,
        wRc,
        cRc);

    h   = CreateFileA("TAO",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_OFFLINE,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tTemporary file with archive attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
        "%d\n",
        "TAO",
        rc,
        wRc,
        cRc);

    h   = CreateFileA("OAR",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf(
        "\tFile with read-only and archive attributes that is available offline: name = \"%s\", rc = %lu, wRc = %lu, "
        "cRc = %lu\n",
        "OAR",
        rc,
        wRc,
        cRc);

    h   = CreateFileA("TAR",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file with archive and read-only attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TAR",
           rc,
           wRc,
           cRc);

    h   = CreateFileA("TAS",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_SYSTEM,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tTemporary file with archive and system attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TAS",
           rc,
           wRc,
           cRc);

    h   = CreateFileA("AHORST",
                    dwFilePermissions,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_READONLY |
                        FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_TEMPORARY,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)systemAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with all attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "AHORST", rc, wRc, cRc);

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            printf("Error %lu querying Windows version.\n", error);
            free(lpRootPathName);
            return;
        }
    }
    else if(oldVersion == 0)
        verInfo.dwPlatformId = VER_PLATFORM_WIN32_NT;

    if(verInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        h   = CreateFileA("COMPRESS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        rc  = 0;
        wRc = 0;
        cRc = 0;
        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            ret = WriteFile(
                h, (LPCVOID)compressedAttributeText, strlen(compressedAttributeText), &dwNumberOfBytesWritten, NULL);
            if(!ret) wRc = GetLastError();

            ret = DeviceIoControl(
                h, FSCTL_SET_COMPRESSION, &defaultCompression, sizeof(DWORD), NULL, 0, &dwNumberOfBytesWritten, NULL);

            if(!ret) { rc = GetLastError(); }

            ret = CloseHandle(h);
            if(!ret) cRc = GetLastError();
        }
        printf("\tFile is compressed: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "COMPRESS", rc, wRc, cRc);
    }

    advapi32 = LoadLibraryA("ADVAPI32.DLL");
    if(!advapi32) return;

    func = GetProcAddress(advapi32, "EncryptFileA");

    if(!func) return;

    WinNtEncryptFileA = func;

    h   = CreateFileA("ENCRYPT", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;

    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("ENCRYPT");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("ENCRYPT", FILE_ATTRIBUTE_NORMAL);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = %lu\n",
           "ENCRYPT",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("EA", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("EA");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("EA", FILE_ATTRIBUTE_ARCHIVE);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file with archived attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = "
           "%lu\n",
           "EA",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);
    h   = CreateFileA("HE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("HE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("HE", FILE_ATTRIBUTE_HIDDEN);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with hidden attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = %lu\n",
        "HE",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("OE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("OE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("OE", FILE_ATTRIBUTE_OFFLINE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = %lu\n",
        "OE",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("RE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("RE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("RE", FILE_ATTRIBUTE_READONLY);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file with read-only attribute: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = "
           "%lu\n",
           "RE",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("TE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("TE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("TE", FILE_ATTRIBUTE_TEMPORARY);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted temporary file: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = %lu\n",
           "TE",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("HAE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("HAE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("HAE", FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file with hidden and archive attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = "
           "%lu, "
           "eRc = %lu\n",
           "HAE",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("OAE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("OAE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("OAE", FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_ARCHIVE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with archive attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
        "%d, aRc = %lu, eRc = %lu\n",
        "OAE",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("RAE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("RAE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("RAE", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with archive and read-only attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = "
        "%d, eRc = %lu\n",
        "RAE",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("TAE", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("TAE");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("TAE", FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with archive attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
        "%d, aRc = %lu, eRc = %lu\n",
        "TAE",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("EAO", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)encryptedAttributeText, strlen(systemAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("EAO");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("EAO", FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_OFFLINE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with archive attribute that is available offline: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
        "%d, aRc = %lu, eRc = %lu\n",
        "EAO",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("EAR", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("EAR");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("EAR", FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with archive and read-only attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = "
        "%d, eRc = %lu\n",
        "EAR",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("OAEH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("OAEH");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("OAEH", FILE_ATTRIBUTE_OFFLINE | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted file with archive and hidden attributes that is available offline: name = \"%s\", rc = %lu, wRc "
        "= %d, cRc = %lu, aRc = %lu, eRc = %lu\n",
        "OAEH",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("RAEH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("RAEH");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("RAEH", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file with read-only, archive and hidden attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
           "%d, aRc = %lu, eRc = %lu\n",
           "RAEH",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("TAEH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("TAEH");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("TAEH", FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted temporary file with hidden and archive attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, "
        "aRc = %lu, eRc = %lu\n",
        "TAEH",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("RAEO", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("RAEO");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("RAEO", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_OFFLINE);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file with read-only and archive attributes that is available offline: name = \"%s\", rc = %lu, "
           "wRc = %lu, cRc = %lu, aRc = %lu, eRc = %lu\n",
           "RAEO",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("TAEO", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("TAEO");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("TAEO", FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_OFFLINE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted temporary file with archive attribute that is available offline: name = \"%s\", rc = %lu, wRc = "
        "%d, cRc = %lu, aRc = %lu, eRc = %lu\n",
        "TAEO",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("TAER", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("TAER");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA("TAER", FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted temporary file with archive and read-only attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
        "%d, aRc = %lu, eRc = %lu\n",
        "TAER",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    h   = CreateFileA("RAEH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret =
            WriteFile(h, (LPCVOID)readonlyAttributeText, strlen(readonlyAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("RAEH");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA(
            "RAEH", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_OFFLINE);
        if(!ret) aRc = GetLastError();
    }
    printf("\tEncrypted file with read-only, archive and hidden attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = "
           "%d, aRc = %lu, eRc = %lu\n",
           "RAEH",
           rc,
           wRc,
           cRc,
           aRc,
           eRc);

    h   = CreateFileA("TAEH", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    aRc = 0;
    eRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(
            h, (LPCVOID)temporaryAttributeText, strlen(temporaryAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret =
            WriteFile(h, (LPCVOID)archivedAttributeText, strlen(archivedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(
            h, (LPCVOID)encryptedAttributeText, strlen(encryptedAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)hiddenAttributeText, strlen(hiddenAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        ret = WriteFile(h, (LPCVOID)offlineAttributeText, strlen(offlineAttributeText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();

        ret = WinNtEncryptFileA("TAEH");
        if(!ret) eRc = GetLastError();

        ret = SetFileAttributesA(
            "TAEH", FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_OFFLINE);
        if(!ret) aRc = GetLastError();
    }
    printf(
        "\tEncrypted temporary file with archive and hidden attributes: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, "
        "aRc = %lu, eRc = %lu\n",
        "TAEH",
        rc,
        wRc,
        cRc,
        aRc,
        eRc);

    FreeLibrary(advapi32);
}

void FilePermissions(const char* path)
{ /* Do nothing, not supported by target operating system */
}

void ExtendedAttributes(const char* path)
{
    BOOL                      ret;
    DWORD                     error;
    WIN_OSVERSIONINFO         verInfo;
    HMODULE                   ntdll;
    void*                     func;
    DWORD                     dwNumberOfBytesWritten;
    DWORD                     rc, wRc, cRc, rRc;
    char                      message[300];
    IO_STATUS_BLOCK           eaStatus;
    HANDLE                    h;
    LPSTR                     lpRootPathName;
    size_t                    pathSize = strlen(path);
    PFILE_FULL_EA_INFORMATION eaData;
    int                       i;
    BOOL                      cmp;

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            printf("Error %lu querying Windows version.\n", error);
            return;
        }
    }
    else if(oldVersion == 0)
        verInfo.dwPlatformId = VER_PLATFORM_WIN32_NT;

    if(verInfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        // Not supported on Windows 9x
        return;
    }

    ntdll = LoadLibraryA("ntdll.dll");

    if(ntdll == NULL)
    {
        error = GetLastError();
        printf("Error %lu loading NTDLL.DLL.\n", error);
        return;
    }

    func = GetProcAddress(ntdll, "NtSetEaFile");

    if(func == NULL)
    {
        error = GetLastError();
        printf("Error %lu finding NtSetEaFile.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    NtSetEaFile = func;

    func = GetProcAddress(ntdll, "NtQueryEaFile");

    if(func == NULL)
    {
        error = GetLastError();
        printf("Error %lu finding NtQueryEaFile.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    NtQueryEaFile = func;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        FreeLibrary(ntdll);
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    ret = CreateDirectoryA("XATTRS", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    ret = SetCurrentDirectoryA("XATTRS");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    printf("Creating files with extended attributes.\n");

    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    cmp = TRUE;
    h   = CreateFileA("COMMENTS",
                    dwFilePermissions,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, "This files has an optional .COMMENTS EA\n");
        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        else
        {
            eaData = malloc(sizeof(CommentsEA));
            memcpy(eaData, &CommentsEA, sizeof(CommentsEA));

            rc = NtSetEaFile(h, &eaStatus, eaData, sizeof(CommentsEA));

            free(eaData);

            if(!rc)
            {
                eaData = malloc(sizeof(CommentsEA));
                memset(eaData, 0, sizeof(CommentsEA));
                rRc = NtQueryEaFile(h, &eaStatus, eaData, sizeof(CommentsEA), TRUE, NULL, 0, NULL, FALSE);

                for(i = 0; i < sizeof(CommentsEA); i++)
                {
                    if(((unsigned char*)eaData)[i] != CommentsEA[i])
                    {
                        cmp = FALSE;
                        break;
                    }
                }

                free(eaData);
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }

    printf("\tFile with comments = \"%s\", rc = 0x%08lx, wRc = %lu, cRc = %lu, rRc = %lu, cmp = %d\n",
           "COMMENTS",
           rc,
           wRc,
           cRc,
           rRc,
           cmp);

    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    cmp = TRUE;
    h   = CreateFileA("COMMENTS.CRT",
                    dwFilePermissions,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, "This files has a critical .COMMENTS EA\n");
        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        else
        {
            eaData = malloc(sizeof(CommentsEACritical));
            memcpy(eaData, &CommentsEACritical, sizeof(CommentsEACritical));

            rc = NtSetEaFile(h, &eaStatus, eaData, sizeof(CommentsEACritical));

            free(eaData);

            if(!rc)
            {
                eaData = malloc(sizeof(CommentsEACritical));
                memset(eaData, 0, sizeof(CommentsEACritical));
                rRc = NtQueryEaFile(h, &eaStatus, eaData, sizeof(CommentsEACritical), TRUE, NULL, 0, NULL, FALSE);

                for(i = 0; i < sizeof(CommentsEACritical); i++)
                {
                    if(((unsigned char*)eaData)[i] != CommentsEACritical[i])
                    {
                        cmp = FALSE;
                        break;
                    }
                }

                free(eaData);
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }

    printf("\tFile with comments = \"%s\", rc = 0x%08lx, wRc = %lu, cRc = %lu, rRc = %lu, cmp = %d\n",
           "COMMENTS.CRT",
           rc,
           wRc,
           cRc,
           rRc,
           cmp);

    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    cmp = TRUE;
    h   = CreateFileA("ICON",
                    dwFilePermissions,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, "This files has an optional .ICON EA\n");
        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        else
        {
            eaData = malloc(sizeof(IconEA));
            memcpy(eaData, &IconEA, sizeof(IconEA));

            rc = NtSetEaFile(h, &eaStatus, eaData, sizeof(IconEA));

            free(eaData);

            if(!rc)
            {
                eaData = malloc(sizeof(IconEA));
                memset(eaData, 0, sizeof(IconEA));
                rRc = NtQueryEaFile(h, &eaStatus, eaData, sizeof(IconEA), TRUE, NULL, 0, NULL, FALSE);

                for(i = 0; i < sizeof(IconEA); i++)
                {
                    if(((unsigned char*)eaData)[i] != IconEA[i])
                    {
                        cmp = FALSE;
                        break;
                    }
                }

                free(eaData);
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }

    printf("\tFile with icon = \"%s\", rc = 0x%08lx, wRc = %lu, cRc = %lu, rRc = %lu, cmp = %d\n",
           "ICON",
           rc,
           wRc,
           cRc,
           rRc,
           cmp);

    FreeLibrary(ntdll);
}

void ResourceFork(const char* path)
{
    BOOL              ret;
    DWORD             error;
    LPSTR             lpRootPathName;
    size_t            pathSize = strlen(path);
    HANDLE            h;
    DWORD             dwNumberOfBytesWritten;
    DWORD             rc, wRc, cRc;
    WIN_OSVERSIONINFO verInfo;
    unsigned int      maxLoop, i;

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            printf("Error %lu querying Windows version.\n", error);
            return;
        }
    }
    else if(oldVersion == 0)
        verInfo.dwPlatformId = VER_PLATFORM_WIN32_NT;

    if(verInfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        // Not supported on Windows 9x
        return;
    }

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("ADS", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("ADS");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating alternate data streams.\n");

    h   = CreateFileA("TINY:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)tinyAdsText, strlen(tinyAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with tiny alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TINY:ADS",
           rc,
           wRc,
           cRc);

    maxLoop = (4095 - strlen(smallAdsText)) / strlen(smallAdsRepeatText);
    h       = CreateFileA("SMALL:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc      = 0;
    wRc     = 0;
    cRc     = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)smallAdsText, strlen(smallAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        for(i = 0; i < maxLoop; i++)
        {
            ret = WriteFile(h, (LPCVOID)smallAdsRepeatText, strlen(smallAdsRepeatText), &dwNumberOfBytesWritten, NULL);
            if(!ret)
            {
                wRc = GetLastError();
                break;
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with small alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "SMALL:ADS",
           rc,
           wRc,
           cRc);

    maxLoop = (65535 - strlen(mediumAdsText)) / strlen(mediumAdsRepeatText);
    h       = CreateFileA("MEDIUM:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc      = 0;
    wRc     = 0;
    cRc     = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)mediumAdsText, strlen(mediumAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        for(i = 0; i < maxLoop; i++)
        {
            ret =
                WriteFile(h, (LPCVOID)mediumAdsRepeatText, strlen(mediumAdsRepeatText), &dwNumberOfBytesWritten, NULL);
            if(!ret)
            {
                wRc = GetLastError();
                break;
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with medium alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "MEDIUM:ADS",
           rc,
           wRc,
           cRc);

    maxLoop = (67584 - strlen(bigAdsText)) / strlen(bigAdsRepeatText);
    h       = CreateFileA("BIG:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc      = 0;
    wRc     = 0;
    cRc     = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)bigAdsText, strlen(bigAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        for(i = 0; i < maxLoop; i++)
        {
            ret = WriteFile(h, (LPCVOID)bigAdsRepeatText, strlen(bigAdsRepeatText), &dwNumberOfBytesWritten, NULL);
            if(!ret)
            {
                wRc = GetLastError();
                break;
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with big alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "BIG:ADS",
           rc,
           wRc,
           cRc);

    h   = CreateFileA("MULTIPLE:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)tinyAdsText, strlen(tinyAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with tiny alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "MULTIPLE:ADS",
           rc,
           wRc,
           cRc);

    maxLoop = (4095 - strlen(smallAdsText)) / strlen(smallAdsRepeatText);
    h       = CreateFileA("MULTIPLE:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc      = 0;
    wRc     = 0;
    cRc     = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)smallAdsText, strlen(smallAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        for(i = 0; i < maxLoop; i++)
        {
            ret = WriteFile(h, (LPCVOID)smallAdsRepeatText, strlen(smallAdsRepeatText), &dwNumberOfBytesWritten, NULL);

            if(!ret)
            {
                wRc = GetLastError();
                break;
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with small alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "MULTIPLE:ADS",
           rc,
           wRc,
           cRc);

    maxLoop = (65535 - strlen(mediumAdsText)) / strlen(mediumAdsRepeatText);
    h       = CreateFileA("MULTIPLE:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc      = 0;
    wRc     = 0;
    cRc     = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)mediumAdsText, strlen(mediumAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        for(i = 0; i < maxLoop; i++)
        {
            ret =
                WriteFile(h, (LPCVOID)mediumAdsRepeatText, strlen(mediumAdsRepeatText), &dwNumberOfBytesWritten, NULL);

            if(!ret)
            {
                wRc = GetLastError();
                break;
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with medium alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "MULTIPLE:ADS",
           rc,
           wRc,
           cRc);

    maxLoop = (67584 - strlen(bigAdsText)) / strlen(bigAdsRepeatText);
    h       = CreateFileA("MULTIPLE:ADS", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc      = 0;
    wRc     = 0;
    cRc     = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        ret = WriteFile(h, (LPCVOID)bigAdsText, strlen(bigAdsText), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        for(i = 0; i < maxLoop; i++)
        {
            ret = WriteFile(h, (LPCVOID)bigAdsRepeatText, strlen(bigAdsRepeatText), &dwNumberOfBytesWritten, NULL);

            if(!ret)
            {
                wRc = GetLastError();
                break;
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile with medium alternate data stream: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
           "MULTIPLE:ADS",
           rc,
           wRc,
           cRc);
}

void Filenames(const char* path)
{
    BOOL         ret;
    DWORD        error;
    LPSTR        lpRootPathName;
    const size_t pathSize = strlen(path);
    HANDLE       h;
    DWORD        dwNumberOfBytesWritten;
    DWORD        rc, wRc, cRc;
    char         message[300];
    int          pos = 0;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("FILENAME", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("FILENAME");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        h   = CreateFileA(filenames[pos], dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        rc  = 0;
        wRc = 0;
        cRc = 0;

        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            memset(message, 0, 300);
            sprintf(message, FILENAME_FORMAT, filenames[pos]);

            ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
            if(!ret) wRc = GetLastError();

            ret = CloseHandle(h);
            if(!ret) cRc = GetLastError();
        }

        printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", filenames[pos], rc, wRc, cRc);
    }
}

void Timestamps(const char* path)
{
    char     message[300];
    BOOL     ret;
    DWORD    error;
    LPSTR    lpRootPathName;
    size_t   pathSize = strlen(path);
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    HANDLE   h;
    DWORD    rc, wRc, cRc, tRc;
    DWORD    dwNumberOfBytesWritten;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("TIMES", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("TIMES");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating timestamped files.\n");

    h   = CreateFileA("MAXCTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, MAXDATETIME, "creation");
        ftCreationTime.dwHighDateTime = MAXTIMESTAMP;
        ftCreationTime.dwLowDateTime  = MAXTIMESTAMP;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, &ftCreationTime, NULL, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "MAXCTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("MAXATIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, MAXDATETIME, "access");
        ftLastAccessTime.dwHighDateTime = MAXTIMESTAMP;
        ftLastAccessTime.dwLowDateTime  = MAXTIMESTAMP;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, &ftLastAccessTime, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "MAXATIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("MAXMTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, MAXDATETIME, "modification");
        ftLastWriteTime.dwHighDateTime = MAXTIMESTAMP;
        ftLastWriteTime.dwLowDateTime  = MAXTIMESTAMP;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, NULL, &ftLastWriteTime);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "MAXMTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("MINCTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, MINDATETIME, "creation");
        ftCreationTime.dwHighDateTime = MINTIMESTAMP;
        ftCreationTime.dwLowDateTime  = MINTIMESTAMP;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, &ftCreationTime, NULL, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "MINCTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("MINATIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, MINDATETIME, "access");
        ftLastAccessTime.dwHighDateTime = MINTIMESTAMP;
        ftLastAccessTime.dwLowDateTime  = MINTIMESTAMP;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, &ftLastAccessTime, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "MINATIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("MINMTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, MINDATETIME, "modification");
        ftLastWriteTime.dwHighDateTime = MINTIMESTAMP;
        ftLastWriteTime.dwLowDateTime  = MINTIMESTAMP;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, NULL, &ftLastWriteTime);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "MINMTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("Y1KCTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, Y1KDATETIME, "creation");
        ftCreationTime.dwHighDateTime = TIMESTAMP_HI;
        ftCreationTime.dwLowDateTime  = Y1KTIMESTAMP_LO;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, &ftCreationTime, NULL, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "Y1KCTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("Y1KATIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, Y1KDATETIME, "access");
        ftLastAccessTime.dwHighDateTime = TIMESTAMP_HI;
        ftLastAccessTime.dwLowDateTime  = Y1KTIMESTAMP_LO;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, &ftLastAccessTime, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "Y1KATIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("Y1KMTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, Y1KDATETIME, "modification");
        ftLastWriteTime.dwHighDateTime = TIMESTAMP_HI;
        ftLastWriteTime.dwLowDateTime  = Y1KTIMESTAMP_LO;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, NULL, &ftLastWriteTime);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "Y1KMTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("Y2KCTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, Y2KDATETIME, "creation");
        ftCreationTime.dwHighDateTime = TIMESTAMP_HI;
        ftCreationTime.dwLowDateTime  = Y2KTIMESTAMP_LO;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, &ftCreationTime, NULL, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "Y2KCTIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("Y2KATIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, Y2KDATETIME, "access");
        ftLastAccessTime.dwHighDateTime = TIMESTAMP_HI;
        ftLastAccessTime.dwLowDateTime  = Y2KTIMESTAMP_LO;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, &ftLastAccessTime, NULL);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "Y2KATIME", rc, wRc, cRc, tRc);

    h   = CreateFileA("Y2KMTIME", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, DATETIME_FORMAT, Y1KDATETIME, "modification");
        ftLastWriteTime.dwHighDateTime = TIMESTAMP_HI;
        ftLastWriteTime.dwLowDateTime  = Y2KTIMESTAMP_LO;

        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = SetFileTime(h, NULL, NULL, &ftLastWriteTime);
        if(!ret) tRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }
    printf("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n", "Y2KMTIME", rc, wRc, cRc, tRc);
}

void DirectoryDepth(const char* path)
{
    BOOL         ret;
    DWORD        error;
    LPSTR        lpRootPathName;
    const size_t pathSize = strlen(path);
    char         filename[9];
    long         pos = 2;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("DEPTH", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("DEPTH");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating deepest directory tree.\n");

    while(ret)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08ld", pos);
        ret = CreateDirectoryA(filename, NULL);

        if(ret) ret = SetCurrentDirectoryA(filename);

        pos++;
    }

    printf("\tCreated %ld levels of directory hierarchy\n", pos);
}

void Fragmentation(const char* path, size_t clusterSize)
{
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    size_t         i;
    BOOL           ret;
    DWORD          error;
    LPSTR          lpRootPathName;
    const size_t   pathSize = strlen(path);
    HANDLE         h;
    DWORD          rc, wRc, cRc, tRc;
    DWORD          dwNumberOfBytesWritten;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("FRAGS", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("FRAGS");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    h   = CreateFileA("HALFCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, halfCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    h   = CreateFileA("QUARCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, quarterCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf(
        "\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    h   = CreateFileA("TWOCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, twoCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("TRQTCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, threeQuartersCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n",
           "TRQTCLST",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = CreateFileA("TWTQCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, twoAndThreeQuartCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n",
           "TWTQCLST",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);

    h   = CreateFileA("TWO1", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, twoCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n", "TWO1", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("TWO2", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, twoCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n", "TWO2", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("TWO3", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, twoCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tDeleting \"TWO2\".\n");
    ret = DeleteFileA("TWO2");
    if(!ret) { rc = GetLastError(); }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n", "TWO3", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("FRAGTHRQ", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, threeQuartersCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tDeleting \"TWO1\".\n");
    ret = DeleteFileA("TWO1");
    if(!ret) { rc = GetLastError(); }
    printf("\tDeleting \"TWO3\".\n");
    ret = DeleteFileA("TWO3");
    if(!ret) { rc = GetLastError(); }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n",
           "FRAGTHRQ",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = CreateFileA("FRAGSIXQ", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, twoAndThreeQuartCluster, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu\n",
           "FRAGSIXQ",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);
}

void Sparse(const char* path)
{
    BOOL                             ret;
    DWORD                            error;
    LPSTR                            lpVolumeNameBuffer;
    DWORD                            dwMaximumComponentLength;
    DWORD                            dwFileSystemFlags;
    LPSTR                            lpFileSystemNameBuffer;
    LPSTR                            lpRootPathName;
    size_t                           pathSize = strlen(path);
    DWORD                            rc, wRc, cRc, sRc, zRc;
    WINNT_FILE_ZERO_DATA_INFORMATION zeroData;
    HANDLE                           h;
    unsigned char*                   buffer;
    int                              i;
    DWORD                            dwNumberOfBytesWritten;

    lpVolumeNameBuffer = malloc(dwMaxNameSize);

    if(lpVolumeNameBuffer == NULL)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    lpFileSystemNameBuffer = malloc(dwMaxNameSize);

    if(lpFileSystemNameBuffer == NULL)
    {
        printf("Could not allocate memory.\n");
        free(lpVolumeNameBuffer);
        return;
    }

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
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
        printf("Error %lu querying volume information.\n", error);
        free(lpVolumeNameBuffer);
        free(lpFileSystemNameBuffer);
        free(lpRootPathName);
        return;
    }

    free(lpVolumeNameBuffer);
    free(lpFileSystemNameBuffer);

    if(!(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_SPARSE_FILES))
    {
        free(lpRootPathName);
        return;
    }

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("SPARSE", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("SPARSE");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    free(lpRootPathName);

    printf("Creating sparse files.\n");

    h   = CreateFileA("SMALL", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    sRc = 0;
    zRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(4096 * 3);
        memset(buffer, 0, 4096 * 3);

        for(i = 0; i < 4096 * 3; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, 4096 * 3, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = DeviceIoControl(h, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
        if(!ret)
        {
            sRc = GetLastError();
            if(sRc == 1)
            {
                sRc = 0;
                ret = DeviceIoControl(h, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
                if(!ret) { sRc = GetLastError(); }
            }
        }

        if(sRc == 0)
        {
            zeroData.FileOffset.QuadPart      = 4096;
            zeroData.BeyondFinalZero.QuadPart = 8192;

            ret = DeviceIoControl(h,
                                  FSCTL_SET_ZERO_DATA,
                                  &zeroData,
                                  sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                  NULL,
                                  0,
                                  &dwNumberOfBytesWritten,
                                  NULL);
            if(!ret)
            {
                zRc = GetLastError();
                if(zRc == 1)
                {
                    zRc = 0;
                    ret = DeviceIoControl(h,
                                          FSCTL_SET_ZERO_DATA,
                                          &zeroData,
                                          sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                          NULL,
                                          0,
                                          &dwNumberOfBytesWritten,
                                          NULL);
                    if(!ret) { zRc = GetLastError(); }
                }
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu, sRc = %lu, zRc = %lu\n",
           "SMALL",
           4096 * 3,
           rc,
           wRc,
           cRc,
           sRc,
           zRc);

    h   = CreateFileA("BIG", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    sRc = 0;
    zRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(4096 * 30);
        memset(buffer, 0, 4096 * 30);

        for(i = 0; i < 4096 * 30; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, 4096 * 30, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = DeviceIoControl(h, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
        if(!ret)
        {
            sRc = GetLastError();
            if(sRc == 1)
            {
                sRc = 0;
                ret = DeviceIoControl(h, FSCTL_SET_SPARSE_OLD, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
                if(!ret) { sRc = GetLastError(); }
            }
        }

        if(sRc == 0)
        {
            zeroData.FileOffset.QuadPart      = 32768;
            zeroData.BeyondFinalZero.QuadPart = 81920;

            ret = DeviceIoControl(h,
                                  FSCTL_SET_ZERO_DATA,
                                  &zeroData,
                                  sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                  NULL,
                                  0,
                                  &dwNumberOfBytesWritten,
                                  NULL);
            if(!ret)
            {
                zRc = GetLastError();
                if(zRc == 1)
                {
                    zRc = 0;
                    ret = DeviceIoControl(h,
                                          FSCTL_SET_ZERO_DATA_OLD,
                                          &zeroData,
                                          sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                          NULL,
                                          0,
                                          &dwNumberOfBytesWritten,
                                          NULL);
                    if(!ret) { zRc = GetLastError(); }
                }
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu, sRc = %lu, zRc = %lu\n",
           "BIG",
           4096 * 30,
           rc,
           wRc,
           cRc,
           sRc,
           zRc);
}

void Links(const char* path)
{
    BOOL              ret;
    DWORD             error;
    WIN_OSVERSIONINFO verInfo;
    void*             func;
    DWORD             dwNumberOfBytesWritten;
    DWORD             rc, wRc, cRc, lRc;
    char              message[300];
    HANDLE            h;
    LPSTR             lpRootPathName;
    size_t            pathSize = strlen(path);

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            printf("Error %lu querying Windows version.\n", error);
            return;
        }
    }
    else if(oldVersion == 0)
        verInfo.dwPlatformId = VER_PLATFORM_WIN32_NT;

    if(verInfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        // Not supported on Windows 9x
        return;
    }

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') { lpRootPathName[pathSize] = '\\'; }

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("LINKS", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("LINKS");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    kernel32 = LoadLibraryA("kernel32.dll");

    if(!kernel32)
    {
        error = GetLastError();
        printf("Error %lu loading KERNEL32.DLL.\n", error);
        return;
    }

    func = GetProcAddress(kernel32, "CreateSymbolicLinkA");

    if(!func)
    {
        error = GetLastError();
        printf("Error %lu finding CreateSymbolicLinkA.\n", error);
    }
    else
    {
        WinNtCreateSymbolicLinkA = func;
        printf("Creating symbolic links.\n");

        h   = CreateFileA("TARGET",
                        dwFilePermissions,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
        rc  = 0;
        wRc = 0;
        cRc = 0;
        lRc = 0;
        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            memset(message, 0, 300);
            sprintf(message, "This file is the target of a symbolic link.\n");
            ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
            if(!ret) wRc = GetLastError();

            ret = CloseHandle(h);
            if(!ret) cRc = GetLastError();

            ret = WinNtCreateSymbolicLinkA("SYMLINK", "TARGET", 0);
            if(!ret) lRc = GetLastError();
        }

        printf("\tSymbolic link, rc = 0x%08lx, wRc = %lu, cRc = %lu, lRc = %lu\n", rc, wRc, cRc, lRc);
    }

    func = GetProcAddress(kernel32, "CreateHardLinkA");

    if(!func)
    {
        error = GetLastError();
        printf("Error %lu finding CreateHardLinkA.\n", error);
    }
    else
    {
        WinNtCreateHardLinkA = func;
        printf("Creating hard links.\n");

        h   = CreateFileA("HARDTRGT",
                        dwFilePermissions,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
        rc  = 0;
        wRc = 0;
        cRc = 0;
        lRc = 0;
        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            memset(message, 0, 300);
            sprintf(message, "This file is part of a hard link.\n");
            ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
            if(!ret) wRc = GetLastError();

            ret = CloseHandle(h);
            if(!ret) cRc = GetLastError();

            ret = WinNtCreateHardLinkA("HARDLINK", "HARDTRGT", NULL);
            if(!ret) lRc = GetLastError();
        }

        printf("\tHard link, rc = 0x%08lx, wRc = %lu, cRc = %lu, lRc = %lu\n", rc, wRc, cRc, lRc);
    }
}

void MillionFiles(const char* path)
{
    char         filename[9];
    DWORD        pos = 0;
    HANDLE       h;
    BOOL         ret;
    DWORD        error;
    LPSTR        lpRootPathName;
    const size_t pathSize = strlen(path);

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("MILLION", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("MILLION");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating lots of files.\n");

    for(pos = 0; pos < 1000; pos++)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08lu", pos);

        h = CreateFileA(filename, dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(h == INVALID_HANDLE_VALUE) break;

        CloseHandle(h);
    }

    printf("\tCreated %lu files\n", pos);
}

void DeleteFiles(const char* path)
{
    char         filename[9];
    DWORD        pos = 0;
    HANDLE       h;
    BOOL         ret;
    DWORD        error;
    LPSTR        lpRootPathName;
    const size_t pathSize = strlen(path);

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("DELETED", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("DELETED");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    printf("Creating and deleting files.\n");

    for(pos = 0; pos < 64; pos++)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%lX", pos);
        h = CreateFileA(filename, dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(h == INVALID_HANDLE_VALUE) { break; }

        CloseHandle(h);
        DeleteFileA(filename);
    }
}

#endif

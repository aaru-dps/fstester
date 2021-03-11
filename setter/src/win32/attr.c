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

#include "attr.h"

#include "../include/consts.h"
#include "../include/defs.h"

static DWORD     dwMaxNameSize     = MAX_PATH + 1;
static DWORD     dwFilePermissions = GENERIC_READ | GENERIC_WRITE;
static DWORD     oldVersion;
static HINSTANCE kernel32;

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

#endif

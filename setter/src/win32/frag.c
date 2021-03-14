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
#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win32.h"
#include "../include/consts.h"
#include "../include/defs.h"

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
    DWORD          rc, wRc, cRc;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    h   = CreateFileA("QUARCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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
        "\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    h   = CreateFileA("TWOCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("TRQTCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TRQTCLST",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = CreateFileA("TWTQCLST", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n",
           "TWTQCLST",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);

    h   = CreateFileA("TWO1", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n", "TWO1", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("TWO2", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n", "TWO2", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("TWO3", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n", "TWO3", twoCluster, rc, wRc, cRc);

    h   = CreateFileA("FRAGTHRQ", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n",
           "FRAGTHRQ",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = CreateFileA("FRAGSIXQ", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
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

    printf("\tFile name = \"%s\", size = "SIZE_T_FORMAT", rc = %lu, wRc = %lu, cRc = %lu\n",
           "FRAGSIXQ",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);
}

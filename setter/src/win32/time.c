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
#include "../include/consts.h"
#include "../include/defs.h"

static DWORD     dwMaxNameSize     = MAX_PATH + 1;
static DWORD     dwFilePermissions = GENERIC_READ | GENERIC_WRITE;
static DWORD     oldVersion;
static HINSTANCE kernel32;

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

#endif

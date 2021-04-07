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
#include "../include/defs.h"
#include "../log.h"
#include "timew32.h"

void Timestamps(const char* path)
{
    char   message[300];
    BOOL   ret;
    DWORD  error;
    LPSTR  lpRootPathName;
    size_t pathSize = strlen(path);
    HANDLE h;
    DWORD  rc, wRc, cRc, tRc;
    DWORD  dwNumberOfBytesWritten;
    int    i;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        log_write("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("TIMES", NULL);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("TIMES");

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu changing to working directory.\n", error);
        return;
    }

    log_write("Creating timestamped files.\n");

    for(i = 0; i < KNOWN_WIN32_TIMESTAMPS; i++)
    {
        h = CreateFileA(
            win32_timestamps[i].filename, dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        rc  = 0;
        wRc = 0;
        cRc = 0;
        tRc = 0;

        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            memset(message, 0, 300);
            sprintf(message, DATETIME_FORMAT, win32_timestamps[i].message, win32_timestamps[i].type);

            ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
            if(!ret) wRc = GetLastError();

            if(strcmp(win32_timestamps[i].type, "creation") == 0)
                ret = SetFileTime(h, &win32_timestamps[i].ftCreationTime, NULL, NULL);
            else if(strcmp(win32_timestamps[i].type, "access") == 0)
                ret = SetFileTime(h, NULL, &win32_timestamps[i].ftLastAccessTime, NULL);
            else if(strcmp(win32_timestamps[i].type, "modification") == 0)
                ret = SetFileTime(h, NULL, NULL, &win32_timestamps[i].ftLastWriteTime);
            else
                tRc = -1;

            if(!ret) tRc = GetLastError();

            ret = CloseHandle(h);
            if(!ret) cRc = GetLastError();
        }

        log_write("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, tRc = %lu\n",
                  win32_timestamps[i].filename,
                  rc,
                  wRc,
                  cRc,
                  tRc);
    }
}

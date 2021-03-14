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
#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"

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
    int          pos;

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

    ret = CreateDirectoryA("FILENAME", NULL);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("FILENAME");

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu changing to working directory.\n", error);
        return;
    }

    log_write("Creating files with different filenames.\n");

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

        log_write("\tFile name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", filenames[pos], rc, wRc, cRc);
    }
}

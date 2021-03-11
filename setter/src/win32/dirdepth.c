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
#include "../include/defs.h"

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

#endif

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

#include "rsrcfork.h"

#include "../include/consts.h"
#include "../include/defs.h"

static DWORD     dwMaxNameSize     = MAX_PATH + 1;
static DWORD     dwFilePermissions = GENERIC_READ | GENERIC_WRITE;
static DWORD     oldVersion;
static HINSTANCE kernel32;

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

#endif

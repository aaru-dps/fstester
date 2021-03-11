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
#include <string.h>

#include "win32.h"
#include "../include/defs.h"

DWORD oldVersion;

void GetOsInfo()
{
    WIN_OSVERSIONINFO verInfo;
    BOOL              ret;
    DWORD             error;
    void*             func;
    HINSTANCE         kernel32;
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

        FreeLibrary(kernel32);

        return;
    }

    WinGetVersionExA = func;

    verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
    ret                         = WinGetVersionExA(&verInfo);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu querying Windows version.\n", error);
        FreeLibrary(kernel32);
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

    FreeLibrary(kernel32);
}

#endif

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

#include "links.h"

#include "../include/defs.h"
#include "../log.h"

extern DWORD oldVersion;

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
    HINSTANCE         kernel32;

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            log_write("Error %lu querying Windows version.\n", error);
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
        log_write("Could not allocate memory.\n");
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') { lpRootPathName[pathSize] = '\\'; }

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("LINKS", NULL);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("LINKS");

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu changing to working directory.\n", error);
        return;
    }

    kernel32 = LoadLibraryA("kernel32.dll");

    if(!kernel32)
    {
        error = GetLastError();
        log_write("Error %lu loading KERNEL32.DLL.\n", error);
        return;
    }

    func = GetProcAddress(kernel32, "CreateSymbolicLinkA");

    if(!func)
    {
        error = GetLastError();
        log_write("Error %lu finding CreateSymbolicLinkA.\n", error);
    }
    else
    {
        WinNtCreateSymbolicLinkA = func;
        log_write("Creating symbolic links.\n");

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

        log_write("\tSymbolic link, rc = 0x%08lx, wRc = %lu, cRc = %lu, lRc = %lu\n", rc, wRc, cRc, lRc);
    }

    func = GetProcAddress(kernel32, "CreateHardLinkA");

    if(!func)
    {
        error = GetLastError();
        log_write("Error %lu finding CreateHardLinkA.\n", error);
    }
    else
    {
        WinNtCreateHardLinkA = func;
        log_write("Creating hard links.\n");

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

        log_write("\tHard link, rc = 0x%08lx, wRc = %lu, cRc = %lu, lRc = %lu\n", rc, wRc, cRc, lRc);
    }

    FreeLibrary(kernel32);
}

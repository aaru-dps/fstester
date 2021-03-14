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

#include "attr.h"

#include "../include/defs.h"
#include "../log.h"

extern DWORD oldVersion;

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
    int               i;

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

    ret = CreateDirectoryA("ATTRS", NULL);

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("ATTRS");

    if(!ret)
    {
        error = GetLastError();
        log_write("Error %lu changing to working directory.\n", error);
        return;
    }

    log_write("Creating attributes files.\n");

    for(i = 0; i < KNOWN_WIN32_ATTRS; i++)
    {
        h  = CreateFileA(win32_attrs[i].filename, dwFilePermissions, 0, NULL, CREATE_ALWAYS, win32_attrs[i].attr, NULL);
        rc = 0;
        wRc = 0;
        cRc = 0;

        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            ret = WriteFile(h,
                            (LPCVOID)win32_attrs[i].description,
                            strlen(win32_attrs[i].description),
                            &dwNumberOfBytesWritten,
                            NULL);
            if(!ret) wRc = GetLastError();

            ret = CloseHandle(h);

            if(!ret) cRc = GetLastError();
        }

        log_write("\t%s: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n",
                  win32_attrs[i].description,
                  win32_attrs[i].filename,
                  rc,
                  wRc,
                  cRc);
    }

    if(WinGetVersionExA)
    {
        verInfo.dwOSVersionInfoSize = sizeof(WIN_OSVERSIONINFO);
        ret                         = WinGetVersionExA(&verInfo);

        if(!ret)
        {
            error = GetLastError();
            log_write("Error %lu querying Windows version.\n", error);
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
        log_write("\tFile is compressed: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu\n", "COMPRESS", rc, wRc, cRc);
    }

    advapi32 = LoadLibraryA("ADVAPI32.DLL");
    if(!advapi32) return;

    func = GetProcAddress(advapi32, "EncryptFileA");

    if(!func) return;

    WinNtEncryptFileA = func;

    for(i = 0; i < KNOWN_WIN32_ATTRS; i++)
    {
        h = CreateFileA(
            encrypted_win32_attrs[i].filename, dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        rc  = 0;
        wRc = 0;
        cRc = 0;
        aRc = 0;
        eRc = 0;

        if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
        else
        {
            ret = WriteFile(h,
                            (LPCVOID)encrypted_win32_attrs[i].description,
                            strlen(encrypted_win32_attrs[i].description),
                            &dwNumberOfBytesWritten,
                            NULL);
            if(!ret) wRc = GetLastError();

            ret = CloseHandle(h);
            if(!ret) cRc = GetLastError();

            ret = WinNtEncryptFileA(encrypted_win32_attrs[i].filename);
            if(!ret) eRc = GetLastError();

            ret = SetFileAttributesA(encrypted_win32_attrs[i].filename, encrypted_win32_attrs[i].attr);
            if(!ret) aRc = GetLastError();
        }
        log_write("\t%s: name = \"%s\", rc = %lu, wRc = %lu, cRc = %lu, aRc = %lu, eRc = %lu\n",
                  encrypted_win32_attrs[i].description,
                  encrypted_win32_attrs[i].filename,
                  rc,
                  wRc,
                  cRc,
                  aRc,
                  eRc);
    }

    FreeLibrary(advapi32);
}

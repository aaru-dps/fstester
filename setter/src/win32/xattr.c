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

#include "xattr.h"

#include "../include/defs.h"

extern DWORD oldVersion;

void ExtendedAttributes(const char* path)
{
    BOOL                      ret;
    DWORD                     error;
    WIN_OSVERSIONINFO         verInfo;
    HMODULE                   ntdll;
    void*                     func;
    DWORD                     dwNumberOfBytesWritten;
    DWORD                     rc, wRc, cRc, rRc;
    char                      message[300];
    IO_STATUS_BLOCK           eaStatus;
    HANDLE                    h;
    LPSTR                     lpRootPathName;
    size_t                    pathSize = strlen(path);
    PFILE_FULL_EA_INFORMATION eaData;
    int                       i;
    BOOL                      cmp;

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

    ntdll = LoadLibraryA("ntdll.dll");

    if(ntdll == NULL)
    {
        error = GetLastError();
        printf("Error %lu loading NTDLL.DLL.\n", error);
        return;
    }

    func = GetProcAddress(ntdll, "NtSetEaFile");

    if(func == NULL)
    {
        error = GetLastError();
        printf("Error %lu finding NtSetEaFile.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    NtSetEaFile = func;

    func = GetProcAddress(ntdll, "NtQueryEaFile");

    if(func == NULL)
    {
        error = GetLastError();
        printf("Error %lu finding NtQueryEaFile.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    NtQueryEaFile = func;

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        FreeLibrary(ntdll);
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
        FreeLibrary(ntdll);
        return;
    }

    ret = CreateDirectoryA("XATTRS", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    ret = SetCurrentDirectoryA("XATTRS");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        FreeLibrary(ntdll);
        return;
    }

    printf("Creating files with extended attributes.\n");

    rRc = 0;
    cmp = TRUE;
    h   = CreateFileA("COMMENTS",
                    dwFilePermissions,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, "This files has an optional .COMMENTS EA\n");
        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        else
        {
            eaData = malloc(sizeof(CommentsEA));
            memcpy(eaData, &CommentsEA, sizeof(CommentsEA));

            rc = NtSetEaFile(h, &eaStatus, eaData, sizeof(CommentsEA));

            free(eaData);

            if(!rc)
            {
                eaData = malloc(sizeof(CommentsEA));
                memset(eaData, 0, sizeof(CommentsEA));
                rRc = NtQueryEaFile(h, &eaStatus, eaData, sizeof(CommentsEA), TRUE, NULL, 0, NULL, FALSE);

                for(i = 0; i < sizeof(CommentsEA); i++)
                {
                    if(((unsigned char*)eaData)[i] != CommentsEA[i])
                    {
                        cmp = FALSE;
                        break;
                    }
                }

                free(eaData);
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }

    printf("\tFile with comments = \"%s\", rc = 0x%08lx, wRc = %lu, cRc = %lu, rRc = %lu, cmp = %d\n",
           "COMMENTS",
           rc,
           wRc,
           cRc,
           rRc,
           cmp);

    rRc = 0;
    cmp = TRUE;
    h   = CreateFileA("COMMENTS.CRT",
                    dwFilePermissions,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, "This files has a critical .COMMENTS EA\n");
        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        else
        {
            eaData = malloc(sizeof(CommentsEACritical));
            memcpy(eaData, &CommentsEACritical, sizeof(CommentsEACritical));

            rc = NtSetEaFile(h, &eaStatus, eaData, sizeof(CommentsEACritical));

            free(eaData);

            if(!rc)
            {
                eaData = malloc(sizeof(CommentsEACritical));
                memset(eaData, 0, sizeof(CommentsEACritical));
                rRc = NtQueryEaFile(h, &eaStatus, eaData, sizeof(CommentsEACritical), TRUE, NULL, 0, NULL, FALSE);

                for(i = 0; i < sizeof(CommentsEACritical); i++)
                {
                    if(((unsigned char*)eaData)[i] != CommentsEACritical[i])
                    {
                        cmp = FALSE;
                        break;
                    }
                }

                free(eaData);
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }

    printf("\tFile with comments = \"%s\", rc = 0x%08lx, wRc = %lu, cRc = %lu, rRc = %lu, cmp = %d\n",
           "COMMENTS.CRT",
           rc,
           wRc,
           cRc,
           rRc,
           cmp);

    rRc = 0;
    cmp = TRUE;
    h   = CreateFileA("ICON",
                    dwFilePermissions,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        memset(message, 0, 300);
        sprintf(message, "This files has an optional .ICON EA\n");
        ret = WriteFile(h, message, strlen(message), &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();
        else
        {
            eaData = malloc(sizeof(IconEA));
            memcpy(eaData, &IconEA, sizeof(IconEA));

            rc = NtSetEaFile(h, &eaStatus, eaData, sizeof(IconEA));

            free(eaData);

            if(!rc)
            {
                eaData = malloc(sizeof(IconEA));
                memset(eaData, 0, sizeof(IconEA));
                rRc = NtQueryEaFile(h, &eaStatus, eaData, sizeof(IconEA), TRUE, NULL, 0, NULL, FALSE);

                for(i = 0; i < sizeof(IconEA); i++)
                {
                    if(((unsigned char*)eaData)[i] != IconEA[i])
                    {
                        cmp = FALSE;
                        break;
                    }
                }

                free(eaData);
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
    }

    printf("\tFile with icon = \"%s\", rc = 0x%08lx, wRc = %lu, cRc = %lu, rRc = %lu, cmp = %d\n",
           "ICON",
           rc,
           wRc,
           cRc,
           rRc,
           cmp);

    FreeLibrary(ntdll);
}

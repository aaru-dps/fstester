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

#include "sparse.h"

#include "../include/consts.h"
#include "../include/defs.h"

void Sparse(const char* path)
{
    BOOL                             ret;
    DWORD                            error;
    LPSTR                            lpVolumeNameBuffer;
    DWORD                            dwMaximumComponentLength;
    DWORD                            dwFileSystemFlags;
    LPSTR                            lpFileSystemNameBuffer;
    LPSTR                            lpRootPathName;
    size_t                           pathSize = strlen(path);
    DWORD                            rc, wRc, cRc, sRc, zRc;
    WINNT_FILE_ZERO_DATA_INFORMATION zeroData;
    HANDLE                           h;
    unsigned char*                   buffer;
    int                              i;
    DWORD                            dwNumberOfBytesWritten;

    lpVolumeNameBuffer = malloc(dwMaxNameSize);

    if(lpVolumeNameBuffer == NULL)
    {
        printf("Could not allocate memory.\n");
        return;
    }

    lpFileSystemNameBuffer = malloc(dwMaxNameSize);

    if(lpFileSystemNameBuffer == NULL)
    {
        printf("Could not allocate memory.\n");
        free(lpVolumeNameBuffer);
        return;
    }

    lpRootPathName = malloc(dwMaxNameSize);

    if(!lpRootPathName)
    {
        printf("Could not allocate memory.\n");
        free(lpVolumeNameBuffer);
        free(lpFileSystemNameBuffer);
        return;
    }

    memset(lpRootPathName, 0x00, MAX_PATH);
    strncpy(lpRootPathName, path, MAX_PATH);

    if(path[pathSize - 1] != '\\') lpRootPathName[pathSize] = '\\';

    ret = GetVolumeInformationA(lpRootPathName,
                                lpVolumeNameBuffer,
                                dwMaxNameSize,
                                NULL,
                                &dwMaximumComponentLength,
                                &dwFileSystemFlags,
                                lpFileSystemNameBuffer,
                                dwMaxNameSize);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu querying volume information.\n", error);
        free(lpVolumeNameBuffer);
        free(lpFileSystemNameBuffer);
        free(lpRootPathName);
        return;
    }

    free(lpVolumeNameBuffer);
    free(lpFileSystemNameBuffer);

    if(!(dwFileSystemFlags & (DWORD)FILE_SUPPORTS_SPARSE_FILES))
    {
        free(lpRootPathName);
        return;
    }

    ret = SetCurrentDirectoryA(lpRootPathName);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to specified path.\n", error);
        return;
    }

    ret = CreateDirectoryA("SPARSE", NULL);

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu creating working directory.\n", error);
        return;
    }

    ret = SetCurrentDirectoryA("SPARSE");

    if(!ret)
    {
        error = GetLastError();
        printf("Error %lu changing to working directory.\n", error);
        return;
    }

    free(lpRootPathName);

    printf("Creating sparse files.\n");

    h   = CreateFileA("SMALL", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    sRc = 0;
    zRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(4096 * 3);
        memset(buffer, 0, 4096 * 3);

        for(i = 0; i < 4096 * 3; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, 4096 * 3, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = DeviceIoControl(h, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
        if(!ret)
        {
            sRc = GetLastError();
            if(sRc == 1)
            {
                sRc = 0;
                ret = DeviceIoControl(h, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
                if(!ret) { sRc = GetLastError(); }
            }
        }

        if(sRc == 0)
        {
            zeroData.FileOffset.QuadPart      = 4096;
            zeroData.BeyondFinalZero.QuadPart = 8192;

            ret = DeviceIoControl(h,
                                  FSCTL_SET_ZERO_DATA,
                                  &zeroData,
                                  sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                  NULL,
                                  0,
                                  &dwNumberOfBytesWritten,
                                  NULL);
            if(!ret)
            {
                zRc = GetLastError();
                if(zRc == 1)
                {
                    zRc = 0;
                    ret = DeviceIoControl(h,
                                          FSCTL_SET_ZERO_DATA,
                                          &zeroData,
                                          sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                          NULL,
                                          0,
                                          &dwNumberOfBytesWritten,
                                          NULL);
                    if(!ret) { zRc = GetLastError(); }
                }
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu, sRc = %lu, zRc = %lu\n",
           "SMALL",
           4096 * 3,
           rc,
           wRc,
           cRc,
           sRc,
           zRc);

    h   = CreateFileA("BIG", dwFilePermissions, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    sRc = 0;
    zRc = 0;
    if(h == INVALID_HANDLE_VALUE) rc = GetLastError();
    else
    {
        buffer = malloc(4096 * 30);
        memset(buffer, 0, 4096 * 30);

        for(i = 0; i < 4096 * 30; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = WriteFile(h, buffer, 4096 * 30, &dwNumberOfBytesWritten, NULL);
        if(!ret) wRc = GetLastError();

        ret = DeviceIoControl(h, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
        if(!ret)
        {
            sRc = GetLastError();
            if(sRc == 1)
            {
                sRc = 0;
                ret = DeviceIoControl(h, FSCTL_SET_SPARSE_OLD, NULL, 0, NULL, 0, &dwNumberOfBytesWritten, NULL);
                if(!ret) { sRc = GetLastError(); }
            }
        }

        if(sRc == 0)
        {
            zeroData.FileOffset.QuadPart      = 32768;
            zeroData.BeyondFinalZero.QuadPart = 81920;

            ret = DeviceIoControl(h,
                                  FSCTL_SET_ZERO_DATA,
                                  &zeroData,
                                  sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                  NULL,
                                  0,
                                  &dwNumberOfBytesWritten,
                                  NULL);
            if(!ret)
            {
                zRc = GetLastError();
                if(zRc == 1)
                {
                    zRc = 0;
                    ret = DeviceIoControl(h,
                                          FSCTL_SET_ZERO_DATA_OLD,
                                          &zeroData,
                                          sizeof(WINNT_FILE_ZERO_DATA_INFORMATION),
                                          NULL,
                                          0,
                                          &dwNumberOfBytesWritten,
                                          NULL);
                    if(!ret) { zRc = GetLastError(); }
                }
            }
        }

        ret = CloseHandle(h);
        if(!ret) cRc = GetLastError();
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %lu, wRc = %lu, cRc = %lu, sRc = %lu, zRc = %lu\n",
           "BIG",
           4096 * 30,
           rc,
           wRc,
           cRc,
           sRc,
           zRc);
}

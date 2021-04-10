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

#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"
#include "os2defs.h"

#define DATETIME_FORMAT "This file is dated %04d/%02d/%02d %02d:%02d:%02d for %s\n"

void Timestamps(const char* path)
{
    char       drivePath[4];
    APIRET     rc = 0, wRc = 0, cRc = 0, tRc = 0;
    ACTION_RET actionTaken = 0;
    HFILE      handle;
    char       message[300];

    // 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
    USHORT     status_size = sizeof(FILESTATUS);
    FILESTATUS status;
    USHORT     driveNo = path[0] - '@';
#else // 32 bit
    ULONG       status_size = sizeof(FILESTATUS3);
    FILESTATUS3 status;
    ULONG       driveNo = path[0] - '@';
#endif

    if(driveNo > 32) driveNo -= 32;

    rc = __os2_chdisk(driveNo);

    if(rc)
    {
        log_write("Cannot change to specified drive, not continuing.\n");
        return;
    }

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    rc = __os2_chdir(drivePath);

    if(rc)
    {
        log_write("Cannot change to specified path, not continuing.\n");
        return;
    }

    rc = __os2_mkdir("TIMES");

    if(rc)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    rc = __os2_chdir("TIMES");

    log_write("Creating timestamped files.\n");

    rc = DosOpen((PSZ) "MAXCTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 127;
        status.fdateCreation.month   = 12;
        status.fdateCreation.day     = 31;
        status.ftimeCreation.hours   = 23;
        status.ftimeCreation.minutes = 59;
        status.ftimeCreation.twosecs = 29;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "creation");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXCTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MINCTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 0;
        status.fdateCreation.month   = 1;
        status.fdateCreation.day     = 1;
        status.ftimeCreation.hours   = 0;
        status.ftimeCreation.minutes = 0;
        status.ftimeCreation.twosecs = 0;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "creation");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINCTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y19CTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 1999 - 1980;
        status.fdateCreation.month   = 12;
        status.fdateCreation.day     = 31;
        status.ftimeCreation.hours   = 23;
        status.ftimeCreation.minutes = 59;
        status.ftimeCreation.twosecs = 29;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "creation");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19CTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y2KCTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 2000 - 1980;
        status.fdateCreation.month   = 1;
        status.fdateCreation.day     = 1;
        status.ftimeCreation.hours   = 0;
        status.ftimeCreation.minutes = 0;
        status.ftimeCreation.twosecs = 0;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "creation");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19CTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MAXWTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastWrite.year    = 127;
        status.fdateLastWrite.month   = 12;
        status.fdateLastWrite.day     = 31;
        status.ftimeLastWrite.hours   = 23;
        status.ftimeLastWrite.minutes = 59;
        status.ftimeLastWrite.twosecs = 29;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastWrite.year + 1980,
                status.fdateLastWrite.month,
                status.fdateLastWrite.day,
                status.ftimeLastWrite.hours,
                status.ftimeLastWrite.minutes,
                status.ftimeLastWrite.twosecs * 2,
                "last written");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXWTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MINWTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastWrite.year    = 0;
        status.fdateLastWrite.month   = 1;
        status.fdateLastWrite.day     = 1;
        status.ftimeLastWrite.hours   = 0;
        status.ftimeLastWrite.minutes = 0;
        status.ftimeLastWrite.twosecs = 0;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastWrite.year + 1980,
                status.fdateLastWrite.month,
                status.fdateLastWrite.day,
                status.ftimeLastWrite.hours,
                status.ftimeLastWrite.minutes,
                status.ftimeLastWrite.twosecs * 2,
                "last written");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINWTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y19WTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastWrite.year    = 1999 - 1980;
        status.fdateLastWrite.month   = 12;
        status.fdateLastWrite.day     = 31;
        status.ftimeLastWrite.hours   = 23;
        status.ftimeLastWrite.minutes = 59;
        status.ftimeLastWrite.twosecs = 29;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastWrite.year + 1980,
                status.fdateLastWrite.month,
                status.fdateLastWrite.day,
                status.ftimeLastWrite.hours,
                status.ftimeLastWrite.minutes,
                status.ftimeLastWrite.twosecs * 2,
                "last written");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19WTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y2KWTIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastWrite.year    = 2000 - 1980;
        status.fdateLastWrite.month   = 1;
        status.fdateLastWrite.day     = 1;
        status.ftimeLastWrite.hours   = 0;
        status.ftimeLastWrite.minutes = 0;
        status.ftimeLastWrite.twosecs = 0;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastWrite.year + 1980,
                status.fdateLastWrite.month,
                status.fdateLastWrite.day,
                status.ftimeLastWrite.hours,
                status.ftimeLastWrite.minutes,
                status.ftimeLastWrite.twosecs * 2,
                "last written");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KWTIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MAXATIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastAccess.year    = 127;
        status.fdateLastAccess.month   = 12;
        status.fdateLastAccess.day     = 31;
        status.ftimeLastAccess.hours   = 23;
        status.ftimeLastAccess.minutes = 59;
        status.ftimeLastAccess.twosecs = 29;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastAccess.year + 1980,
                status.fdateLastAccess.month,
                status.fdateLastAccess.day,
                status.ftimeLastAccess.hours,
                status.ftimeLastAccess.minutes,
                status.ftimeLastAccess.twosecs * 2,
                "last access");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXATIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MINATIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastAccess.year    = 0;
        status.fdateLastAccess.month   = 1;
        status.fdateLastAccess.day     = 1;
        status.ftimeLastAccess.hours   = 0;
        status.ftimeLastAccess.minutes = 0;
        status.ftimeLastAccess.twosecs = 0;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastAccess.year + 1980,
                status.fdateLastAccess.month,
                status.fdateLastAccess.day,
                status.ftimeLastAccess.hours,
                status.ftimeLastAccess.minutes,
                status.ftimeLastAccess.twosecs * 2,
                "last access");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINATIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y19ATIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastAccess.year    = 1999 - 1980;
        status.fdateLastAccess.month   = 12;
        status.fdateLastAccess.day     = 31;
        status.ftimeLastAccess.hours   = 23;
        status.ftimeLastAccess.minutes = 59;
        status.ftimeLastAccess.twosecs = 29;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastAccess.year + 1980,
                status.fdateLastAccess.month,
                status.fdateLastAccess.day,
                status.ftimeLastAccess.hours,
                status.ftimeLastAccess.minutes,
                status.ftimeLastAccess.twosecs * 2,
                "last access");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19ATIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y2KATIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateLastAccess.year    = 2000 - 1980;
        status.fdateLastAccess.month   = 1;
        status.fdateLastAccess.day     = 1;
        status.ftimeLastAccess.hours   = 0;
        status.ftimeLastAccess.minutes = 0;
        status.ftimeLastAccess.twosecs = 0;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateLastAccess.year + 1980,
                status.fdateLastAccess.month,
                status.fdateLastAccess.day,
                status.ftimeLastAccess.hours,
                status.ftimeLastAccess.minutes,
                status.ftimeLastAccess.twosecs * 2,
                "last access");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KATIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MAX_TIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 127;
        status.fdateCreation.month   = 12;
        status.fdateCreation.day     = 31;
        status.ftimeCreation.hours   = 23;
        status.ftimeCreation.minutes = 59;
        status.ftimeCreation.twosecs = 29;
        status.fdateLastAccess       = status.fdateCreation;
        status.ftimeLastAccess       = status.ftimeCreation;
        status.fdateLastWrite        = status.fdateCreation;
        status.ftimeLastWrite        = status.ftimeCreation;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "all");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAX_TIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "MIN_TIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 0;
        status.fdateCreation.month   = 1;
        status.fdateCreation.day     = 1;
        status.ftimeCreation.hours   = 0;
        status.ftimeCreation.minutes = 0;
        status.ftimeCreation.twosecs = 0;
        status.fdateLastAccess       = status.fdateCreation;
        status.ftimeLastAccess       = status.ftimeCreation;
        status.fdateLastWrite        = status.fdateCreation;
        status.ftimeLastWrite        = status.ftimeCreation;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "all");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MIN_TIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y19_TIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 1999 - 1980;
        status.fdateCreation.month   = 12;
        status.fdateCreation.day     = 31;
        status.ftimeCreation.hours   = 23;
        status.ftimeCreation.minutes = 59;
        status.ftimeCreation.twosecs = 29;
        status.fdateLastAccess       = status.fdateCreation;
        status.ftimeLastAccess       = status.ftimeCreation;
        status.fdateLastWrite        = status.fdateCreation;
        status.ftimeLastWrite        = status.ftimeCreation;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "all");

        wRc = DosWrite(handle, message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19_TIME", rc, wRc, cRc, tRc);

    rc = DosOpen((PSZ) "Y2K_TIME",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        memset(&status, 0, status_size);
        status.fdateCreation.year    = 2000 - 1980;
        status.fdateCreation.month   = 1;
        status.fdateCreation.day     = 1;
        status.ftimeCreation.hours   = 0;
        status.ftimeCreation.minutes = 0;
        status.ftimeCreation.twosecs = 0;
        status.fdateLastAccess       = status.fdateCreation;
        status.ftimeLastAccess       = status.ftimeCreation;
        status.fdateLastWrite        = status.fdateCreation;
        status.ftimeLastWrite        = status.ftimeCreation;
        memset(message, 0, 300);
        sprintf(message,
                DATETIME_FORMAT,
                status.fdateCreation.year + 1980,
                status.fdateCreation.month,
                status.fdateCreation.day,
                status.ftimeCreation.hours,
                status.ftimeCreation.minutes,
                status.ftimeCreation.twosecs * 2,
                "all");

        wRc = DosWrite(handle, &message, strlen(message), &actionTaken);
        tRc = DosSetFileInfo(handle, 1, (PBYTE)&status, status_size);
        cRc = DosClose(handle);
    }

    log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2K_TIME", rc, wRc, cRc, tRc);
}

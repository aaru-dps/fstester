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

void Fragmentation(const char* path, size_t clusterSize)
{
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    char           drivePath[4];
    APIRET         rc = 0, wRc = 0, cRc = 0;
    ACTION_RET     actionTaken = 0;
    HFILE          handle;
    long           i;

// 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
    USHORT driveNo = path[0] - '@';
#else // 32 bit
    ULONG driveNo = path[0] - '@';
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

    rc = __os2_mkdir("FRAGS");

    if(rc)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    rc = __os2_chdir("FRAGS");

    rc = DosOpen((PSZ) "HALFCLST",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, halfCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    rc = DosOpen((PSZ) "QUARCLST",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, quarterCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write(
        "\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    rc = DosOpen((PSZ) "TWOCLST",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, twoCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    rc = DosOpen((PSZ) "TRQTCLST",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, threeQuartersCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "TRQTCLST",
              threeQuartersCluster,
              rc,
              wRc,
              cRc);

    rc = DosOpen((PSZ) "TWTQCLST",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, twoAndThreeQuartCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "TWTQCLST",
              twoAndThreeQuartCluster,
              rc,
              wRc,
              cRc);

    rc = DosOpen((PSZ) "TWO1",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, twoCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    rc = DosOpen((PSZ) "TWO2",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, twoCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    rc = DosOpen((PSZ) "TWO3",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, twoCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tDeleting \"TWO2\".\n");
    rc = __os2_delete((PSZ) "TWO2");

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    rc = DosOpen((PSZ) "FRAGTHRQ",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, threeQuartersCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tDeleting \"TWO1\".\n");
    rc = __os2_delete((PSZ) "TWO1");
    log_write("\tDeleting \"TWO3\".\n");
    rc = __os2_delete((PSZ) "TWO3");

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "FRAGTHRQ",
              threeQuartersCluster,
              rc,
              wRc,
              cRc);

    rc = DosOpen((PSZ) "FRAGSIXQ",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);
    if(!rc)
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = DosWrite(handle, buffer, twoAndThreeQuartCluster, &actionTaken);
        cRc = DosClose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "FRAGSIXQ",
              twoAndThreeQuartCluster,
              rc,
              wRc,
              cRc);
}

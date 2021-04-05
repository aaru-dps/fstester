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

void DeleteFiles(const char* path)
{
    char       drivePath[4];
    APIRET     rc = 0;
    char       filename[9];
    short      pos         = 0;
    ACTION_RET actionTaken = 0;
    HFILE      handle;

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

    rc = __os2_mkdir("DELETED");

    if(rc)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    rc = __os2_chdir("DELETED");

    log_write("Creating and deleting files.\n");

    for(pos = 0; pos < 64; pos++)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%X", pos);
        rc = DosOpen(filename,
                     &handle,
                     &actionTaken,
                     0,
                     FILE_NORMAL,
                     OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                     OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                     0);
        if(rc) break;

        DosClose(handle);
        __os2_delete(filename);
    }
}

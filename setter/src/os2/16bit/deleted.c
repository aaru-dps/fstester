/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : os2_16.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains 16-bit OS/2 code

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

#if(defined(__I86__) || defined(__i86__) || defined(_M_I86)) && (defined(__OS2__) || defined(__os2__)) &&              \
    !defined(__DOS__)

#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../os2.h"
#include "include/consts.h"
#include "include/defs.h"

void DeleteFiles(const char* path)
{
    char   drivePath[4];
    USHORT rc = 0;
    char   filename[9];
    short  pos         = 0;
    USHORT actionTaken = 0;
    HFILE  handle;

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    rc = DosChDir(drivePath, 0);

    if(rc)
    {
        printf("Cannot change to specified path, not continuing.\n");
        return;
    }

    rc = DosMkDir("DELETED", 0);

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = DosChDir("DELETED", 0);

    printf("Creating and deleting files.\n");

    for(pos = 0; pos < 64; pos++)
    {
        memset(&filename, 0, 9);
        sprintf(&filename, "%X", pos);
        rc = DosOpen(&filename,
                     &handle,
                     &actionTaken,
                     0,
                     FILE_NORMAL,
                     OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                     OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_CACHE | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                     0);
        if(rc) break;

        DosClose(handle);
        DosDelete(&filename, 0);
    }
}

#endif
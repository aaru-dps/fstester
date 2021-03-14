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
#include "os2.h"

void Filenames(const char* path)
{
    char       drivePath[4];
    APIRET     rc = 0, wRc = 0, cRc = 0;
    ACTION_RET actionTaken = 0;
    HFILE      handle;
    char       message[300];
    int        pos = 0;

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    rc = __os2_chdir(drivePath);

    if(rc)
    {
        printf("Cannot change to specified path, not continuing.\n");
        return;
    }

    rc = __os2_mkdir("FILENAME");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = __os2_chdir("FILENAME");

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        rc = DosOpen((PSZ)filenames[pos],
                     &handle,
                     &actionTaken,
                     0,
                     FILE_NORMAL,
                     OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_FAIL_IF_EXISTS,
                     OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                     0);

        if(!rc)
        {
            memset(message, 0, 300);
            sprintf(message, FILENAME_FORMAT, filenames[pos]);
            wRc = DosWrite(handle, message, strlen(message), &actionTaken);
            cRc = DosClose(handle);
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}

/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : attr.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains common OS/2 code

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

#include "attr.h"

#include "include/consts.h"
#include "include/defs.h"
#include "os2.h"

void FileAttributes(const char* path)
{
    char   drivePath[4];
    APIRET rc = 0, wRc = 0, cRc = 0;
    HFILE  handle;
    int        i;
    ACTION_RET actionTaken = 0;

// 32 bit
#if(defined(__I386__) || defined(__i386__) || defined(__THW_INTEL) || defined(_M_I386))
    FILESTATUS3 fileStatus  = {{0}};
#endif

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

    rc = __os2_mkdir("ATTRS");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = __os2_chdir("ATTRS");

    printf("Creating attributes files.\n");

    for(i = 0; i < KNOWN_OS2_ATTRS; i++)
    {
        rc = DosOpen(os2_attrs[i].filename,
                     &handle,
                     &actionTaken,
                     0,
                     FILE_NORMAL,
                     OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                     OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                     0);

        if(!rc)
        {
            wRc = DosWrite(handle, (PVOID)os2_attrs[i].contents, strlen(os2_attrs[i].contents), &actionTaken);

            // 32 bit
#if(defined(__I386__) || defined(__i386__) || defined(__THW_INTEL) || defined(_M_I386))
            // It operates over the handle so file must be closed after setting attribute
            fileStatus.attrFile = os2_attrs[i].attr;
            rc                  = DosSetFileInfo(handle, FIL_STANDARD, &fileStatus, sizeof(FILESTATUS3));
            cRc                 = DosClose(handle);
#else // 16 bit
      // It operates over the filename so file must be closed before setting attribute
            cRc = DosClose(handle);
            rc  = DosSetFileMode(os2_attrs[i].filename, os2_attrs[i].attr, 0);
#endif
        }

        printf("\t%s: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
               os2_attrs[i].description,
               os2_attrs[i].filename,
               rc,
               wRc,
               cRc);
    }
}

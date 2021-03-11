/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : os2_32.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains 32-bit OS/2 code

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

#if(defined(__I386__) || defined(__i386__) || defined(__THW_INTEL) || defined(_M_I386)) &&                             \
    (defined(__OS2__) || defined(__os2__)) && !defined(__DOS__)

#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../os2.h"
#include "include/consts.h"
#include "include/defs.h"

void DirectoryDepth(const char* path)
{
    char   drivePath[4];
    APIRET rc = 0;
    char   filename[9];
    long   pos = 2;

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    rc = DosSetCurrentDir(drivePath);

    if(rc)
    {
        printf("Cannot change to specified path, not continuing.\n");
        return;
    }

    rc = DosCreateDir("DEPTH", NULL);

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = DosSetCurrentDir("DEPTH");

    printf("Creating deepest directory tree.\n");

    while(!rc)
    {
        memset(&filename, 0, 9);
        sprintf(&filename, "%08d", pos);
        rc = DosCreateDir(filename, NULL);

        if(!rc) rc = DosSetCurrentDir(filename);

        pos++;
    }

    printf("\tCreated %d levels of directory hierarchy\n", pos);
}

#endif
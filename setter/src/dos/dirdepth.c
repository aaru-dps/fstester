/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : dos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains DOS code

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

#if defined(__DOS__) || defined(MSDOS)

#include <direct.h>
#include <dos.h>
#include <i86.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "../include/dosos2.h"
#include "dos.h"

void DirectoryDepth(const char* path)
{
    char     driveNo = path[0] - '@';
    int      rc      = 0;
    unsigned total;
    char     filename[9];
    long     pos = 2;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = mkdir("DEPTH");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = chdir("DEPTH");

    printf("Creating deepest directory tree.\n");

    while(!rc)
    {
        memset(&filename, 0, 9);
        sprintf(&filename, "%08d", pos);
        rc = mkdir(filename);

        if(!rc) rc = chdir(filename);

        pos++;
    }

    printf("\tCreated %d levels of directory hierarchy\n", pos);
}

#endif

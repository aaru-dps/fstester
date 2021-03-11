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

#include <dos.h>
#include <stdio.h>
#include <string.h>

#if defined(__WATCOM__)
#include <direct.h>
#elif defined(__DJGPP__)
#include <unistd.h>
#endif

#include "../include/defs.h"
#include "dos.h"

void MillionFiles(const char* path)
{
    char          driveNo = path[0] - '@';
    int           rc      = 0;
    char          filename[9];
    unsigned long pos = 0;
    int           handle;
    unsigned      total;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = __dos_mkdir("MILLION");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = chdir("MILLION");

    printf("Creating lots of files.\n");

    for(pos = 0; pos < 1000; pos++)
    {
        memset(&filename, 0, 9);
        sprintf(&filename, "%08llu", pos);
        rc = _dos_creatnew(&filename, _A_NORMAL, &handle);
        if(rc) break;

        _dos_close(handle);
    }

    printf("\tCreated %llu files\n", pos);
}

#endif
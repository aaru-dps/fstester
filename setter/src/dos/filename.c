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

#include "../include/consts.h"
#include "../include/defs.h"
#include "dos.h"

void Filenames(const char* path)
{
    char     driveNo = path[0] - '@';
    int      rc = 0, wRc = 0, cRc = 0;
    unsigned actionTaken, total;
    int      handle;
    char     message[300];
    int      pos = 0;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = __dos_mkdir("FILENAME");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = chdir("FILENAME");

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        rc = _dos_creatnew(filenames[pos], _A_NORMAL, &handle);

        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf(&message, FILENAME_FORMAT, filenames[pos]);
            wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
            cRc = _dos_close(handle);
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}

#endif

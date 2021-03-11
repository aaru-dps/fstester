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
#include "attr.h"
#include "dos.h"

void FileAttributes(const char* path)
{
    char         driveNo = path[0] - '@';
    unsigned     total, actionTaken;
    unsigned int rc, wRc, cRc;
    int          handle;
    int          i;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = __dos_mkdir("ATTRS");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    chdir("ATTRS");

    printf("Creating attributes files.\n");

    for(i = 0; i < KNOWN_DOS_ATTRS; i++)
    {
        rc = _dos_creat(dos_attrs[i].filename, _A_NORMAL, &handle);

        if(!rc)
        {
            wRc = _dos_write(handle, (void*)dos_attrs[i].contents, strlen(dos_attrs[i].contents), &actionTaken);
            cRc = _dos_close(handle);
            rc  = _dos_setfileattr(dos_attrs[i].filename, dos_attrs[i].attr);
        }

        printf("\t%s: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
               dos_attrs[i].description,
               dos_attrs[i].filename,
               rc,
               wRc,
               cRc);
    }
}

#endif

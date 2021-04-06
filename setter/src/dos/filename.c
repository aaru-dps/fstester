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
#include "../log.h"
#include "dosdefs.h"

void Filenames(const char* path)
{
    char         driveNo = path[0] - '@';
    unsigned int rc, wRc = 0, cRc = 0;
    unsigned     actionTaken, total;
    int          handle;
    char         message[300];
    int          pos;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = __dos_mkdir("FILENAME");

    if(rc)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    chdir("FILENAME");

    log_write("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        rc = _dos_creatnew(filenames[pos], 0, &handle);

        if(!rc)
        {
            memset(message, 0, 300);
            sprintf(message, FILENAME_FORMAT, filenames[pos]);
            wRc = _dos_write(handle, message, strlen(message), &actionTaken);
            cRc = _dos_close(handle);
        }

        log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}

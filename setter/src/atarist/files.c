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

#include <eti.h>
#include <mint/osbind.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "../log.h"

void MillionFiles(const char* path)
{
    char         driveNo = path[0] - '@';
    unsigned int rc;
    char         filename[9];
    unsigned int pos;
    int          handle;
    unsigned     total;

    if(driveNo > 32) driveNo -= 32;

    Dsetdrv(driveNo);
    Dsetpath("\\");

    rc = Dcreate("MILLION");

    if(rc != E_OK)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    Dsetpath("MILLION");

    log_write("Creating lots of files.\n");

    for(pos = 0; pos < 1000; pos++)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08d", pos);
        handle = Fcreate(filename, 0);
        if(rc < 0) break;

        Fclose(handle);
    }

    log_write("\tCreated %d files\n", pos);
}

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

void DirectoryDepth(const char* path)
{
    char         driveNo = path[0] - '@';
    unsigned int rc;
    char         filename[9];
    int          pos = 2;

    if(driveNo > 32) driveNo -= 32;

    Dsetdrv(driveNo);
    Dsetpath("\\");

    rc = Dcreate("DEPTH");

    if(rc != E_OK)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    rc = Dsetpath("DEPTH");

    log_write("Creating deepest directory tree.\n");

    while(rc == E_OK)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08d", pos);
        rc = Dcreate(filename);

        if(rc == E_OK) rc = Dsetpath(filename);

        pos++;
    }

    log_write("\tCreated %d levels of directory hierarchy\n", pos);
}

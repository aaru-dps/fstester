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
#include "../log.h"
#include "os2defs.h"

void DirectoryDepth(const char* path)
{
    char   drivePath[4];
    APIRET rc = 0;
    char   filename[9];
    int    pos = 2;

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    rc = __os2_chdir(drivePath);

    if(rc)
    {
        log_write("Cannot change to specified path, not continuing.\n");
        return;
    }

    rc = __os2_mkdir("DEPTH");

    if(rc)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    rc = __os2_chdir("DEPTH");

    log_write("Creating deepest directory tree.\n");

    while(!rc)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08d", pos);
        rc = __os2_mkdir(filename);

        if(!rc) rc = __os2_chdir(filename);

        pos++;
    }

    log_write("\tCreated %d levels of directory hierarchy\n", pos);
}

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

#include <mint/osbind.h>
#include <mint/ostruct.h>
#include <stdio.h>
#include <string.h>

#include "attr.h"

#include "../include/defs.h"
#include "../log.h"

void FileAttributes(const char* path)
{
    char  driveNo = path[0] - '@';
    short rc, wRc, cRc;
    short handle;
    int   i;

    if(driveNo > 32) driveNo -= 32;

    Dsetdrv(driveNo);
    Dsetpath("\\");

    rc = Dcreate("ATTRS");

    if(rc)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    Dsetpath("ATTRS");

    log_write("Creating attributes files.\n");

    for(i = 0; i < KNOWN_ATARI_ATTRS; i++)
    {
        handle = Fcreate(atari_attrs[i].filename, 0);

        if(handle > 0)
        {
            wRc = Fwrite(handle, strlen(atari_attrs[i].contents), (void*)atari_attrs[i].contents);
            cRc = Fclose(handle);
            rc  = Fattrib(atari_attrs[i].filename, 1, atari_attrs[i].attr);
        }

        log_write("\t%s: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
                  atari_attrs[i].description,
                  atari_attrs[i].filename,
                  rc,
                  wRc,
                  cRc);
    }
}

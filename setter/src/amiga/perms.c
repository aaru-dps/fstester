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

#include <dos/dos.h>
#include <proto/dos.h>
#include <stdio.h>
#include <string.h>
#if defined(__amigaos4__)
#include <dos/obsolete.h>
#endif

#include "../include/defs.h"
#include "../log.h"
#include "perms.h"

void FilePermissions(const char* path)
{
    BPTR pathLock;
    BPTR dirLock;
    BPTR file;
    int  rc;
    int  cRc;
    int  i;
    char buffer[256];

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "PERMS");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Creating permissions files.\n");

    for(i = 0; i < KNOWN_AMIGA_PERMS; i++)
    {
        file = Open((CONST_STRPTR)amiga_perms[i].filename, MODE_NEWFILE);
        rc   = 0;
        cRc  = 0;

        if(!file) rc = IoErr();
        else
        {
            memset(buffer, 0, 256);
            snprintf(buffer, 256, "%s.\n", amiga_perms[i].description);
            Write(file, buffer, 256);
            Close(file);
            cRc = SetProtection((CONST_STRPTR)amiga_perms[i].filename, amiga_perms[i].mode);
            if(!cRc) cRc = IoErr();
        }

        log_write(
            "\t%s: name = \"%s\", rc = %d, cRc = %d\n", amiga_perms[i].description, amiga_perms[i].filename, rc, cRc);
    }
}

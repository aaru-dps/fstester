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

#include <proto/dos.h>
#include <string.h>
#if defined(__amigaos4__)
#include <dos/obsolete.h>
#endif

#include "../include/defs.h"
#include "../log.h"

void ExtendedAttributes(const char* path)
{
    BPTR  pathLock;
    BPTR  dirLock;
    BPTR  file;
    int   rc;
    int   cRc;
    char* buffer = "This file has a comment.\n";

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "XATTRS");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Creating files with extended attributes.\n");

    rc   = 0;
    cRc  = 0;
    file = Open((CONST_STRPTR) "comment", MODE_NEWFILE);
    if(!file) rc = IoErr();
    else
    {
        Write(file, buffer, strlen(buffer));
        Close(file);

        cRc = SetComment((CONST_STRPTR) "comment", (CONST_STRPTR) "This is a comment for a file named comment!\n");
        if(!cRc) cRc = IoErr();
    }
    log_write("\tFile with an extended attribute called \"comment\", rc = %d, cRc = %d\n", rc, cRc);
}

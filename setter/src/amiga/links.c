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

#include "../include/defs.h"
#include "../log.h"

// This is a stupid way of doing things by the Amiga/AROS/MorphOS SDK creators
#if defined(__amigaos4__)
#define LNKLONG APTR
#elif defined(__AROS__)
#define LNKLONG SIPTR
#else
#define LNKLONG LONG
#endif

void Links(const char* path)
{
    BPTR pathLock;
    BPTR dirLock;
    BPTR h;
    int  ret;

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "LINKS");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Creating links.\n");

    h = Open((CONST_STRPTR) "TARGET", MODE_NEWFILE);

    if(!h)
    {
        log_write("Error %d creating target file.\n", IoErr());
        return;
    }

    Write(h, "This is the target for the links.\n", strlen("This is the target for the links.\n"));

    ret = MakeLink((CONST_STRPTR) "HARD", (LNKLONG)h, LINK_HARD);

    if(ret != DOSTRUE) log_write("Error %d creating hard link.\n", IoErr());

    ret = MakeLink((CONST_STRPTR) "SYMBOLIC", (LNKLONG) "TARGET", LINK_SOFT);

    if(ret != DOSTRUE) log_write("Error %d creating symbolic link.\n", IoErr());

    Close(h);

    h = CreateDir((CONST_STRPTR) "TARGETDIR");

    if(!h)
    {
        log_write("Error %d creating target directory.\n", IoErr());
        return;
    }

    ret = MakeLink((CONST_STRPTR) "DIRLINK", (LNKLONG)h, LINK_HARD);

    if(ret != DOSTRUE) log_write("Error %d creating directory hard link.\n", IoErr());
}

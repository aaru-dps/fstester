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
#include <stdio.h>
#include <string.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"

void Filenames(const char* path)
{
    BPTR pathLock;
    BPTR dirLock;
    int  ret;
    BPTR h;
    int  rc, wRc, cRc;
    int  pos;
    char text[255];

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "FILENAME");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        h   = Open((CONST_STRPTR)filenames[pos], MODE_NEWFILE);
        rc  = 0;
        wRc = 0;
        cRc = 0;

        if(!h) { rc = IoErr(); }
        else
        {
            memset(text, 0, 255);
            snprintf(text, 255, FILENAME_FORMAT, filenames[pos]);
            ret = Write(h, text, strlen(text));

            if(ret < 0) wRc = IoErr();

            ret = Close(h);
            if(!ret) cRc = IoErr();
        }

        log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}

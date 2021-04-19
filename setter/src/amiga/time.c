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
#if defined(__amigaos4__)
#include <dos/obsolete.h>
#endif

#include "../include/defs.h"
#include "../log.h"
#include "time.h"

void Timestamps(const char* path)
{
    BPTR             pathLock;
    BPTR             dirLock;
    int              ret;
    BPTR             h;
    int              rc, wRc, cRc, tRc;
    struct DateStamp times;
    int              i;
    char             buffer[256];

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "TIMES");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Creating timestamped files.\n");

    for(i = 0; i < KNOWN_AMIGA_TIMES; i++)
    {
        memset(&times, 0, sizeof(struct DateStamp));
        h   = Open((CONST_STRPTR)amiga_times[i].filename, MODE_NEWFILE);
        rc  = 0;
        wRc = 0;
        cRc = 0;
        tRc = 0;

        if(!h) rc = IoErr();
        else
        {
            times.ds_Days   = amiga_times[i].days;
            times.ds_Minute = amiga_times[i].minutes;
            times.ds_Tick   = amiga_times[i].ticks;

            memset(buffer, 0, 255);
            snprintf(buffer, 255, DATETIME_FORMAT, amiga_times[i].message);

            ret = Write(h, buffer, 255);
            if(ret < 0) wRc = IoErr();

            ret = Close(h);
            if(!ret) cRc = IoErr();

            ret = SetFileDate((CONST_STRPTR)amiga_times[i].filename, &times);
            if(!ret) tRc = IoErr();
        }

        log_write("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n",
                  amiga_times[i].filename,
                  rc,
                  wRc,
                  cRc,
                  tRc);
    }
}

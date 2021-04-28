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

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

#include "../include/defs.h"
#include "../log.h"
#include "beostime.h"

void Timestamps(const char* path)
{
    int            ret;
    FILE*          h;
    int            rc, wRc, cRc, tRc;
    struct utimbuf times;
    int            i;

    ret = chdir(path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("TIMES", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("TIMES");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);
        return;
    }

    log_write("Creating timestamped files.\n");

    for(i = 0; i < KNOWN_BEOS_TIMES; i++)
    {
        memset(&times, 0, sizeof(struct utimbuf));
        h   = fopen(beos_times[i].filename, "w+");
        rc  = 0;
        wRc = 0;
        cRc = 0;
        tRc = 0;
        if(h == NULL) { rc = errno; }
        else
        {
            times.actime  = beos_times[i].access;
            times.modtime = beos_times[i].modification;

            ret = fprintf(h, DATETIME_FORMAT, beos_times[i].message, beos_times[i].type);
            if(ret < 0) { wRc = errno; }

            ret = fclose(h);
            if(ret) { cRc = errno; }

            ret = utime(beos_times[i].filename, &times);
            if(ret) { tRc = errno; }
        }
        log_write(
            "\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", beos_times[i].filename, rc, wRc, cRc, tRc);
    }
}

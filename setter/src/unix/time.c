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

#if defined(__NeXT__)
#if NS_TARGET < 42 && !defined(_POSIX_SOURCE)
#error Need to be compiled with -posix argument
#elif NS_TARGET >= 42 && defined(_POSIX_SOURCE)
#error Need to be compiled without -posix argument
#endif
#endif

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

#include "time.h"

#include "../include/defs.h"
#include "../log.h"

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

    for(i = 0; i < KNOWN_UNIX_TIMES; i++)
    {
        memset(&times, 0, sizeof(struct utimbuf));
        h   = fopen(unix_times[i].filename, "w+");
        rc  = 0;
        wRc = 0;
        cRc = 0;
        tRc = 0;
        if(h == NULL) { rc = errno; }
        else
        {
            times.actime  = unix_times[i].access;
            times.modtime = unix_times[i].modification;

            ret = fprintf(h, DATETIME_FORMAT, unix_times[i].message, unix_times[i].type);
            if(ret < 0) { wRc = errno; }

            ret = fclose(h);
            if(ret) { cRc = errno; }

            ret = utime(unix_times[i].filename, &times);
            if(ret) { tRc = errno; }
        }
        log_write(
            "\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", unix_times[i].filename, rc, wRc, cRc, tRc);
    }
}

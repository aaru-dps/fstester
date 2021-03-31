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

#include "../../include/consts.h"
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../log.h"
#include "linux.h"

void LinuxSparse(const char* path)
{
    int   ret;
    int   rc, wRc, cRc, zRc;
    FILE* h;
    int   i;
    int   fd;

    ret = chdir(path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("SPARSE", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("SPARSE");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);
        return;
    }

    log_write("Creating sparse files.\n");

    h   = fopen("SMALL", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    zRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        for(i = 0; i < 4096 * 3; i += CLAUNIA_SIZE)
        {
            ret = fwrite(clauniaBytes, CLAUNIA_SIZE, 1, h);
            if(ret < 0)
            {
                wRc = errno;
                break;
            }
        }

        fd  = fileno(h);
        ret = fallocate(fd, FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE, 4096, 8192);
        if(ret) { zRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d, sRc = %d\n",
              "SMALL",
              4096 * 4,
              rc,
              wRc,
              cRc,
              zRc);

    h   = fopen("BIG", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    zRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        for(i = 0; i < 4096 * 30; i += CLAUNIA_SIZE)
        {
            ret = fwrite(clauniaBytes, CLAUNIA_SIZE, 1, h);
            if(ret < 0)
            {
                wRc = errno;
                break;
            }
        }

        fd  = fileno(h);
        ret = fallocate(fd, FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE, 32768, 81920);
        if(ret) { zRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d, sRc = %d\n",
              "BIG",
              4096 * 30,
              rc,
              wRc,
              cRc,
              zRc);
}

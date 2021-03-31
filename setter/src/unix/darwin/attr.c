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
#include <stdio.h>
#include <unistd.h>

#include "attr.h"

#include "../../log.h"

void DarwinFileAttributes(const char* path)
{
    int   ret;
    int   fd;
    FILE* h;
    int   rc;
    int   wRc;
    int   sRc;
    int   cRc;
    int   attr;
    int   i;

    ret = chdir(path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("ATTRS", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("ATTRS");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);
        return;
    }

    log_write("Creating files with different flags (attributes).\n");

    for(i = 0; i < KNOWN_DARWIN_ATTRS; i++)
    {
        h    = fopen(darwin_attrs[i].filename, "w+");
        rc   = 0;
        wRc  = 0;
        sRc  = 0;
        cRc  = 0;
        attr = 0;
        if(h == NULL) { rc = errno; }
        else
        {
            fd  = fileno(h);
            ret = fchflags(fd, darwin_attrs[i].attr);

            if(ret)
            {
                sRc = errno;
                unlink(darwin_attrs[i].filename);
            }
            else
            {
                ret = fprintf(h, "%s", darwin_attrs[i].contents);
                if(ret < 1)
                {
                    wRc = errno;
                    unlink(darwin_attrs[i].filename);
                }
            }

            ret = fclose(h);
            if(ret) { cRc = errno; }
        }
        log_write("\t%s, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", darwin_attrs[i].description, rc, wRc, sRc, cRc);
    }
}

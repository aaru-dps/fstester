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
#include <linux/fs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "attr.h"

#include "linux.h"

void LinuxFileAttributes(const char* path)
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
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("ATTRS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("ATTRS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating files with different flags (attributes).\n");

    for(i = 0; i < KNOWN_LINUX_ATTRS; i++)
    {
        h    = fopen(linux_attrs[i].filename, "w+");
        rc   = 0;
        wRc  = 0;
        sRc  = 0;
        cRc  = 0;
        attr = 0;
        if(h == NULL) { rc = errno; }
        else
        {
            attr |= linux_attrs[i].attr;
            fd  = fileno(h);
            ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

            if(ret)
            {
                sRc = errno;
                unlink(linux_attrs[i].filename);
            }
            else
            {
                ret = fprintf(h, "%s", linux_attrs[i].contents);
                if(ret < 1)
                {
                    wRc = errno;
                    unlink(linux_attrs[i].filename);
                }
            }

            ret = fclose(h);
            if(ret) { cRc = errno; }
        }
        printf("\t%s, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", linux_attrs[i].description, rc, wRc, sRc, cRc);
    }
}

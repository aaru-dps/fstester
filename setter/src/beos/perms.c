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
#include <sys/stat.h>
#include <unistd.h>

#include "perms.h"

#include "../include/defs.h"
#include "../log.h"

void FilePermissions(const char* path)
{
    int   ret;
    FILE* file;
    int   rc;
    int   cRc;
    int   i;

    ret = chdir(path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("PERMS", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("PERMS");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);
        return;
    }

    log_write("Creating attributes files.\n");

    for(i = 0; i < KNOWN_BEOS_PERMS; i++)
    {
        file = fopen(beos_perms[i].filename, "w+");
        rc   = 0;
        cRc  = 0;

        if(!file) rc = errno;
        else
        {
            fprintf(file, "%s.\n", beos_perms[i].description);
            fclose(file);
            cRc = chmod(beos_perms[i].filename, beos_perms[i].mode);
        }

        log_write(
            "\t%s: name = \"%s\", rc = %d, cRc = %d\n", beos_perms[i].description, beos_perms[i].filename, rc, cRc);
    }
}

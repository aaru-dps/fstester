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
#include <sys/stat.h>
#include <unistd.h>

#include "../include/defs.h"

void Links(const char* path)
{
    FILE* h;
    int   ret;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("LINKS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("LINKS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating links.\n");

    h = fopen("TARGET", "w+");

    if(h == NULL)
    {
        printf("Error %d creating target file.\n", errno);
        return;
    }

    fprintf(h, "This is the target for the links.\n");

    fclose(h);

    ret = link("TARGET", "HARD");

    if(ret) { printf("Error %d creating hard link.\n", errno); }

    ret = symlink("TARGET", "SYMBOLIC");

    if(ret) { printf("Error %d creating symbolic link.\n", errno); }
}

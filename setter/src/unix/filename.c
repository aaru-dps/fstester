/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : filename.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains common implementations for UNIX family and compatibles

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
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/consts.h"
#include "../include/defs.h"

void Filenames(const char* path)
{
    int   ret;
    FILE* h;
    int   rc, wRc, cRc;
    char  message[300];
    int   pos = 0;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("FILENAME", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("FILENAME");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        h   = fopen(filenames[pos], "w+");
        rc  = 0;
        wRc = 0;
        cRc = 0;

        if(!h) { rc = errno; }
        else
        {
            memset(&message, 0, 300);
            sprintf((char*)&message, FILENAME_FORMAT, filenames[pos]);

            ret = fprintf(h, (const char*)&message);
            if(ret < 0) { wRc = errno; }

            ret = fclose(h);
            if(ret) { cRc = errno; }
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}

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

#include "../include/consts.h"
#include "../include/defs.h"

void Filenames(const char* path)
{
    int   ret;
    FILE* h;
    int   rc, wRc, cRc;
    int   pos;

    printf("\nPlease insert the \"FILENAME\" disk.\n");
    printf("Press Y to continue,\n");
    printf("any other key exits.\n");
    ret = getchar();

    if(ret != 'Y' && ret != 'y') return;

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        h   = fopen(filenames[pos], "w");
        rc  = 0;
        wRc = 0;
        cRc = 0;

        if(!h) rc = errno != 0 ? errno : -1;
        else
        {
            ret = fprintf(h, FILENAME_FORMAT, filenames[pos]);
            if(ret < 0) { wRc = errno; }

            ret = fclose(h);
            if(ret) { cRc = errno; }
        }

        printf("%d:%d,%d,%d-", pos, rc, wRc, cRc);
    }

    printf("\n\n");
}

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

#ifdef USE_FOLDERS
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "../include/defs.h"

void DirectoryDepth(const char* path)
{
#ifdef USE_FOLDERS
    int  ret;
    char filename[9];
    long pos = 0;

    printf("Please insert the \"DEPTH\" disk.\n");
    printf("Press Y to continue, any other key exits.\n");
    ret = getchar();

    if(ret != 'Y' && ret != 'y') return;

    while(!ret)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08ld", pos);
        ret = mkdir(filename, 0755);

        if(!ret) ret = chdir(filename);

        pos++;

        // This can continue until the disk fills, the kernel crashes, or some other nasty success
        if(pos >= 1000) break;
    }

    printf("\tCreated %ld levels of directory hierarchy\n", pos);
#endif
}

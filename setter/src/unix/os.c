/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : os.c
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
#include <sys/utsname.h>

#include "../include/defs.h"

void GetOsInfo()
{
    struct utsname buf;
    int            ret;

    ret = uname(&buf);

    if(ret)
    {
        printf("Error %d retrieving OS information.\n", errno);
        return;
    }

    printf("OS information:\n");
    printf("\tOS name: %s\n", buf.sysname);
    printf("\tRelease: %s\n", buf.release);
    printf("\tVersion: %s\n", buf.version);
    printf("\tMachine: %s\n", buf.machine);
}

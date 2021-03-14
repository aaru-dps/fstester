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

#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../os2.h"
#include "../../include/consts.h"
#include "../../include/defs.h"

void GetOsInfo()
{
    ULONG  aulBuffer[3];
    APIRET rc;
    ULONG  MajorVer;
    ULONG  MinorVer;
    ULONG  pathLen[1];

    rc = DosQuerySysInfo(QSV_VERSION_MAJOR, QSV_VERSION_REVISION, (PVOID)aulBuffer, 3 * sizeof(ULONG));

    if(rc)
    {
        printf("Error %d querying OS/2 version.\n", rc);
        return;
    }

    if(aulBuffer[0] == 20)
    {
        MajorVer = aulBuffer[1] / 10;
        MinorVer = aulBuffer[1] % 10;
    }
    else
    {
        MajorVer = aulBuffer[0];
        MinorVer = aulBuffer[1];
    }

    printf("OS information:\n");

    if(aulBuffer[2] > 0x20) printf("\tRunning under OS/2 %d.%d revision %c.\n", MajorVer, MinorVer, aulBuffer[2]);
    else
        printf("\tRunning under OS/2 %d.%d\n", MajorVer, MinorVer);

    rc = DosQuerySysInfo(QSV_MAX_PATH_LENGTH, QSV_MAX_PATH_LENGTH, (PVOID)pathLen, sizeof(ULONG));

    printf("\tMaximum path is %lu bytes.\n", pathLen[0]);
}

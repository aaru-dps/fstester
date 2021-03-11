/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : os2_32.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains 32-bit OS/2 code

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

#if(defined(__I386__) || defined(__i386__) || defined(__THW_INTEL) || defined(_M_I386)) &&                             \
    (defined(__OS2__) || defined(__os2__)) && !defined(__DOS__)

#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../os2.h"
#include "include/consts.h"
#include "include/defs.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    APIRET      rc;
    BYTE        bData[64];
    ULONG       cbData = sizeof(bData);
    PFSALLOCATE pfsAllocateBuffer;
    ULONG       driveNo = path[0] - '@';
    char*       fsdName;
    PFSINFO     pfsInfo;

    if(driveNo > 32) driveNo -= 32;

    *clusterSize = 0;

    rc = DosQueryFSAttach((PSZ)path, 0, FSAIL_QUERYNAME, (PVOID)&bData, &cbData);

    printf("Volume information:\n");
    printf("\tPath: %s\n", path);
    printf("\tDrive number: %d\n", driveNo - 1);

    if(rc) { printf("Error %d requesting volume information.\n", rc); }
    else
    {
        fsdName = &bData[8 + (USHORT)bData[2] + 1];
        printf("\tFSD name: %s\n", fsdName);
    }

    pfsAllocateBuffer = (PFSALLOCATE)malloc(sizeof(FSALLOCATE));
    rc                = DosQueryFSInfo(driveNo, FSIL_ALLOC, (PBYTE)pfsAllocateBuffer, sizeof(FSALLOCATE));

    if(rc) { printf("Error %d requesting volume information.\n", rc); }
    else
    {
        printf("\tBytes per sector: %u\n", pfsAllocateBuffer->cbSector);
        printf("\tSectors per cluster: %lu (%lu bytes)\n",
               pfsAllocateBuffer->cSectorUnit,
               pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector);
        printf("\tClusters: %lu (%lu bytes)\n",
               pfsAllocateBuffer->cUnit,
               pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector * pfsAllocateBuffer->cUnit);
        printf("\tFree clusters: %lu (%lu bytes)\n",
               pfsAllocateBuffer->cUnitAvail,
               pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector * pfsAllocateBuffer->cUnitAvail);

        *clusterSize = pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector;
    }

    free(pfsAllocateBuffer);

    pfsInfo = (PFSINFO)malloc(sizeof(FSINFO));
    rc      = DosQueryFSInfo(driveNo, FSIL_VOLSER, (PBYTE)pfsInfo, sizeof(FSINFO));

    if(rc) { printf("Error %d requesting volume information.\n", rc); }
    else
    {
        printf("\tVolume label: %s\n", pfsInfo->vol.szVolLabel);
        printf("\tVolume created on %d/%02d/%02d %02d:%02d:%02d\n",
               pfsInfo->fdateCreation.year + 1980,
               pfsInfo->fdateCreation.month - 1,
               pfsInfo->fdateCreation.day,
               pfsInfo->ftimeCreation.hours,
               pfsInfo->ftimeCreation.minutes,
               pfsInfo->ftimeCreation.twosecs * 2);
    }

    free(pfsInfo);
}

#endif

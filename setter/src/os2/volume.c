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

#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"
#include "os2.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    APIRET      rc;
    BYTE        bData[64];
    PFSALLOCATE pfsAllocateBuffer;
    char*       fsdName;
    PFSINFO     pfsInfo;

// 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
    USHORT cbData  = sizeof(bData);
    USHORT driveNo = path[0] - '@';
#else // 32 bit
    ULONG cbData  = sizeof(bData);
    ULONG driveNo = path[0] - '@';
#endif

    if(driveNo > 32) driveNo -= 32;

    *clusterSize = 0;

// 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
    rc = DosQFSAttach((PSZ)path, 0, FSAIL_QUERYNAME, (PVOID)&bData, &cbData, 0);
#else // 32 bit
    rc            = DosQueryFSAttach((PSZ)path, 0, FSAIL_QUERYNAME, (PVOID)&bData, &cbData);
#endif

    log_write("Volume information:\n");
    log_write("\tPath: %s\n", path);
    log_write("\tDrive number: %d\n", driveNo - 1);

    if(rc) log_write("Error %d requesting volume information.\n", rc);
    else
    {
// 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
        fsdName = &bData[4 + (USHORT)bData[2] + 1 + 2];
#else // 32 bit
        fsdName = &bData[8 + (USHORT)bData[2] + 1];
#endif
        log_write("\tFSD name: %s\n", fsdName);
    }

    pfsAllocateBuffer = (PFSALLOCATE)malloc(sizeof(FSALLOCATE));

// 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
    rc = DosQFSInfo(driveNo, 1, (PBYTE)pfsAllocateBuffer, sizeof(FSALLOCATE));
#else // 32 bit
    rc = DosQueryFSInfo(driveNo, FSIL_ALLOC, (PBYTE)pfsAllocateBuffer, sizeof(FSALLOCATE));
#endif

    if(rc) log_write("Error %d requesting volume information.\n", rc);
    else
    {
        log_write("\tBytes per sector: %u\n", pfsAllocateBuffer->cbSector);
        log_write("\tSectors per cluster: %lu (%lu bytes)\n",
                  pfsAllocateBuffer->cSectorUnit,
                  pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector);
        log_write("\tClusters: %lu (%lu bytes)\n",
                  pfsAllocateBuffer->cUnit,
                  pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector * pfsAllocateBuffer->cUnit);
        log_write("\tFree clusters: %lu (%lu bytes)\n",
                  pfsAllocateBuffer->cUnitAvail,
                  pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector * pfsAllocateBuffer->cUnitAvail);

        *clusterSize = pfsAllocateBuffer->cSectorUnit * pfsAllocateBuffer->cbSector;
    }

    free(pfsAllocateBuffer);

    pfsInfo = (PFSINFO)malloc(sizeof(FSINFO));

// 16 bit
#if(defined(__I86__) || defined(__i86__) || defined(_M_I86))
    rc = DosQFSInfo(driveNo, 2, (PBYTE)pfsInfo, sizeof(FSINFO));
#else // 32 bit
    rc = DosQueryFSInfo(driveNo, FSIL_VOLSER, (PBYTE)pfsInfo, sizeof(FSINFO));
#endif

    if(rc) log_write("Error %d requesting volume information.\n", rc);
    else
    {
        log_write("\tVolume label: %s\n", pfsInfo->vol.szVolLabel);
        log_write("\tVolume created on %d/%02d/%02d %02d:%02d:%02d\n",
                  pfsInfo->fdateCreation.year + 1980,
                  pfsInfo->fdateCreation.month - 1,
                  pfsInfo->fdateCreation.day,
                  pfsInfo->ftimeCreation.hours,
                  pfsInfo->ftimeCreation.minutes,
                  pfsInfo->ftimeCreation.twosecs * 2);
    }

    free(pfsInfo);
}

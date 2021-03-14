/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : dos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains DOS code

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

#include <dos.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "dos.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    char                 driveNo = path[0] - '@';
    struct diskfree_t    oldFreeSpace;
    struct diskfree_ex_t freeSpace;
    unsigned int         rc;

    memset(&oldFreeSpace, 0, sizeof(struct diskfree_t));
    memset(&freeSpace, 0, sizeof(struct diskfree_ex_t));

    if(driveNo > 32) driveNo -= 32;

    rc = _dos_getdiskfree_ex(driveNo, &freeSpace);

    if(rc)
    {
        if(errno == ENOSYS)
        {
            rc                          = _dos_getdiskfree(driveNo, &oldFreeSpace);
            freeSpace.sectorsPerCluster = oldFreeSpace.sectors_per_cluster;
            freeSpace.freeClusters      = oldFreeSpace.avail_clusters;
            freeSpace.bytesPerSector    = oldFreeSpace.bytes_per_sector;
            freeSpace.totalClusters     = oldFreeSpace.total_clusters;
        }
        else
        {
            printf("Error %d requesting volume information.\n", _doserrno);
            return;
        }
    }

    if(rc == 0)
    {
        printf("\tBytes per sector: %lu\n", freeSpace.bytesPerSector);
        printf("\tSectors per cluster: %lu (%lu bytes)\n",
               freeSpace.sectorsPerCluster,
               freeSpace.sectorsPerCluster * freeSpace.bytesPerSector);
        printf("\tClusters: %lu (%lu bytes)\n",
               freeSpace.totalClusters,
               freeSpace.sectorsPerCluster * freeSpace.bytesPerSector * freeSpace.totalClusters);
        printf("\tFree clusters: %lu (%lu bytes)\n",
               freeSpace.freeClusters,
               freeSpace.sectorsPerCluster * freeSpace.bytesPerSector * freeSpace.freeClusters);

        *clusterSize = freeSpace.sectorsPerCluster * freeSpace.bytesPerSector;
    }
}

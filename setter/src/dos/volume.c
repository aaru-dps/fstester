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

#if defined(__DOS__) || defined(MSDOS)

#include <direct.h>
#include <dos.h>
#include <i86.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WATCOM__)
#include <direct.h>
#elif defined(__DJGPP__)
#include <unistd.h>
#endif

#include "../include/consts.h"
#include "../include/defs.h"
#include "../include/dosos2.h"
#include "dos.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    union REGS        regs;
    struct SREGS      sregs;
    char              drivePath[4];
    char              driveNo = path[0] - '@';
    struct diskfree_t oldFreeSpace;
    Fat32FreeSpace*   freeSpace = malloc(sizeof(Fat32FreeSpace));

    memset(freeSpace, 0, sizeof(Fat32FreeSpace));

    if(driveNo > 32) driveNo -= 32;

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    regs.w.ax = 0x7303;
    sregs.ds  = FP_SEG(drivePath);
    regs.w.dx = FP_OFF(drivePath);
    sregs.es  = FP_SEG(freeSpace);
    regs.w.di = FP_OFF(freeSpace);
    regs.w.cx = sizeof(Fat32FreeSpace);

    int86x(0x21, &regs, &regs, &sregs);

    if(regs.h.al == 0 && !regs.w.cflag)
    {
        _dos_getdiskfree(driveNo, &oldFreeSpace);
        freeSpace->sectorsPerCluster = oldFreeSpace.sectors_per_cluster;
        freeSpace->freeClusters      = oldFreeSpace.avail_clusters;
        freeSpace->bytesPerSector    = oldFreeSpace.bytes_per_sector;
        freeSpace->totalClusters     = oldFreeSpace.total_clusters;
    }
    else if(regs.w.cflag)
    {
        printf("Error %d requesting volume information.\n", regs.w.ax);
        free(freeSpace);
        return;
    }

    if(!regs.w.cflag)
    {
        printf("\tBytes per sector: %lu\n", freeSpace->bytesPerSector);
        printf("\tSectors per cluster: %lu (%lu bytes)\n",
               freeSpace->sectorsPerCluster,
               freeSpace->sectorsPerCluster * freeSpace->bytesPerSector);
        printf("\tClusters: %lu (%lu bytes)\n",
               freeSpace->totalClusters,
               freeSpace->sectorsPerCluster * freeSpace->bytesPerSector * freeSpace->totalClusters);
        printf("\tFree clusters: %lu (%lu bytes)\n",
               freeSpace->freeClusters,
               freeSpace->sectorsPerCluster * freeSpace->bytesPerSector * freeSpace->freeClusters);

        *clusterSize = freeSpace->sectorsPerCluster * freeSpace->bytesPerSector;
    }
}

#endif

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

#include <eti.h>
#include <mint/dcntl.h>
#include <mint/mintbind.h>
#include <mint/osbind.h>
#include <mint/ostruct.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "../log.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    char           driveNo = path[0] - 'A';
    _BPB*          bpb;
    _DISKINFO      diskInfo;
    unsigned int   rc;
    char           xfsName[256];
    struct fs_info fsInfo;

    if(driveNo > 32) driveNo -= 32;

    bpb = Getbpb(driveNo);

    if(bpb == NULL)
    {
        log_write("Error %d requesting volume information.\n", rc);
        return;
    }

    log_write("\tBytes per sector: %lu\n", bpb->recsiz);
    log_write("\tSectors per cluster: %lu (%lu bytes)\n", bpb->clsiz, (int)bpb->clsiz * bpb->recsiz);
    log_write("\tClusters: %lu (%lu bytes)\n", bpb->numcl, (int)bpb->numcl * bpb->clsiz * bpb->recsiz);

    *clusterSize = bpb->clsiz * bpb->recsiz;

    memset(&diskInfo, 0, sizeof(_DISKINFO));

    rc = Dfree(&diskInfo, driveNo);

    if(rc == E_OK)
    {
        log_write(
            "\tFree clusters: %lu (%lu bytes)\n", diskInfo.b_free, (int)diskInfo.b_free * bpb->clsiz * bpb->recsiz);
    }

    memset(&fsInfo, 0, sizeof(struct fs_info));

    rc = Dcntl(FS_INFO, path, &fsInfo);

    if(rc == E_OK)
    {
        log_write("\tFilesystem name: %s", fsInfo.name);
        log_write("\tFilesystem version: %d.%02d", (fsInfo.version & 0xFFFF0000) >> 16, fsInfo.version & 0xFFFF);
        log_write("\tFilesystem type: %d (%s)", fsInfo.type, fsInfo.type_asc);
    }
    else
    {
        memset(xfsName, 0, 256);

        rc = Dcntl(MX_KER_XFSNAME, path, xfsName);

        if(rc == E_OK) log_write("\tFilesystem name: %s", xfsName);
        else
            log_write("\tFilesystem name: FAT");
    }
}

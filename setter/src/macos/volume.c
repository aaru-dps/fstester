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

#include <Files.h>
#include <Gestalt.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "../log.h"
#include "macos.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    OSErr        rc;
    Str255       str255;
    HVolumeParam hpb;
    XVolumeParam xpb;
    int32_t      gestaltResponse;
    int16_t      drvInfo;
    int16_t      refNum;
    uint64_t     totalBlocks;
    uint64_t     freeBlocks;
    uint32_t     crDate;
    uint32_t     lwDate;
    uint32_t     bkDate;
    uint16_t     fsId;
    uint64_t     totalBytes;
    uint64_t     freeBytes;
    int          hfsPlusApis = 0;
    int          bigVol      = 0;
    *clusterSize             = 0;

    snprintf((char*)str255, 255, "%s", path);

    rc = Gestalt(gestaltFSAttr, &gestaltResponse);
    if(!rc)
    {
        hfsPlusApis = (gestaltResponse & (1 << gestaltHasHFSPlusAPIs)) != 0;
        bigVol      = (gestaltResponse & (1 << gestaltFSSupports2TBVols)) != 0;
    }

    if(!bigVol)
    {
        hpb.ioNamePtr  = str255;
        hpb.ioVRefNum  = 0;
        hpb.ioVolIndex = -1;
        rc             = PBHGetVInfoSync((HParmBlkPtr)&hpb);
        if(rc)
        {
            log_write("Could not get volume information.\n");
            return;
        }
        drvInfo      = hpb.ioVDrvInfo;
        refNum       = hpb.ioVRefNum;
        totalBlocks  = hpb.ioVNmAlBlks;
        freeBlocks   = hpb.ioVFrBlk;
        crDate       = hpb.ioVCrDate;
        lwDate       = hpb.ioVLsMod;
        bkDate       = hpb.ioVBkUp;
        fsId         = hpb.ioVSigWord;
        *clusterSize = hpb.ioVAlBlkSiz;
        totalBytes   = totalBlocks * *clusterSize;
        freeBytes    = freeBlocks * *clusterSize;
        if(hpb.ioVFSID != 0) { fsId = hpb.ioVFSID; }
    }
    else
    {
        xpb.ioNamePtr  = str255;
        xpb.ioVRefNum  = 0;
        xpb.ioVolIndex = -1;
        rc             = PBXGetVolInfo((XVolumeParamPtr)&xpb, 0);
        if(rc)
        {
            log_write("Could not get volume information.\n");
            return;
        }

        // Because old compilers use a struct instead of a 64 bit integer
        memcpy(&totalBytes, &xpb.ioVTotalBytes, 8);
        memcpy(&freeBytes, &xpb.ioVFreeBytes, 8);

        drvInfo      = xpb.ioVDrvInfo;
        refNum       = xpb.ioVRefNum;
        totalBlocks  = totalBytes / xpb.ioVAlBlkSiz;
        freeBlocks   = freeBytes / xpb.ioVAlBlkSiz;
        crDate       = xpb.ioVCrDate;
        lwDate       = xpb.ioVLsMod;
        bkDate       = xpb.ioVBkUp;
        fsId         = xpb.ioVSigWord;
        *clusterSize = xpb.ioVAlBlkSiz;
        if(xpb.ioVFSID != 0) { fsId = xpb.ioVFSID; }
    }

    log_write("Volume information:\n");
    log_write("\tPath: %s\n", path);
    if(bigVol) { log_write("\tVolume supports up to 2Tb disks.\n"); }
    if(hfsPlusApis) { log_write("\tVolume supports HFS Plus APIs.\n"); }
    log_write("\tDrive number: %d\n", drvInfo);
    log_write("\tVolume number: %d\n", refNum);
    log_write("\tVolume name: %#s\n", str255);
    log_write("\t%llu allocation blocks in volume, %llu free\n", totalBlocks, freeBlocks);
    log_write("\t%llu bytes in volume, %llu free\n", totalBytes, freeBytes);
    log_write("\t%lu bytes per allocation block.\n", *clusterSize);
    log_write("\tVolume created on 0x%08lX\n", crDate);
    log_write("\tVolume last written on 0x%08lX\n", lwDate);
    log_write("\tVolume last backed up on 0x%08lX\n", bkDate);
    log_write("\tFilesystem type: ");
    switch(fsId)
    {
        case 0xD2D7: log_write("MFS\n"); break;
        case 0x4244: log_write("HFS\n"); break;
        case 0x482B: log_write("HFS Plus\n"); break;
        case 0x4147: log_write("ISO9660\n"); break;
        case 0x55DF: log_write("UDF\n"); break;
        case 0x4242: log_write("High Sierra\n"); break;
        case 0x4A48: log_write("Audio CD\n"); break;
        case 0x0100: log_write("ProDOS\n"); break;
        case 0x4953: log_write("FAT\n"); break;
        case 0x0017: log_write("UFS\n"); break;
        default: log_write("unknown id 0x%04X\n", fsId); break;
    }
}

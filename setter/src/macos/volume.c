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
#include <MacTypes.h>
#include <stdint.h>
#include <stdio.h>

#include "../include/defs.h"
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
        hfsPlusApis = (gestaltResponse & (1 << gestaltHasHFSPlusAPIs))!= 0;
        bigVol      = (gestaltResponse & (1 << gestaltFSSupports2TBVols))!=0;
    }

    if(!bigVol)
    {
        hpb.ioNamePtr  = str255;
        hpb.ioVRefNum  = 0;
        hpb.ioVolIndex = -1;
        rc             = PBHGetVInfoSync((HParmBlkPtr)&hpb);
        if(rc)
        {
            printf("Could not get volume information.\n");
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
            printf("Could not get volume information.\n");
            return;
        }
        drvInfo      = xpb.ioVDrvInfo;
        refNum       = xpb.ioVRefNum;
        totalBlocks  = xpb.ioVTotalBytes / xpb.ioVAlBlkSiz;
        freeBlocks   = xpb.ioVFreeBytes / xpb.ioVAlBlkSiz;
        crDate       = xpb.ioVCrDate;
        lwDate       = xpb.ioVLsMod;
        bkDate       = xpb.ioVBkUp;
        fsId         = xpb.ioVSigWord;
        *clusterSize = xpb.ioVAlBlkSiz;
        totalBytes   = xpb.ioVTotalBytes;
        freeBytes    = xpb.ioVFreeBytes;
        if(xpb.ioVFSID != 0) { fsId = xpb.ioVFSID; }
    }

    printf("Volume information:\n");
    printf("\tPath: %s\n", path);
    if(bigVol) { printf("\tVolume supports up to 2Tb disks.\n"); }
    if(hfsPlusApis) { printf("\tVolume supports HFS Plus APIs.\n"); }
    printf("\tDrive number: %d\n", drvInfo);
    printf("\tVolume number: %d\n", refNum);
    printf("\tVolume name: %#s\n", str255);
    printf("\t%llu allocation blocks in volume, %llu free\n", totalBlocks, freeBlocks);
    printf("\t%llu bytes in volume, %llu free\n", totalBytes, freeBytes);
    printf("\t%lu bytes per allocation block.\n", *clusterSize);
    printf("\tVolume created on 0x%08lX\n", crDate);
    printf("\tVolume last written on 0x%08lX\n", lwDate);
    printf("\tVolume last backed up on 0x%08lX\n", bkDate);
    printf("\tFilesystem type: ");
    switch(fsId)
    {
        case 0xD2D7: printf("MFS\n"); break;
        case 0x4244: printf("HFS\n"); break;
        case 0x482B: printf("HFS Plus\n"); break;
        case 0x4147: printf("ISO9660\n"); break;
        case 0x55DF: printf("UDF\n"); break;
        case 0x4242: printf("High Sierra\n"); break;
        case 0x4A48: printf("Audio CD\n"); break;
        case 0x0100: printf("ProDOS\n"); break;
        case 0x4953: printf("FAT\n"); break;
        default: printf("unknown id 0x%04X\n", fsId); break;
    }
}

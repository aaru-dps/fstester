/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : macos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains Mac OS code.

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

#if defined(macintosh)

#if defined(HAVE_ALIASES_H) || !defined(HAVE_MULTIVERSE_H)
#include <Aliases.h>
#endif

#if defined(HAVE_FILE_TYPES_AND_CREATORS_H) || !defined(HAVE_MULTIVERSE_H)
#include <FileTypesAndCreators.h>
#endif

#include <Files.h>
#include <Gestalt.h>
#include <MacTypes.h>
#include <Resources.h>
#include <TextUtils.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "macos.h"
#include "time.h"

void Timestamps(const char* path)
{
    OSErr        rc, wRc, cRc, tRc;
    Str255       str255;
    HVolumeParam hpb;
    int16_t      refNum;
    int16_t      refFile;
    int32_t      dirId;
    FInfo        finderInfo;
    int32_t      count;
    HFileInfo*   fpb;
    CInfoPBRec   cipbr;
    char           message[300];
    HParamBlockRec dirPB;
    int            i;

    snprintf((char*)str255, 255, "%s", path);
    hpb.ioNamePtr  = str255;
    hpb.ioVRefNum  = 0;
    hpb.ioVolIndex = -1;
    rc             = PBHGetVInfoSync((HParmBlkPtr)&hpb);
    if(rc)
    {
        printf("Could not get volume information.\n");
        return;
    }
    refNum = hpb.ioVRefNum;

    memset(&dirPB, 0, sizeof(HParamBlockRec));

    dirPB.fileParam.ioCompletion = 0;                     // Nothing, sync
    dirPB.fileParam.ioVRefNum    = refNum;                // Volume specification
    dirPB.fileParam.ioNamePtr    = (StringPtr) "\pTIMES"; // Directory name to create
    dirPB.fileParam.ioDirID      = 0;                     // ID of parent directory, 0 for root of volume

    rc = PBDirCreateSync(&dirPB);

    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    dirId = dirPB.fileParam.ioDirID;

    printf("Creating timestamped files.\n");

    for(i = 0; i < KNOWN_MAC_TIMES; i++)
    {
        memset(str255, 0, 256);
        memcpy(str255, mac_times[i].filename, strlen(mac_times[i].filename));

        rc = HCreate(refNum, dirId, str255, ostUnknown, ftGenericDocumentPC);

        if(!rc)
        {
            rc = HOpenDF(refNum, dirId, str255, 0, &refFile);

            if(!rc)
            {
                memset(&message, 0, 300);
                sprintf((char*)message, DATETIME_FORMAT, mac_times[i].message, mac_times[i].type);
                count = strlen(message);
                wRc   = FSWrite(refFile, &count, message);
                cRc   = FSClose(refFile);
            }

            memset(&cipbr, 0, sizeof(CInfoPBRec));
            fpb              = (HFileInfo*)&cipbr;
            fpb->ioVRefNum   = refNum;
            fpb->ioNamePtr   = str255;
            fpb->ioDirID     = dirId;
            fpb->ioFDirIndex = 0;
            PBGetCatInfoSync(&cipbr);

            fpb->ioFlCrDat = mac_times[i].creation;
            fpb->ioFlMdDat = mac_times[i].modification;
            fpb->ioFlBkDat = mac_times[i].backup;
            fpb->ioDirID   = dirId;
            tRc            = PBSetCatInfoSync(&cipbr);
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", str255, rc, wRc, cRc, tRc);
    }
}
#endif

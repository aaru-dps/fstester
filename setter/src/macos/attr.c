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

#if defined(HAVE_FILE_TYPES_AND_CREATORS_H) || !defined(HAVE_MULTIVERSE_H)
#include <FileTypesAndCreators.h>
#endif

#include <Files.h>
#include <MacTypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "attr.h"
#include "macos.h"

void FileAttributes(const char* path)
{
    OSErr        rc, wRc, cRc;
    Str255       str255;
    HVolumeParam hpb;
    int16_t      refNum;
    int16_t      refFile;
    int32_t      dirId;
    FInfo        finderInfo;
    int32_t        count;
    HParamBlockRec fpb;
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
    dirPB.fileParam.ioNamePtr    = (StringPtr) "\pATTRS"; // Directory name to create
    dirPB.fileParam.ioDirID      = 0;                     // ID of parent directory, 0 for root of volume

    rc = PBDirCreateSync(&dirPB);

    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    dirId = dirPB.fileParam.ioDirID;

    printf("Creating attribute files.\n");

    for(i = 0; i < KNOWN_MAC_ATTRS; i++)
    {
        memset(str255, 0, 256);
        memcpy(str255, mac_attrs[i].filename, strlen(mac_attrs[i].filename));

        memset(&finderInfo, 0, sizeof(FInfo));
        rc = HCreate(refNum, dirId, str255, ostUnknown, ftGenericDocumentPC);

        if(!rc)
        {
            rc = HOpenDF(refNum, dirId, str255, 0, &refFile);

            if(!rc)
            {
                memset(&fpb, 0, sizeof(HParamBlockRec));

                count = strlen(mac_attrs[i].contents);
                wRc   = FSWrite(refFile, &count, mac_attrs[i].contents);
                cRc   = FSClose(refFile);

                fpb.fileParam.ioVRefNum                 = refNum;
                fpb.fileParam.ioNamePtr                 = str255;
                fpb.fileParam.ioDirID                   = dirId;
                fpb.fileParam.ioFDirIndex               = 0;
                fpb.fileParam.ioFlFndrInfo.fdType       = mac_attrs[i].type;
                fpb.fileParam.ioFlFndrInfo.fdCreator    = mac_attrs[i].creator;
                fpb.fileParam.ioFlFndrInfo.fdFlags      = mac_attrs[i].flags;
                fpb.fileParam.ioFlFndrInfo.fdLocation.h = mac_attrs[i].location.h;
                fpb.fileParam.ioFlFndrInfo.fdLocation.v = mac_attrs[i].location.v;

                rc = PBHSetFInfoSync(&fpb);
            }
        }

        printf("\t%s: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
               mac_attrs[i].description,
               mac_attrs[i].filename,
               rc,
               wRc,
               cRc);
    }
}
#endif

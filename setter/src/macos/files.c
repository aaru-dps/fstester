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

#if defined(HAVE_FILE_TYPES_AND_CREATORS_H) || !defined(HAVE_MULTIVERSE_H)
#include <FileTypesAndCreators.h>
#endif

#include <Files.h>
#include <MacTypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "macos.h"

void MillionFiles(const char* path)
{
    OSErr          rc, wRc, cRc;
    Str255         str255;
    HVolumeParam   hpb;
    int16_t        refNum;
    int16_t        refFile;
    int32_t        dirId;
    FInfo          finderInfo;
    int32_t        count;
    char           filename[9];
    int            pos = 0;
    HParamBlockRec dirPB;

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

    dirPB.fileParam.ioCompletion = 0;                       // Nothing, sync
    dirPB.fileParam.ioVRefNum    = refNum;                  // Volume specification
    dirPB.fileParam.ioNamePtr    = (StringPtr) "\pMILLION"; // Directory name to create
    dirPB.fileParam.ioDirID      = 0;                       // ID of parent directory, 0 for root of volume

    rc = PBDirCreateSync(&dirPB);

    dirId = dirPB.fileParam.ioDirID;

    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    printf("Creating lots of files.\n");

    for(pos = 0; pos < 5000; pos++)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08d", pos);
        str255[0] = 8;
        memcpy(str255 + 1, filename, 8);

        rc = HCreate(refNum, dirId, str255, ostUnknown, ftGenericDocumentPC);

        if(rc) break;
    }

    printf("\tCreated %d files\n", pos);
}

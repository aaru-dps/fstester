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
#include <Resources.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "macos.h"
#include "rsrcfork.h"

static OSErr SaveResourceToNewFile(int16_t        vRefNum,
                                   int32_t        dirID,
                                   Str255         filename,
                                   ResType        type,
                                   int16_t        resId,
                                   Str255         resName,
                                   unsigned char* buffer,
                                   size_t         length)
{
    Handle  h;
    OSErr   rc;
    int16_t resRef;

    h = NewHandle(length);

    if(!h) return notEnoughMemoryErr;

    memcpy(*h, buffer, length);

    HCreateResFile(vRefNum, dirID, filename);

    resRef = HOpenResFile(vRefNum, dirID, filename, fsCurPerm);
    rc     = ResError();

    if(resRef == -1 || rc) return rc;

    UseResFile(resRef);

    AddResource(h, type, resId, resName);
    rc = ResError();

    CloseResFile(resRef);

    DisposeHandle(h);

    return rc;
}

void ResourceFork(const char* path)
{
    OSErr          rc, wRc, cRc, rRc, rRc2, rRc3;
    Str255         str255;
    HVolumeParam   hpb;
    int16_t        refNum;
    int16_t        refFile;
    int32_t        dirId;
    FInfo          finderInfo;
    int32_t        count;
    HParamBlockRec fpb;
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

    dirPB.fileParam.ioCompletion = 0;                    // Nothing, sync
    dirPB.fileParam.ioVRefNum    = refNum;               // Volume specification
    dirPB.fileParam.ioNamePtr    = (StringPtr) "\pRSRC"; // Directory name to create
    dirPB.fileParam.ioDirID      = 0;                    // ID of parent directory, 0 for root of volume

    rc = PBDirCreateSync(&dirPB);

    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    dirId = dirPB.fileParam.ioDirID;

    printf("Creating resource forks.\n");

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pICON", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rRc = SaveResourceToNewFile(refNum,
                                    dirId,
                                    "\pICON",
                                    rtIcons,
                                    -16455,
                                    "\pIcon resource",
                                    (unsigned char*)IcnsResource,
                                    sizeof(IcnsResource));
        rc  = HOpenDF(refNum, dirId, "\pICON", 0, &refFile);
        if(!rc)
        {
            memset(&fpb, 0, sizeof(HParamBlockRec));

            count = strlen(rsrcText);
            wRc   = FSWrite(refFile, &count, rsrcText);
            cRc   = FSClose(refFile);

            fpb.fileParam.ioVRefNum              = refNum;
            fpb.fileParam.ioNamePtr              = "\pICON";
            fpb.fileParam.ioDirID                = dirId;
            fpb.fileParam.ioFlFndrInfo.fdType    = ftGenericDocumentPC;
            fpb.fileParam.ioFlFndrInfo.fdCreator = ostAaru;
            fpb.fileParam.ioFlFndrInfo.fdFlags   = kHasCustomIcon;

            rc = PBHSetFInfoSync(&fpb);
        }
    }
    printf("\tFile with three items in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
           "ICON",
           rc,
           wRc,
           cRc,
           rRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPICT", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rRc = SaveResourceToNewFile(refNum,
                                    dirId,
                                    "\pPICT",
                                    ftPICTFile,
                                    29876,
                                    "\pPicture resource",
                                    (unsigned char*)PictResource,
                                    sizeof(PictResource));
        rc  = HOpenDF(refNum, dirId, "\pPICT", 0, &refFile);
        if(!rc)
        {
            memset(&fpb, 0, sizeof(HParamBlockRec));

            count                = strlen(rsrcText);
            wRc                  = FSWrite(refFile, &count, rsrcText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftPICTFile;
            finderInfo.fdCreator = ostAaru;

            fpb.fileParam.ioVRefNum              = refNum;
            fpb.fileParam.ioNamePtr              = "\pPICT";
            fpb.fileParam.ioDirID                = dirId;
            fpb.fileParam.ioFlFndrInfo.fdType    = ftPICTFile;
            fpb.fileParam.ioFlFndrInfo.fdCreator = ostAaru;

            rc = PBHSetFInfoSync(&fpb);
        }
    }
    printf("\tFile with three items in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
           "PICT",
           rc,
           wRc,
           cRc,
           rRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pVERSION", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rRc = SaveResourceToNewFile(refNum,
                                    dirId,
                                    "\pVERSION",
                                    rtVersion,
                                    1,
                                    "\pVersion resource",
                                    (unsigned char*)VersResource,
                                    sizeof(VersResource));
        rc  = HOpenDF(refNum, dirId, "\pVERSION", 0, &refFile);
        if(!rc)
        {
            memset(&fpb, 0, sizeof(HParamBlockRec));

            count = strlen(rsrcText);
            wRc   = FSWrite(refFile, &count, rsrcText);
            cRc   = FSClose(refFile);

            fpb.fileParam.ioVRefNum              = refNum;
            fpb.fileParam.ioNamePtr              = "\pVERSION";
            fpb.fileParam.ioDirID                = dirId;
            fpb.fileParam.ioFlFndrInfo.fdType    = ftGenericDocumentPC;
            fpb.fileParam.ioFlFndrInfo.fdCreator = ostAaru;

            rc = PBHSetFInfoSync(&fpb);
        }
    }
    printf("\tFile with three items in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
           "VERSION",
           rc,
           wRc,
           cRc,
           rRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pALL", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rRc  = SaveResourceToNewFile(refNum,
                                    dirId,
                                    "\pALL",
                                    rtIcons,
                                    -16455,
                                    "\pIcon resource",
                                    (unsigned char*)IcnsResource,
                                    sizeof(IcnsResource));
        rRc2 = SaveResourceToNewFile(refNum,
                                     dirId,
                                     "\pALL",
                                     ftPICTFile,
                                     29876,
                                     "\pPicture resource",
                                     (unsigned char*)PictResource,
                                     sizeof(PictResource));
        rRc3 = SaveResourceToNewFile(refNum,
                                     dirId,
                                     "\pALL",
                                     rtVersion,
                                     1,
                                     "\pVersion resource",
                                     (unsigned char*)VersResource,
                                     sizeof(VersResource));
        rc   = HOpenDF(refNum, dirId, "\pALL", 0, &refFile);
        if(!rc)
        {
            memset(&fpb, 0, sizeof(HParamBlockRec));

            count = strlen(rsrcText);
            wRc   = FSWrite(refFile, &count, rsrcText);
            cRc   = FSClose(refFile);

            fpb.fileParam.ioVRefNum              = refNum;
            fpb.fileParam.ioNamePtr              = "\pALL";
            fpb.fileParam.ioDirID                = dirId;
            fpb.fileParam.ioFlFndrInfo.fdType    = ftPICTFile;
            fpb.fileParam.ioFlFndrInfo.fdCreator = ostAaru;
            fpb.fileParam.ioFlFndrInfo.fdFlags   = kHasCustomIcon;

            rc = PBHSetFInfoSync(&fpb);
        }
    }
    printf("\tFile with three items in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d, rRc2 = "
           "%d, rRc3 = %d\n",
           "ALL",
           rc,
           wRc,
           cRc,
           rRc,
           rRc2,
           rRc3);
}
#endif

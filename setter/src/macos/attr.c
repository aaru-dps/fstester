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

void FileAttributes(const char* path)
{
    OSErr        rc, wRc, cRc;
    Str255       str255;
    HVolumeParam hpb;
    int16_t      refNum;
    int16_t      refFile;
    int32_t      dirId;
    FInfo        finderInfo;
    int32_t      count;
    HFileInfo*   fpb;
    CInfoPBRec   cipbr;

    snprintf((char*)str255, 255, "%s", path);
    hpb.ioNamePtr  = str255;
    hpb.ioVRefNum  = 0;
    hpb.ioVolIndex = -1;
    rc             = PBHGetVInfo((HParmBlkPtr)&hpb, 0);
    if(rc)
    {
        printf("Could not get volume information.\n");
        return;
    }
    refNum = hpb.ioVRefNum;

    rc = DirCreate(refNum, fsRtDirID, (unsigned char*)"\pATTRS", &dirId);
    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    printf("Creating attribute files.\n");

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pNONE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pNONE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(noAttributeText);
            wRc                  = FSWrite(refFile, &count, noAttributeText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            rc                   = HSetFInfo(refNum, dirId, "\pNONE", &finderInfo);
        }
    }
    printf("\tFile with no attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "NONE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pINDESK", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pINDESK", 0, &refFile);
        if(!rc)
        {
            count                = strlen(desktopText);
            wRc                  = FSWrite(refFile, &count, desktopText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kIsOnDesk;
            rc                   = HSetFInfo(refNum, dirId, "\pINDESK", &finderInfo);
        }
    }
    printf("\tFile is in desktop: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "INDESK", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pBROWN", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pBROWN", 0, &refFile);
        if(!rc)
        {
            count                = strlen(color2Text);
            wRc                  = FSWrite(refFile, &count, color2Text);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x02;
            rc                   = HSetFInfo(refNum, dirId, "\pBROWN", &finderInfo);
        }
    }
    printf("\tFile is colored brown: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "BROWN", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pGREEN", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pGREEN", 0, &refFile);
        if(!rc)
        {
            count                = strlen(color4Text);
            wRc                  = FSWrite(refFile, &count, color4Text);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x04;
            rc                   = HSetFInfo(refNum, dirId, "\pGREEN", &finderInfo);
        }
    }
    printf("\tFile is colored green: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "GREEN", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pLILAC", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pLILAC", 0, &refFile);
        if(!rc)
        {
            count                = strlen(color6Text);
            wRc                  = FSWrite(refFile, &count, color6Text);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x06;
            rc                   = HSetFInfo(refNum, dirId, "\pLILAC", &finderInfo);
        }
    }
    printf("\tFile is colored lilac: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "LILAC", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pBLUE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pBLUE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(color8Text);
            wRc                  = FSWrite(refFile, &count, color8Text);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x08;
            rc                   = HSetFInfo(refNum, dirId, "\pBLUE", &finderInfo);
        }
    }
    printf("\tFile is colored blue: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "BLUE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pMAGENTA", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMAGENTA", 0, &refFile);
        if(!rc)
        {
            count                = strlen(colorAText);
            wRc                  = FSWrite(refFile, &count, colorAText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x0A;
            rc                   = HSetFInfo(refNum, dirId, "\pMAGENTA", &finderInfo);
        }
    }
    printf("\tFile is colored magenta: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "MAGENTA", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pRED", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pRED", 0, &refFile);
        if(!rc)
        {
            count                = strlen(colorCText);
            wRc                  = FSWrite(refFile, &count, colorCText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x0C;
            rc                   = HSetFInfo(refNum, dirId, "\pRED", &finderInfo);
        }
    }
    printf("\tFile is colored red: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "RED", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pORANGE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pORANGE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(colorEText);
            wRc                  = FSWrite(refFile, &count, colorEText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0x0E;
            rc                   = HSetFInfo(refNum, dirId, "\pORANGE", &finderInfo);
        }
    }
    printf("\tFile is colored orange: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "ORANGE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pSWITCH", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pSWITCH", 0, &refFile);
        if(!rc)
        {
            count                = strlen(requireSwitchText);
            wRc                  = FSWrite(refFile, &count, requireSwitchText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kRequireSwitchLaunch;
            rc                   = HSetFInfo(refNum, dirId, "\pSWITCH", &finderInfo);
        }
    }
    printf("\tFile require switch launch: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "SWITCH", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pSHARED", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pSHARED", 0, &refFile);
        if(!rc)
        {
            count                = strlen(sharedText);
            wRc                  = FSWrite(refFile, &count, sharedText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kIsShared;
            rc                   = HSetFInfo(refNum, dirId, "\pSHARED", &finderInfo);
        }
    }
    printf("\tFile is shared: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "SHARED", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pNOINIT", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pNOINIT", 0, &refFile);
        if(!rc)
        {
            count                = strlen(noInitText);
            wRc                  = FSWrite(refFile, &count, noInitText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kHasNoINITs;
            rc                   = HSetFInfo(refNum, dirId, "\pNOINIT", &finderInfo);
        }
    }
    printf("\tFile has no INITs: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "NOINIT", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pINITED", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pINITED", 0, &refFile);
        if(!rc)
        {
            count                = strlen(initedText);
            wRc                  = FSWrite(refFile, &count, initedText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kHasBeenInited;
            rc                   = HSetFInfo(refNum, dirId, "\pINITED", &finderInfo);
        }
    }
    printf("\tFile has been INITed: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "INITED", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pAOCE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pAOCE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(aoceText);
            wRc                  = FSWrite(refFile, &count, aoceText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kAOCE;
            rc                   = HSetFInfo(refNum, dirId, "\pAOCE", &finderInfo);
        }
    }
    printf("\tFile with AOCE set: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "AOCE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pICON", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pICON", 0, &refFile);
        if(!rc)
        {
            count                = strlen(customIconText);
            wRc                  = FSWrite(refFile, &count, customIconText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kHasCustomIcon;
            rc                   = HSetFInfo(refNum, dirId, "\pICON", &finderInfo);
        }
    }
    printf("\tFile has custom icon (not really): name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "ICON", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pSTATIONERY", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pSTATIONERY", 0, &refFile);
        if(!rc)
        {
            count                = strlen(stationeryText);
            wRc                  = FSWrite(refFile, &count, stationeryText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kIsStationery;
            rc                   = HSetFInfo(refNum, dirId, "\pSTATIONERY", &finderInfo);
        }
    }
    printf("\tFile is stationery: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "STATIONERY", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pLOCKED", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pLOCKED", 0, &refFile);
        if(!rc)
        {
            count                = strlen(nameLockText);
            wRc                  = FSWrite(refFile, &count, nameLockText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kNameLocked;
            rc                   = HSetFInfo(refNum, dirId, "\pLOCKED", &finderInfo);
        }
    }
    printf("\tFile is locked: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "LOCKED", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pBUNDLE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pBUNDLE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(bundleText);
            wRc                  = FSWrite(refFile, &count, bundleText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kHasBundle;
            rc                   = HSetFInfo(refNum, dirId, "\pBUNDLE", &finderInfo);
        }
    }
    printf("\tFile has bundle (not really): name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "BUNDLE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pINVISIBLE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pINVISIBLE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(invisibleText);
            wRc                  = FSWrite(refFile, &count, invisibleText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kIsInvisible;
            rc                   = HSetFInfo(refNum, dirId, "\pINVISIBLE", &finderInfo);
        }
    }
    printf("\tFile is invisible: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "INVISIBLE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pALIAS", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pALIAS", 0, &refFile);
        if(!rc)
        {
            count                = strlen(aliasText);
            wRc                  = FSWrite(refFile, &count, aliasText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = kIsAlias;
            rc                   = HSetFInfo(refNum, dirId, "\pALIAS", &finderInfo);
        }
    }
    printf("\tFile is alias to nowhere: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "ALIAS", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pSIMPLE", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pSIMPLE", 0, &refFile);
        if(!rc)
        {
            count                = strlen(simpletextText);
            wRc                  = FSWrite(refFile, &count, simpletextText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostSimpleText;
            rc                   = HSetFInfo(refNum, dirId, "\pSIMPLE", &finderInfo);
        }
    }
    printf("\tFile with creator SimpleText: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "SIMPLE", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pAARU", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pAARU", 0, &refFile);
        if(!rc)
        {
            count                = strlen(aaruText);
            wRc                  = FSWrite(refFile, &count, aaruText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostAaru;
            rc                   = HSetFInfo(refNum, dirId, "\pAARU", &finderInfo);
        }
    }
    printf("\tFile with creator 'aaru': name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "AARU", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_M32_M32", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_M32_M32", 0, &refFile);
        if(!rc)
        {
            count = strlen(pos_m32_m32);
            wRc   = FSWrite(refFile, &count, pos_m32_m32);
            cRc   = FSClose(refFile);

            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = -32768;
            finderInfo.fdLocation.v = -32768;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_M32_M32", &finderInfo);
        }
    }
    printf("\tFile with position -32768,-32768: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "POS_M32_M32",
           rc,
           wRc,
           cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_32_32", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_32_32", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_32_32);
            wRc                     = FSWrite(refFile, &count, pos_32_32);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = 32767;
            finderInfo.fdLocation.v = 32767;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_32_32", &finderInfo);
        }
    }
    printf("\tFile with position 32767,32767: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_32_32", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_M1_M1", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_M1_M1", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_m1_m1);
            wRc                     = FSWrite(refFile, &count, pos_m1_m1);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = -1024;
            finderInfo.fdLocation.v = -1024;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_M1_M1", &finderInfo);
        }
    }
    printf("\tFile with position -1024,-1024: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_M1_M1", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_M1_M32", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_M1_M32", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_m1_m32);
            wRc                     = FSWrite(refFile, &count, pos_m1_m32);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = -1024;
            finderInfo.fdLocation.v = -32768;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_M1_M32", &finderInfo);
        }
    }
    printf(
        "\tFile with position -1024,-32768: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_M1_M32", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_M1_32", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_M1_32", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_m1_32);
            wRc                     = FSWrite(refFile, &count, pos_m1_32);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = -1024;
            finderInfo.fdLocation.v = 32767;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_M1_32", &finderInfo);
        }
    }
    printf("\tFile with position -1024,32767: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_M1_32", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_M1_1", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_M1_1", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_m1_1);
            wRc                     = FSWrite(refFile, &count, pos_m1_1);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = -1024;
            finderInfo.fdLocation.v = 1024;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_M1_1", &finderInfo);
        }
    }
    printf("\tFile with position -1024,1024: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_M1_1", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_1_M1", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_1_M1", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_1_m1);
            wRc                     = FSWrite(refFile, &count, pos_1_m1);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = 1024;
            finderInfo.fdLocation.v = -1024;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_1_M1", &finderInfo);
        }
    }
    printf("\tFile with position 1024,-1024: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_1_M1", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_1_M32", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_1_M32", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_1_m32);
            wRc                     = FSWrite(refFile, &count, pos_1_m32);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = 1024;
            finderInfo.fdLocation.v = -32768;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_1_M32", &finderInfo);
        }
    }
    printf("\tFile with position 1024,-32768: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_1_M32", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_1_32", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_1_32", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_1_32);
            wRc                     = FSWrite(refFile, &count, pos_1_32);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = 1024;
            finderInfo.fdLocation.v = 32767;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_1_32", &finderInfo);
        }
    }
    printf("\tFile with position 1024,32767: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_1_32", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pPOS_1_1", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pPOS_1_1", 0, &refFile);
        if(!rc)
        {
            count                   = strlen(pos_1_1);
            wRc                     = FSWrite(refFile, &count, pos_1_1);
            cRc                     = FSClose(refFile);
            finderInfo.fdType       = ftGenericDocumentPC;
            finderInfo.fdCreator    = ostUnknown;
            finderInfo.fdLocation.h = 1024;
            finderInfo.fdLocation.v = 1024;
            rc                      = HSetFInfo(refNum, dirId, "\pPOS_1_1", &finderInfo);
        }
    }
    printf("\tFile with position 1024,1024: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "POS_1_1", rc, wRc, cRc);

    memset(&finderInfo, 0, sizeof(FInfo));
    rc = HCreate(refNum, dirId, "\pALL", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pALL", 0, &refFile);
        if(!rc)
        {
            count                = strlen(allText);
            wRc                  = FSWrite(refFile, &count, allText);
            cRc                  = FSClose(refFile);
            finderInfo.fdType    = ftGenericDocumentPC;
            finderInfo.fdCreator = ostUnknown;
            finderInfo.fdFlags   = 0xFFFF;
            rc                   = HSetFInfo(refNum, dirId, "\pALL", &finderInfo);
        }
    }
    printf("\tFile has all flags bits set: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "ALL", rc, wRc, cRc);
}
#endif

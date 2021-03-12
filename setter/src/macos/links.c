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

#include <FileTypesAndCreators.h>
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

static pascal OSErr

    CreateAliasFile(const FSSpec* targetFile, const FSSpec* aliasFile, OSType fileCreator, OSType fileType)
{
    short       rsrcID;
    short       aliasRefnum;
    FInfo       finf;
    OSErr       err;
    AliasHandle alias;

    FSpCreateResFile(aliasFile, fileCreator, fileType, 0);
    err = ResError();
    if(err != noErr) return err;

    err = NewAlias(aliasFile, targetFile, &alias);
    if(err != noErr || alias == NULL) return err;

    aliasRefnum = FSpOpenResFile(aliasFile, fsRdWrPerm);

    AddResource((Handle)alias, rAliasType, 0, "\pAaru alias");
    err = ResError();

    CloseResFile(aliasRefnum);
    FSpGetFInfo(aliasFile, &finf);

    finf.fdCreator = fileCreator;
    finf.fdType    = fileType;
    finf.fdFlags |= 0x8000;
    finf.fdFlags &= (~0x0100);

    FSpSetFInfo(aliasFile, &finf);

    return err;
}

void Links(const char* path)
{
    int32_t      gestaltResponse;
    OSErr        rc, wRc, cRc, oRc, aRc;
    Str255       str255;
    HVolumeParam hpb;
    int16_t      refNum;
    int16_t      refFile;
    int32_t      dirId;
    char         filename[9];
    int          pos = 0;
    FSSpec       targetSpec, aliasSpec;
    int32_t      count;

    rc = Gestalt(gestaltAliasMgrAttr, &gestaltResponse);
    if(rc || !(gestaltResponse & (1 << gestaltAliasMgrPresent)))
    {
        printf("Alias Manager not present, cannot create aliases.\n");
        return;
    }

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

    rc = DirCreate(refNum, fsRtDirID, (unsigned char*)"\pLINKS", &dirId);
    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    printf("Creating aliases.\n");

    for(pos = 0; pos < 64; pos++)
    {
        memset(&filename, 0, 9);
        sprintf((char*)filename, "TARGET%02d", pos);
        str255[0] = 8;
        memcpy(str255 + 1, filename, 8);

        rc = HCreate(refNum, dirId, str255, ostSimpleText, ftGenericDocumentPC);

        if(rc) break;

        oRc = HOpenDF(refNum, dirId, str255, 0, &refFile);
        if(oRc) break;

        count = strlen(targetText);
        wRc   = FSWrite(refFile, &count, targetText);
        cRc   = FSClose(refFile);

        memset(&targetSpec, 0, sizeof(FSSpec));
        targetSpec.vRefNum = refNum;
        targetSpec.parID   = dirId;
        targetSpec.name[0] = 8;
        memcpy(targetSpec.name + 1, filename, 8);

        memset(&filename, 0, 9);
        sprintf((char*)filename, "ALIAS_%02d", pos);
        memset(&aliasSpec, 0, sizeof(FSSpec));
        aliasSpec.vRefNum = refNum;
        aliasSpec.parID   = dirId;
        aliasSpec.name[0] = 8;
        memcpy(aliasSpec.name + 1, filename, 8);

        aRc = CreateAliasFile(&targetSpec, &aliasSpec, ostSimpleText, ftGenericDocumentPC);

        if(aRc) break;
    }

    printf("pos = %d, rc = %d, wRc = %d, cRc = %d, oRc = %d, aRc = %d\n", pos, rc, wRc, cRc, oRc, aRc);
}
#endif
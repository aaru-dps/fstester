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

void Filenames(const char* path)
{
    OSErr        rc, wRc, cRc;
    Str255       str255;
    HVolumeParam hpb;
    int16_t      refNum;
    int16_t      refFile;
    int32_t      dirId;
    FInfo        finderInfo;
    int32_t      count;
    char         message[300];
    int          pos = 0;

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

    rc = DirCreate(refNum, fsRtDirID, (unsigned char*)"\pFILENAME", &dirId);
    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        count = strlen(filenames[pos]);
        memset(&str255, 0, sizeof(Str255));
        if(count > 255) { continue; }
        str255[0] = (char)count;
        memcpy(str255 + 1, filenames[pos], count);

        rc = HCreate(refNum, dirId, str255, ostUnknown, ftGenericDocumentPC);
        if(!rc)
        {
            rc = HOpenDF(refNum, dirId, str255, 0, &refFile);
            if(!rc)
            {
                memset(&message, 0, 300);
                sprintf((char*)message, FILENAME_FORMAT, filenames[pos]);
                count = strlen(message);
                wRc   = FSWrite(refFile, &count, message);
                cRc   = FSClose(refFile);
            }
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}
#endif

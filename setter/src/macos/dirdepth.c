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
#include <MacTypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "../log.h"
#include "macos.h"

void DirectoryDepth(const char* path)
{
    OSErr          rc;
    Str255         str255;
    HVolumeParam   hpb;
    int16_t        refNum;
    int32_t        dirId;
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
        log_write("Could not get volume information.\n");
        return;
    }
    refNum = hpb.ioVRefNum;

    memset(&dirPB, 0, sizeof(HParamBlockRec));

    dirPB.fileParam.ioCompletion = 0;                     // Nothing, sync
    dirPB.fileParam.ioVRefNum    = refNum;                // Volume specification
    dirPB.fileParam.ioNamePtr    = (StringPtr) "\pDEPTH"; // Directory name to create
    dirPB.fileParam.ioDirID      = 0;                     // ID of parent directory, 0 for root of volume

    rc = PBDirCreateSync(&dirPB);

    if(rc)
    {
        log_write("Error %d creating working directory.\n", rc);
        return;
    }

    log_write("Creating deepest directory tree.\n");

    while(!rc)
    {
        memset(filename, 0, 9);
        sprintf(filename, "%08d", pos);
        str255[0] = 8;
        memcpy(str255 + 1, filename, 8);

        dirId = dirPB.fileParam.ioDirID;

        memset(&dirPB, 0, sizeof(HParamBlockRec));

        dirPB.fileParam.ioCompletion = 0;      // Nothing, sync
        dirPB.fileParam.ioVRefNum    = refNum; // Volume specification
        dirPB.fileParam.ioNamePtr    = str255; // Directory name to create
        dirPB.fileParam.ioDirID      = dirId;  // ID of parent directory, 0 for root of volume

        rc = PBDirCreateSync(&dirPB);

        pos++;
        /* Mac OS has no limit, but it will crash because the catalog is single threaded */
        if(pos == 500) break;
    }

    log_write("\tCreated %d levels of directory hierarchy\n", pos);
}

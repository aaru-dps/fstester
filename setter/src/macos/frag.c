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

void Fragmentation(const char* path, size_t clusterSize)
{
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    OSErr          rc, wRc, cRc;
    Str255         str255;
    HVolumeParam   hpb;
    int16_t        refNum;
    int16_t        refFile;
    int32_t        dirId;
    int32_t        count;
    long           i;

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

    rc = DirCreate(refNum, fsRtDirID, (unsigned char*)"\pFRAGS", &dirId);
    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    rc = HCreate(refNum, dirId, "\pHALFCLST", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pHALFCLST", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(halfCluster);
            memset(buffer, 0, halfCluster);

            for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = halfCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    rc = HCreate(refNum, dirId, "\pQUARCLST", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pQUARCLST", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(quarterCluster);
            memset(buffer, 0, quarterCluster);

            for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = quarterCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    rc = HCreate(refNum, dirId, "\pTWOCLST", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pTWOCLST", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(twoCluster);
            memset(buffer, 0, twoCluster);

            for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = twoCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    rc = HCreate(refNum, dirId, "\pTRQTCLST", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pTRQTCLST", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(threeQuartersCluster);
            memset(buffer, 0, threeQuartersCluster);

            for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = threeQuartersCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TRQTCLST",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    rc = HCreate(refNum, dirId, "\pTWOQCLST", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pTWOQCLST", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(twoAndThreeQuartCluster);
            memset(buffer, 0, twoAndThreeQuartCluster);

            for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = twoAndThreeQuartCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TWTQCLST",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);

    rc = HCreate(refNum, dirId, "\pTWO1", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pTWO1", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(twoCluster);
            memset(buffer, 0, twoCluster);

            for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = twoCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    rc = HCreate(refNum, dirId, "\pTWO2", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pTWO2", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(twoCluster);
            memset(buffer, 0, twoCluster);

            for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = twoCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    rc = HCreate(refNum, dirId, "\pTWO3", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pTWO3", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(twoCluster);
            memset(buffer, 0, twoCluster);

            for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = twoCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tDeleting \"TWO2\".\n");
    rc = HDelete(refNum, dirId, "\pTWO2");

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    rc = HCreate(refNum, dirId, "\pFRAGTHRQ", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pFRAGTHRQ", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(threeQuartersCluster);
            memset(buffer, 0, threeQuartersCluster);

            for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = threeQuartersCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tDeleting \"TWO1\".\n");
    rc = HDelete(refNum, dirId, "\pTWO1");
    printf("\tDeleting \"TWO3\".\n");
    rc = HDelete(refNum, dirId, "\pTWO3");

    rc = HCreate(refNum, dirId, "\pFRAGSIXQ", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pFRAGSIXQ", 0, &refFile);
        if(!rc)
        {
            buffer = malloc(twoAndThreeQuartCluster);
            memset(buffer, 0, twoAndThreeQuartCluster);

            for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

            count = twoAndThreeQuartCluster;
            wRc   = FSWrite(refFile, &count, buffer);
            cRc   = FSClose(refFile);
            free(buffer);
        }
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "FRAGSIXQ",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);
}

#endif

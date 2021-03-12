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
    char         message[300];

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

    rc = DirCreate(refNum, fsRtDirID, (unsigned char*)"\pTIMES", &dirId);
    if(rc)
    {
        printf("Error %d creating working directory.\n", rc);
        return;
    }

    printf("Creating timestamped files.\n");

    rc = HCreate(refNum, dirId, "\pMAXCTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMAXCTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MAXDATETIME, "creation");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMAXCTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = MAXTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXCTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMAXMTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMAXMTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MAXDATETIME, "modification");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMAXMTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = MAXTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXMTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMAXBTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMAXBTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MAXDATETIME, "backup");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMAXBTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = MAXTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXBTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMINCTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMINCTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MINDATETIME, "creation");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMINCTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = MINTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINCTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMINMTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMINMTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MINDATETIME, "modification");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMINMTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = MINTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINMTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMINBTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMINBTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MINDATETIME, "backup");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMINBTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = MINTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINBTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY2KCTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY2KCTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y2KDATETIME, "creation");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY2KCTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = Y2KTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KCTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY2KMTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY2KMTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y2KDATETIME, "modification");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY2KMTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = Y2KTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KMTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY2KBTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY2KBTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y2KDATETIME, "backup");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY2KBTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = Y2KTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KBTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY1KCTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY1KCTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "creation");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY1KCTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = Y1KTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KCTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY1KMTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY1KMTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "modification");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY1KMTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = Y1KTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KMTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY1KBTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY1KBTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "backup");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY1KBTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = Y1KTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KBTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMAXTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMAXTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MAXDATETIME, "all");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMAXTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = MAXTIMESTAMP;
        fpb->ioFlMdDat = MAXTIMESTAMP;
        fpb->ioFlBkDat = MAXTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pMINTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pMINTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, MINDATETIME, "all");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pMINTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = MINTIMESTAMP;
        fpb->ioFlMdDat = MINTIMESTAMP;
        fpb->ioFlBkDat = MINTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pNOTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pNOTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, NONDATETIME, "all");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pNOTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = NONTIMESTAMP;
        fpb->ioFlMdDat = NONTIMESTAMP;
        fpb->ioFlBkDat = NONTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "NOTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY2KTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY2KTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y2KDATETIME, "all");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY2KTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = Y2KTIMESTAMP;
        fpb->ioFlMdDat = Y2KTIMESTAMP;
        fpb->ioFlBkDat = Y2KTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KTIME", rc, wRc, cRc, tRc);

    rc = HCreate(refNum, dirId, "\pY1KTIME", ostUnknown, ftGenericDocumentPC);
    if(!rc)
    {
        rc = HOpenDF(refNum, dirId, "\pY1KTIME", 0, &refFile);
        if(!rc)
        {
            memset(&message, 0, 300);
            sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "all");
            count = strlen(message);
            wRc   = FSWrite(refFile, &count, message);
            cRc   = FSClose(refFile);
        }
        memset(&cipbr, 0, sizeof(CInfoPBRec));
        fpb              = (HFileInfo*)&cipbr;
        fpb->ioVRefNum   = refNum;
        fpb->ioNamePtr   = "\pY1KTIME";
        fpb->ioDirID     = dirId;
        fpb->ioFDirIndex = 0;
        PBGetCatInfoSync(&cipbr);

        fpb->ioFlCrDat = Y1KTIMESTAMP;
        fpb->ioFlMdDat = Y1KTIMESTAMP;
        fpb->ioFlBkDat = Y1KTIMESTAMP;
        fpb->ioDirID   = dirId;
        tRc            = PBSetCatInfoSync(&cipbr);
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KTIME", rc, wRc, cRc, tRc);
}
#endif

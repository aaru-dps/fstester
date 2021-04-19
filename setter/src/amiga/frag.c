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

#include <proto/dos.h>
#include <stdlib.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"

void Fragmentation(const char* path, size_t clusterSize)
{
    BPTR           pathLock;
    BPTR           dirLock;
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    long           i;
    int            ret;
    BPTR           h;
    int            rc, wRc, cRc;

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "FRAGS");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Writing fragmented files:\n");

    h   = Open((CONST_STRPTR) "HALFCLST", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, halfCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "QUARCLST", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, quarterCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write(
        "\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "TWOCLST", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, twoCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "TRQTCLST", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, threeQuartersCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "TRQTCLST",
              threeQuartersCluster,
              rc,
              wRc,
              cRc);

    h   = Open((CONST_STRPTR) "TWTQCLST", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, twoAndThreeQuartCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "TWTQCLST",
              twoAndThreeQuartCluster,
              rc,
              wRc,
              cRc);

    h   = Open((CONST_STRPTR) "TWO1", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, twoCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "TWO2", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, twoCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "TWO3", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, twoCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tDeleting \"TWO2\".\n");
    ret = DeleteFile((CONST_STRPTR) "TWO2");
    if(!ret) rc = IoErr();

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "FRAGTHRQ", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, threeQuartersCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tDeleting \"TWO1\".\n");
    ret = DeleteFile((CONST_STRPTR) "TWO1");
    if(!ret) rc = IoErr();
    log_write("\tDeleting \"TWO3\".\n");
    ret = DeleteFile((CONST_STRPTR) "TWO3");
    if(!ret) rc = IoErr();

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "FRAGTHRQ",
              threeQuartersCluster,
              rc,
              wRc,
              cRc);

    h   = Open((CONST_STRPTR) "FRAGSIXQ", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = Write(h, buffer, twoAndThreeQuartCluster);
        if(ret < 0) wRc = IoErr();

        ret = Close(h);
        if(!ret) cRc = IoErr();
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "FRAGSIXQ",
              twoAndThreeQuartCluster,
              rc,
              wRc,
              cRc);
}

/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : frag.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains common implementations for UNIX family and compatibles

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

#if defined(unix) || defined(UNIX) || defined(__unix) || defined(__unix__) || defined(__UNIX__)

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/consts.h"
#include "../include/defs.h"

void Fragmentation(const char* path, size_t clusterSize)
{
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    long           i;
    int            ret;
    FILE*          h;
    int            rc, wRc, cRc;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("FRAGS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("FRAGS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Writing fragmented files:\n");

    h   = fopen("HALFCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, halfCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    h   = fopen("QUARCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, quarterCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    h   = fopen("TWOCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    h   = fopen("TRQTCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, threeQuartersCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TRQTCLST",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = fopen("TWTQCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoAndThreeQuartCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TWTQCLST",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);

    h   = fopen("TWO1", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    h   = fopen("TWO2", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    h   = fopen("TWO3", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tDeleting \"TWO2\".\n");
    ret = unlink("TWO2");
    if(!ret) { rc = errno; }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    h   = fopen("FRAGTHRQ", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, threeQuartersCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tDeleting \"TWO1\".\n");
    ret = unlink("TWO1");
    if(!ret) { rc = errno; }
    printf("\tDeleting \"TWO3\".\n");
    ret = unlink("TWO3");
    if(!ret) { rc = errno; }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "FRAGTHRQ",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = fopen("FRAGSIXQ", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoAndThreeQuartCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "FRAGSIXQ",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);
}

#endif

/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : dos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains DOS code

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

#if defined(__DOS__) || defined(MSDOS)

#include <direct.h>
#include <dos.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __WATCOMC__
#include <i86.h>
#elif defined(__DJGPP__)
#include <unistd.h>
#endif

#include "../include/consts.h"
#include "../include/defs.h"
#include "../include/dosos2.h"
#include "dos.h"

void Fragmentation(const char* path, size_t clusterSize)
{
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    char           driveNo = path[0] - '@';
    int            rc = 0, wRc = 0, cRc = 0;
    unsigned       total, actionTaken = 0;
    int            handle;
    long           i;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = mkdir("FRAGS");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = chdir("FRAGS");

    rc = _dos_creatnew("HALFCLST", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, halfCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    rc = _dos_creatnew("QUARCLST", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, quarterCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    rc = _dos_creatnew("TWOCLST", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, twoCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    rc = _dos_creatnew("TRQTCLST", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, threeQuartersCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TRQTCLST",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    rc = _dos_creatnew("TWTQCLST", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, twoAndThreeQuartCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TWTQCLST",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);

    rc = _dos_creatnew("TWO1", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, twoCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    rc = _dos_creatnew("TWO2", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, twoCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    rc = _dos_creatnew("TWO3", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, twoCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tDeleting \"TWO2\".\n");
    rc = unlink("TWO2");

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    rc = _dos_creatnew("FRAGTHRQ", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, threeQuartersCluster, &actionTaken);
        cRc = _dos_close(handle);
        free(buffer);
    }

    printf("\tDeleting \"TWO1\".\n");
    rc = unlink("TWO1");
    printf("\tDeleting \"TWO3\".\n");
    rc = unlink("TWO3");

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "FRAGTHRQ",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    rc = _dos_creatnew("FRAGSIXQ", _A_NORMAL, &handle);
    if(!rc)
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = _dos_write(handle, buffer, twoAndThreeQuartCluster, &actionTaken);
        cRc = _dos_close(handle);
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

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

#include <eti.h>
#include <mint/osbind.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"

void Fragmentation(const char* path, size_t clusterSize)
{
    unsigned int   halfCluster             = clusterSize / 2;
    unsigned int   quarterCluster          = clusterSize / 4;
    unsigned int   twoCluster              = clusterSize * 2;
    unsigned int   threeQuartersCluster    = halfCluster + quarterCluster;
    unsigned int   twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char* buffer;
    char           driveNo = path[0] - 'A';
    unsigned int   rc, wRc = 0, cRc = 0;
    int            handle;
    long           i;

    if(driveNo >= 32) driveNo -= 32;

    Dsetdrv(driveNo);
    Dsetpath("\\");

    rc = Dcreate("FRAGS");

    if(rc != E_OK)
    {
        log_write("Cannot create working directory.\n");
        return;
    }

    Dsetpath("FRAGS");

    handle = Fcreate("HALFCLST", 0);
    if(rc > 0)
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, halfCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    rc = Fcreate("QUARCLST", 0);
    if(rc > 0)
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, quarterCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write(
        "\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    rc = Fcreate("TWOCLST", 0);
    if(rc > 0)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, twoCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    rc = Fcreate("TRQTCLST", 0);
    if(rc > 0)
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, threeQuartersCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "TRQTCLST",
              threeQuartersCluster,
              rc,
              wRc,
              cRc);

    rc = Fcreate("TWTQCLST", 0);
    if(rc > 0)
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, twoAndThreeQuartCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "TWTQCLST",
              twoAndThreeQuartCluster,
              rc,
              wRc,
              cRc);

    rc = Fcreate("TWO1", 0);
    if(rc > 0)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, twoCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    rc = Fcreate("TWO2", 0);
    if(rc > 0)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, twoCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    rc = Fcreate("TWO3", 0);
    if(rc > 0)
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, twoCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tDeleting \"TWO2\".\n");
    rc = Fdelete("TWO2");

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    rc = Fcreate("FRAGTHRQ", 0);
    if(rc > 0)
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, threeQuartersCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tDeleting \"TWO1\".\n");
    Fdelete("TWO1");
    log_write("\tDeleting \"TWO3\".\n");
    rc = Fdelete("TWO3");

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "FRAGTHRQ",
              threeQuartersCluster,
              rc,
              wRc,
              cRc);

    rc = Fcreate("FRAGSIXQ", 0);
    if(rc > 0)
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        wRc = Fwrite(handle, twoAndThreeQuartCluster, buffer);
        cRc = Fclose(handle);
        free(buffer);
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
              "FRAGSIXQ",
              twoAndThreeQuartCluster,
              rc,
              wRc,
              cRc);
}

/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : perms.c
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
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/defs.h"

void FilePermissions(const char* path)
{
    int   ret;
    FILE* file;
    int   rc;
    int   cRc;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("PERMS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("PERMS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating attributes files.\n");

    file = fopen("NONE", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with no permissions.\n");
        fclose(file);
        cRc = chmod("NONE", 0);
    }
    printf("\tFile with no permissions: name = \"%s\", rc = %d, cRc = %d\n", "NONE", rc, cRc);

    file = fopen("04000", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with set-user-ID.\n");
        fclose(file);
        cRc = chmod("04000", 04000);
    }
    printf("\tFile with set-user-ID: name = \"%s\", rc = %d, cRc = %d\n", "04000", rc, cRc);

    file = fopen("02000", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with set-group-ID.\n");
        fclose(file);
        cRc = chmod("02000", 02000);
    }
    printf("\tFile with set-group-ID: name = \"%s\", rc = %d, cRc = %d\n", "02000", rc, cRc);

    file = fopen("01000", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with sticky bit.\n");
        fclose(file);
        cRc = chmod("01000", 01000);
    }
    printf("\tFile with sticky bit: name = \"%s\", rc = %d, cRc = %d\n", "01000", rc, cRc);

    file = fopen("00400", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with read by owner.\n");
        fclose(file);
        cRc = chmod("00400", 00400);
    }
    printf("\tFile with read by owner: name = \"%s\", rc = %d, cRc = %d\n", "00400", rc, cRc);

    file = fopen("00200", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with write by owner.\n");
        fclose(file);
        cRc = chmod("00200", 00200);
    }
    printf("\tFile with write by owner: name = \"%s\", rc = %d, cRc = %d\n", "00200", rc, cRc);

    file = fopen("00100", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with execute by owner.\n");
        fclose(file);
        cRc = chmod("00100", 00100);
    }
    printf("\tFile with execute by owner: name = \"%s\", rc = %d, cRc = %d\n", "00100", rc, cRc);

    file = fopen("00040", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with read by group.\n");
        fclose(file);
        cRc = chmod("00040", 00040);
    }
    printf("\tFile with read by group: name = \"%s\", rc = %d, cRc = %d\n", "00040", rc, cRc);

    file = fopen("00020", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with write by group.\n");
        fclose(file);
        cRc = chmod("00020", 00020);
    }
    printf("\tFile with write by group: name = \"%s\", rc = %d, cRc = %d\n", "00020", rc, cRc);

    file = fopen("00010", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with execute by group.\n");
        fclose(file);
        cRc = chmod("00010", 00010);
    }
    printf("\tFile with execute by group: name = \"%s\", rc = %d, cRc = %d\n", "00010", rc, cRc);

    file = fopen("00004", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with read by others.\n");
        fclose(file);
        cRc = chmod("00004", 00004);
    }
    printf("\tFile with read by others: name = \"%s\", rc = %d, cRc = %d\n", "00004", rc, cRc);

    file = fopen("00002", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with write by others.\n");
        fclose(file);
        cRc = chmod("00002", 00002);
    }
    printf("\tFile with write by others: name = \"%s\", rc = %d, cRc = %d\n", "00002", rc, cRc);

    file = fopen("00001", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with execute by others.\n");
        fclose(file);
        cRc = chmod("00001", 00001);
    }
    printf("\tFile with execute by others: name = \"%s\", rc = %d, cRc = %d\n", "00001", rc, cRc);
}

#endif

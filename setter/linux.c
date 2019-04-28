/****************************************************************************
The Disc Image Chef
-----------------------------------------------------------------------------

Filename       : linux.c
Author(s)      : Natalia Portillo

Component      : fstester.setter

--[ Description ] -----------------------------------------------------------

Contains Linux implementations

--[ License ] ---------------------------------------------------------------
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as
     published by the Free Software Foundation, either version 3 of the
     License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warraty of
     MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
Copyright (C) 2011-2018 Natalia Portillo
*****************************************************************************/

#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)

#include "consts.h"
#define _GNU_SOURCE
#include "linux.h"

#include <errno.h>
#include <fcntl.h>
#include <features.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#if((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 3)) || (__GLIBC__ > 2)
#include <sys/xattr.h>
#endif

void LinuxExtendedAttributes(const char *path)
{
#if((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 3)) || (__GLIBC__ > 2)
    int   ret;
    FILE *file;
    int   rc;
    int   cRc;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("XATTRS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("XATTRS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating files with extended attributes.\n");

    rc   = 0;
    cRc  = 0;
    file = fopen("com.ibm.os2.comment", "w+");
    if(file == NULL)
        rc = errno;
    else
    {
        fprintf(file, "This file has an extended attribute called \"com.ibm.os2.comment\" that is 72 bytes long.\n");
        fclose(file);
        ret = setxattr("com.ibm.os2.comment", "user.com.ibm.os2.comment", CommentsEA, 72, XATTR_CREATE);

        if(ret) cRc = errno;
    }
    printf("\tFile with an extended attribute called \"com.ibm.os2.comment\", rc = %d, cRc = %d\n", rc, cRc);

    rc   = 0;
    cRc  = 0;
    file = fopen("com.ibm.os2.icon", "w+");
    if(file == NULL)
        rc = errno;
    else
    {
        fprintf(file, "This file has an extended attribute called \"com.ibm.os2.icon\" that is 3516 bytes long.\n");
        fclose(file);
        ret = setxattr("com.ibm.os2.icon", "user.com.ibm.os2.icon", IconEA, 3516, XATTR_CREATE);

        if(ret) cRc = errno;
    }
    printf("\tFile with an extended attribute called \"com.ibm.os2.icon\", rc = %d, cRc = %d\n", rc, cRc);
#endif
}

void LinuxSparse(const char *path)
{
    int            ret;
    int            rc, wRc, cRc, zRc;
    FILE *         h;
    unsigned char *buffer;
    int            i;
    int            fd;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("SPARSE", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("SPARSE");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating sparse files.\n");

    h   = fopen("SMALL", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    zRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(4096 * 3);
        memset(buffer, 0, 4096 * 3);

        for(i = 0; i < 4096 * 3; i += CLAUNIA_SIZE)
        {
            ret = fwrite(clauniaBytes, CLAUNIA_SIZE, 1, h);
            if(ret < 0)
            {
                wRc = errno;
                break;
            }
        }

        fd  = fileno(h);
        ret = fallocate(fd, FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE, 4096, 8192);
        if(ret) { zRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d, sRc = %d\n",
           "SMALL",
           4096 * 3,
           rc,
           wRc,
           cRc,
           zRc);

    h   = fopen("BIG", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    zRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(4096 * 30);
        memset(buffer, 0, 4096 * 30);

        for(i = 0; i < 4096 * 30; i += CLAUNIA_SIZE)
        {
            ret = fwrite(clauniaBytes, CLAUNIA_SIZE, 1, h);
            if(ret < 0)
            {
                wRc = errno;
                break;
            }
        }

        fd  = fileno(h);
        ret = fallocate(fd, FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE, 32768, 81920);
        if(ret) { zRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d, sRc = %d\n",
           "BIG",
           4096 * 30,
           rc,
           wRc,
           cRc,
           zRc);
}

#endif
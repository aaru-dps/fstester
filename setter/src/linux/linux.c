/****************************************************************************
Aaru Data Preservation Suite
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
Copyright (C) 2011-2021 Natalia Portillo
*****************************************************************************/

#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)

#include "../consts.h"
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <features.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linux.h"

#include <linux/fs.h>
#include <sys/stat.h>
#include <sys/types.h>

#if((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 3)) || (__GLIBC__ > 2)
#include <sys/ioctl.h>
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

void LinuxFileAttributes(const char *path)
{
    int   ret;
    int   fd;
    FILE *h;
    int   rc;
    int   wRc;
    int   sRc;
    int   cRc;
    int   attr;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("ATTRS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("ATTRS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating files with different flags (attributes).\n");

    h    = fopen("APPEND", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_APPEND_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("APPEND");
        }
        else
        {
            ret = fprintf(h, "This file is now append only");
            if(ret < 1)
            {
                wRc = errno;
                unlink("APPEND");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with append only flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("COMPRESS", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_COMPR_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("COMPRESS");
        }
        else
        {
            ret = fprintf(h, "This file is now compressed");
            if(ret < 1)
            {
                wRc = errno;
                unlink("COMPRESS");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with compressed flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("IMMUTABLE", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_IMMUTABLE_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("IMMUTABLE");
        }
        else
        {
            ret = fprintf(h, "This file is now immutable");
            if(ret < 1)
            {
                wRc = errno;
                unlink("IMMUTABLE");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with immutable flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("JOURNALED", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_JOURNAL_DATA_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("JOURNALED");
        }
        else
        {
            ret = fprintf(h, "This file is now journaled");
            if(ret < 1)
            {
                wRc = errno;
                unlink("JOURNALED");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with journaled flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("NOATIME", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_NOATIME_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("NOATIME");
        }
        else
        {
            ret = fprintf(h, "This file is now noatime");
            if(ret < 1)
            {
                wRc = errno;
                unlink("NOATIME");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with noatime flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("NOCOW", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_NOCOW_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("NOCOW");
        }
        else
        {
            ret = fprintf(h, "This file is now not copy on write");
            if(ret < 1)
            {
                wRc = errno;
                unlink("NOCOW");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with no copy on write flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("NODUMP", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_NODUMP_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("NODUMP");
        }
        else
        {
            ret = fprintf(h, "This file is now not dumpable");
            if(ret < 1)
            {
                wRc = errno;
                unlink("NODUMP");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with no dump flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("NOTAIL", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_NOTAIL_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("NOTAIL");
        }
        else
        {
            ret = fprintf(h, "This file is now not tailed");
            if(ret < 1)
            {
                wRc = errno;
                unlink("NOTAIL");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with no tail flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("PROJECTINHERIT", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_PROJINHERIT_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("PROJECTINHERIT");
        }
        else
        {
            ret = fprintf(h, "This file is now inheriting project id");
            if(ret < 1)
            {
                wRc = errno;
                unlink("PROJECTINHERIT");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with project inherit flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("SECUREDELETION", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_SECRM_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("SECUREDELETION");
        }
        else
        {
            ret = fprintf(h, "This file is now secure deletable");
            if(ret < 1)
            {
                wRc = errno;
                unlink("SECUREDELETION");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with secure delete flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("SYNC", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_SYNC_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("SYNC");
        }
        else
        {
            ret = fprintf(h, "This file is now synchronous");
            if(ret < 1)
            {
                wRc = errno;
                unlink("SYNC");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with synchronous flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);

    h    = fopen("UNREMOVABLE", "w+");
    rc   = 0;
    wRc  = 0;
    sRc  = 0;
    cRc  = 0;
    attr = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        attr |= FS_UNRM_FL;
        fd  = fileno(h);
        ret = ioctl(fd, FS_IOC_SETFLAGS, &attr);

        if(ret)
        {
            sRc = errno;
            unlink("UNREMOVABLE");
        }
        else
        {
            ret = fprintf(h, "This file is now marked for undeletion");
            if(ret < 1)
            {
                wRc = errno;
                unlink("UNREMOVABLE");
            }
        }

        ret = fclose(h);
        if(ret) { cRc = errno; }
    }
    printf("\tFile with undeletion flag, rc = %d, wRc = %d, sRc = %d, cRc = %d\n", rc, wRc, sRc, cRc);
}

#endif
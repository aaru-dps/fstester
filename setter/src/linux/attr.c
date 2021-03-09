/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : linux.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains Linux implementations

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

#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)

#include <errno.h>
#include <linux/fs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "linux.h"

void LinuxFileAttributes(const char* path)
{
    int   ret;
    int   fd;
    FILE* h;
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
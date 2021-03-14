/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : time.c
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

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

#include "../include/defs.h"
#include "unix.h"

void Timestamps(const char* path)
{
    char           message[300];
    int            ret;
    time_t         ftLastAccessTime;
    time_t         ftLastWriteTime;
    FILE*          h;
    int            rc, wRc, cRc, tRc;
    struct utimbuf times;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("TIMES", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("TIMES");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating timestamped files.\n");

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MAXATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, MAXDATETIME, "access");
        times.actime = MAXTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MAXATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MAXMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, MAXDATETIME, "modification");
        times.modtime = MAXTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MAXMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MINATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, MINDATETIME, "access");
        times.actime = MINTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MINATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MINMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, MINDATETIME, "modification");
        times.modtime = MINTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MINMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y1KATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "access");
        times.actime = Y1KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y1KATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y1KMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "modification");
        times.modtime = Y1KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y1KMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y2KATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, Y2KDATETIME, "access");
        times.actime = Y2KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y2KATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y2KMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, Y1KDATETIME, "modification");
        times.modtime = Y2KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y2KMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("LESSATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, LESSDATETIME, "access");
        times.actime = LESSTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("LESSATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "LESSATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("LESSMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char*)message, DATETIME_FORMAT, LESSDATETIME, "modification");
        times.modtime = LESSTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("LESSMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "LESSMTIME", rc, wRc, cRc, tRc);
}

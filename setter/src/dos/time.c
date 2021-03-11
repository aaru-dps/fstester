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
#include <i86.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WATCOM__)
#include <direct.h>
#elif defined(__DJGPP__)
#include <unistd.h>
#endif

#include "../include/consts.h"
#include "../include/defs.h"
#include "../include/dosos2.h"
#include "dos.h"

#define DATETIME_FORMAT "This file is dated %04d/%02d/%02d %02d:%02d:%02d for %s\n"

void Timestamps(const char* path)
{
    char           driveNo = path[0] - '@';
    int            rc = 0, wRc = 0, cRc = 0, tRc = 0;
    unsigned       actionTaken, total;
    int            handle;
    char           message[300];
    union REGS     regs;
    unsigned short maxtime = 0xBF7D;
    unsigned short maxdate = 0xFF9F;
    unsigned short y1kdate = 0x2621;
    unsigned short y2kdate = 0x2821;
    unsigned short mindate = 0x0021;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = mkdir("TIMES");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = chdir("TIMES");

    printf("Creating timestamped files.\n");

    rc = _dos_creatnew("MAXCTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(maxdate),
                MONTH(maxdate),
                DAY(maxdate),
                HOUR(maxtime),
                MINUTE(maxtime),
                SECOND(maxtime),
                "creation");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = maxtime;
        regs.w.dx = maxdate;
        regs.w.ax = 0x5707;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXCTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("MINCTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(mindate),
                MONTH(mindate),
                DAY(mindate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "creation");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = mindate;
        regs.w.ax = 0x5707;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINCTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("Y19CTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(y1kdate),
                MONTH(y1kdate),
                DAY(y1kdate),
                HOUR(maxtime),
                MINUTE(maxtime),
                SECOND(maxtime),
                "creation");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = maxtime;
        regs.w.dx = y1kdate;
        regs.w.ax = 0x5707;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19CTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("Y2KCTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(y2kdate),
                MONTH(y2kdate),
                DAY(y2kdate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "creation");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = y2kdate;
        regs.w.ax = 0x5707;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19CTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("MAXWTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(maxdate),
                MONTH(maxdate),
                DAY(maxdate),
                HOUR(maxtime),
                MINUTE(maxtime),
                SECOND(maxtime),
                "last written");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = maxtime;
        regs.w.dx = maxdate;
        regs.w.ax = 0x5701;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXWTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("MINWTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(mindate),
                MONTH(mindate),
                DAY(mindate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "last written");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = mindate;
        regs.w.ax = 0x5701;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINWTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("Y19WTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(y1kdate),
                MONTH(y1kdate),
                DAY(y1kdate),
                HOUR(maxtime),
                MINUTE(maxtime),
                SECOND(maxtime),
                "last written");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = maxtime;
        regs.w.dx = y1kdate;
        regs.w.ax = 0x5701;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19WTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("Y2KWTIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(y2kdate),
                MONTH(y2kdate),
                DAY(y2kdate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "last written");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = y2kdate;
        regs.w.ax = 0x5701;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KWTIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("MAXATIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(maxdate),
                MONTH(maxdate),
                DAY(maxdate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "last access");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = maxdate;
        regs.w.ax = 0x5705;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXATIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("MINATIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(mindate),
                MONTH(mindate),
                DAY(mindate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "last access");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = mindate;
        regs.w.ax = 0x5705;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINATIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("Y19ATIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(y1kdate),
                MONTH(y1kdate),
                DAY(y1kdate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "last access");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = y1kdate;
        regs.w.ax = 0x5705;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y19ATIME", rc, wRc, cRc, tRc);

    rc = _dos_creatnew("Y2KATIME", _A_NORMAL, &handle);

    if(!rc)
    {
        memset(&message, 0, 300);
        sprintf(&message,
                DATETIME_FORMAT,
                YEAR(y2kdate),
                MONTH(y2kdate),
                DAY(y2kdate),
                HOUR(0),
                MINUTE(0),
                SECOND(0),
                "last access");

        wRc = _dos_write(handle, &message, strlen(message), &actionTaken);
        memset(&regs, 0, sizeof(regs));
        regs.w.bx = handle;
        regs.w.cx = 0;
        regs.w.dx = y2kdate;
        regs.w.ax = 0x5705;
        int86(0x21, &regs, &regs);
        tRc = regs.w.ax;
        cRc = _dos_close(handle);
    }

    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KATIME", rc, wRc, cRc, tRc);
}

#endif

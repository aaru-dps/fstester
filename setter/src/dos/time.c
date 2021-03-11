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

#include <dos.h>
#include <stdio.h>
#include <string.h>

#if defined(__WATCOM__)
#include <direct.h>
#include <i86.h>
#elif defined(__DJGPP__)
#include <unistd.h>
#endif

#include "../include/defs.h"
#include "dos.h"
#include "time.h"

void Timestamps(const char* path)
{
    char           driveNo = path[0] - '@';
    unsigned int            rc, wRc = 0, cRc = 0, tRc = 0;
    unsigned       actionTaken, total;
    int            handle;
    char           message[300];
    union REGS     regs;
    int i;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = __dos_mkdir("TIMES");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = chdir("TIMES");

    printf("Creating timestamped files.\n");

    for(i = 0; i < KNOWN_DOS_TIMES; i++)
    {
        rc = _dos_creatnew(dos_times[i].filename, _A_NORMAL, &handle);

        if(!rc)
        {
            memset(message, 0, 300);
            sprintf(message,
                    DATETIME_FORMAT,
                    YEAR(dos_times[i].date),
                    MONTH(dos_times[i].date),
                    DAY(dos_times[i].date),
                    HOUR(dos_times[i].time),
                    MINUTE(dos_times[i].time),
                    SECOND(dos_times[i].time),
                    dos_times[i].definition);

            wRc = _dos_write(handle, message, strlen(message), &actionTaken);
            memset(&regs, 0, sizeof(regs));
            regs.w.bx = handle;
            regs.w.cx = dos_times[i].time;
            regs.w.dx = dos_times[i].date;
            regs.w.ax = dos_times[i].function;
            int86(0x21, &regs, &regs);
            tRc = regs.w.ax;
            cRc = _dos_close(handle);
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", dos_times[i].filename, rc, wRc, cRc, tRc);
    }
}

#endif

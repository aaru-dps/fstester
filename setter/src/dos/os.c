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

void GetOsInfo()
{
    union REGS    regs;
    unsigned char major, minor;

    regs.w.ax = 0x3306;

    int86(0x21, &regs, &regs);

    if(regs.h.al == 0xFF || (regs.w.ax == 0x1 && regs.w.cflag))
    {
        memset(&regs, 0, sizeof(regs));
        regs.w.ax = 0x3000;
        int86(0x21, &regs, &regs);
        major = regs.h.al;
        minor = regs.h.ah;
    }
    else
    {
        major = regs.h.bl;
        minor = regs.h.bh;
    }

    if(major == 10 || major == 20)
    {
        printf("Will not run under OS/2. Exiting...\n");
        exit(1);
    }

    if(major == 5 && minor == 50)
    {
        printf("Will not run under Windows NT. Exiting...\n");
        exit(1);
    }

    if(major == 0) major = 1;

    printf("OS information:\n");
    printf("\tRunning under DOS %d.%d\n", major, minor);
}

#endif

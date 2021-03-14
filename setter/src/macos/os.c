/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : macos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains Mac OS code.

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

#include <Gestalt.h>
#include <MacTypes.h>
#include <stdint.h>
#include <stdio.h>

#include "../include/defs.h"
#include "macos.h"

void GetOsInfo()
{
    int32_t gestaltResponse;
    OSErr   rc;

    printf("OS information:\n");

    rc = Gestalt(gestaltAUXVersion, &gestaltResponse);
    if(!rc) { printf("Running under A/UX version 0x%08lX\n", gestaltResponse); }
    else
    {
        rc = Gestalt(gestaltSystemVersion, &gestaltResponse);
        if(rc) { printf("Could not get Mac OS version.\n"); }
        else
        {
            printf("Running under Mac OS version %ld.%ld.%ld",
                   (gestaltResponse & 0xF00) >> 8,
                   (gestaltResponse & 0xF0) >> 4,
                   gestaltResponse & 0xF);
            rc = Gestalt(gestaltSysArchitecture, &gestaltResponse);
            if(!rc)
            {
                printf(" for ");
                switch(gestaltResponse)
                {
                    case 1: printf("Motorola 68k architecture."); break;
                    case 2: printf("PowerPC architecture."); break;
                    case 3: printf("x86 architecture."); break;
                    default: printf("unknown architecture code %ld.", gestaltResponse); break;
                }
            }
            printf("\n");
        }
        rc = Gestalt(gestaltMacOSCompatibilityBoxAttr, &gestaltResponse);
        if(!rc) { printf("Running under Classic.\n"); }
    }
}

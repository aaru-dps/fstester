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

#include <Gestalt.h>
#include <stdio.h>

#include "../include/defs.h"
#include "../log.h"
#include "macos.h"

void GetOsInfo()
{
    int32_t gestaltResponse;
    OSErr   rc;

    log_write("OS information:\n");

    rc = Gestalt(gestaltAUXVersion, &gestaltResponse);
    if(!rc) log_write("Running under A/UX version %d.%d\n", (gestaltResponse & 0xFF00) >> 8, gestaltResponse & 0xFF);
    else
    {
        rc = Gestalt(gestaltSystemVersion, &gestaltResponse);
        if(rc) { log_write("Could not get Mac OS version.\n"); }
        else
        {
            log_write("Running under Mac OS version %ld.%ld.%ld",
                      (gestaltResponse & 0xF00) >> 8,
                      (gestaltResponse & 0xF0) >> 4,
                      gestaltResponse & 0xF);
            rc = Gestalt(gestaltSysArchitecture, &gestaltResponse);
            if(!rc)
            {
                log_write(" for ");
                switch(gestaltResponse)
                {
                    case 1: log_write("Motorola 68k architecture."); break;
                    case 2: log_write("PowerPC architecture."); break;
                    case 3: log_write("x86 architecture."); break;
                    default: log_write("unknown architecture code %ld.", gestaltResponse); break;
                }
            }
            log_write("\n");
        }
        rc = Gestalt(gestaltMacOSCompatibilityBoxAttr, &gestaltResponse);
        if(!rc) { log_write("Running under Classic.\n"); }
    }
}

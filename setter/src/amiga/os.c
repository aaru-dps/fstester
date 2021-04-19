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

#include <exec/execbase.h>
#include <proto/exec.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "../log.h"

void GetOsInfo()
{
    BOOL            amithlon = FALSE;
    struct Node*    node;
    char            version[16];
    char            system[16];
    struct Library* VersionBase;
    struct Library* ArosBase;
    int             error = -1;

    memset(version, 0, 16);
    memset(system, 0, 16);

    strncpy(system, "AmigaOS", 7);

    switch(SysBase->LibNode.lib_Version)
    {
        case 27: strncpy(version, "0.7", 3); break;
        case 29: strncpy(version, "0.9", 3); break;
        case 30: strncpy(version, "1.0", 3); break;
        case 31:
        case 32: strncpy(version, "1.1", 3); break;
        case 33: strncpy(version, "1.2", 3); break;
        case 34:
        case 35: strncpy(version, "1.3", 3); break;
        case 36: strncpy(version, "2.0", 3); break;
        case 37: strncpy(version, "2.04", 4); break;
        case 38: strncpy(version, "2.1", 3); break;
        case 39: strncpy(version, "3.0", 3); break;
        case 40:
        case 41: strncpy(version, "3.1", 3); break;
        case 43: strncpy(version, "3.2", 3); break;
        case 44: strncpy(version, "3.5", 3); break;
        case 45: strncpy(version, "3.9", 3); break;
        case 50:
        case 51:
        case 52: strncpy(version, "4.0", 3); break;
        case 53: strncpy(version, "4.1", 3); break;
        default: strncpy(version, "unknown version", 15); break;
    }

    Disable();
    for(node = SysBase->ResourceList.lh_Head; node->ln_Succ != NULL; node = node->ln_Succ)
    {
        if(strcmp(node->ln_Name, "amithlon.resource") == 0)
        {
            amithlon = TRUE;
            break;
        }
    }
    Enable();

    ArosBase = OpenLibrary((CONST_STRPTR) "aros.library", 0);
    if(ArosBase)
    {
        memset(system, 0, 16);
        memset(version, 0, 16);
        strncpy(system, "AROS", 4);
        snprintf(version, 16, "%d.%d", ArosBase->lib_Version, ArosBase->lib_Revision);
    }

    // TODO: Detect MorphOS

    log_write("OS information:\n");

    log_write("Running under %s %s\n", system, version);
    log_write("KickStart v%d.%d\n", SysBase->LibNode.lib_Version, SysBase->LibNode.lib_Revision);

    VersionBase = OpenLibrary((CONST_STRPTR) "version.library", 0);
    if(VersionBase)
    {
        log_write("Workbench v%d.%d\n", VersionBase->lib_Version, VersionBase->lib_Revision);

        CloseLibrary(VersionBase);
    }

    if(amithlon) log_write("Running under Amithlon\n");
}

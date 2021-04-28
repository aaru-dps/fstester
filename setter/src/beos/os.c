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

// BeOS R3: BeOS, release 1, version 9
// BeOS R4.5.2: BeOS, release 4.5, version 1000009
// Haiku: Haiku, release 1, version hrevXXXXXX+<date>

#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

#include "../include/defs.h"
#include "../log.h"

#if !defined(_SYS_NAMELEN)
#define _SYS_NAMELEN 32
#endif

void GetOsInfo()
{
    struct utsname buf;
    int            ret;
    char           version[_SYS_NAMELEN];
    char*          version_date;

    memset(version, 0, _SYS_NAMELEN);

    ret = uname(&buf);

    if(ret)
    {
        log_write("Error %d retrieving OS information.\n", errno);
        return;
    }

    if(strncmp(buf.sysname, "BeOS", 4) == 0)
    {
        if(strncmp(buf.release, "1", 1) == 0)
        {
            if(strncmp(buf.version, "9", 1) == 0) log_write("Running under BeOS R3\n");
            else
                log_write("Running under BeOS DR%s\n", buf.version);
        }
        else
            log_write("Running under BeOS R%s\n", buf.release);
    }
    else if(strncmp(buf.sysname, "Haiku", 5) == 0)
    {
        strncpy(version, buf.version, _SYS_NAMELEN);
        version_date  = strchr(version, '+');
        *version_date = '\0';

        log_write("Running under Haiku %s\n", buf.version);
    }
    else
    {
        log_write("OS information:\n");
        log_write("\tOS name: %s\n", buf.sysname);
        log_write("\tRelease: %s\n", buf.release);
        log_write("\tVersion: %s\n", buf.version);
        log_write("\tMachine: %s\n", buf.machine);
    }
}

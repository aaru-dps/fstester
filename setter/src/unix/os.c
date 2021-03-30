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

#if defined(__APPLE__) && defined(__MACH__)
#include "../darwin/darwin.h"
#else
#include <errno.h>
#include <sys/utsname.h>

#include "../log.h"
#endif

#include "../include/defs.h"

void GetOsInfo()
{
#if defined(__APPLE__) && defined(__MACH__)
    DarwinGetOsInfo();
#else
    struct utsname buf;
    int            ret;

    ret = uname(&buf);

    if(ret)
    {
        log_write("Error %d retrieving OS information.\n", errno);
        return;
    }

    log_write("OS information:\n");
    log_write("\tOS name: %s\n", buf.sysname);
    log_write("\tRelease: %s\n", buf.release);
    log_write("\tVersion: %s\n", buf.version);
    log_write("\tMachine: %s\n", buf.machine);
#endif
}

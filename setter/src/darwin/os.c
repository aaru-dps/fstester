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

#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/utsname.h>

#include "../include/defs.h"
#include "../log.h"

void DarwinGetOsInfo()
{
    struct utsname buf;
    int            ret;
    struct stat finder;

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
}

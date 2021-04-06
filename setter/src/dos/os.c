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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WATCOM__)
#include <i86.h>
#endif

#include "../include/defs.h"
#include "../log.h"
#include "dosuname.h"

void GetOsInfo()
{
    struct dosuname_version_t dosuname_version;

    memset(&dosuname_version, 0, sizeof(struct dosuname_version_t));

    getdosver(&dosuname_version);

    switch(dosuname_version.flavor)
    {
        case DOS_FLAVOR_UNKNOWN:
            log_write("OS information:\n");
            log_write("\tRunning under DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_MSDOS:
            log_write("OS information:\n");
            log_write("\tRunning under MS-DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_PCDOS:
            log_write("OS information:\n");
            log_write("\tRunning under PC-DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_DRDOS:
            log_write("OS information:\n");
            log_write("\tRunning under DR-DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_FREEDOS:
            log_write("OS information:\n");
            log_write("\tRunning under FreeDOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_WIN95:
        case DOS_FLAVOR_WIN9X:
        case DOS_FLAVOR_WINME: log_write("Will not run under Windows 9x. Exiting...\n"); exit(1);
        case DOS_FLAVOR_WINNT: log_write("Will not run under Windows NT. Exiting...\n"); exit(1);
        case DOS_FLAVOR_OS2: log_write("Will not run under OS/2. Exiting...\n"); exit(1);
        case DOS_FLAVOR_PTSDOS:
            log_write("OS information:\n");
            log_write("\tRunning under PTS-DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_RXDOS:
            log_write("OS information:\n");
            log_write("\tRunning under RxDOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_CONCURRENTDOS:
            log_write("OS information:\n");
            log_write("\tRunning under Concurrent DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_NOVELLDOS:
            log_write("OS information:\n");
            log_write("\tRunning under Novell DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
        case DOS_FLAVOR_MSPCDOS:
            log_write("OS information:\n");
            log_write("\tRunning under MS-DOS or PC-DOS %d.%d\n", dosuname_version.major, dosuname_version.minor);
            break;
    }
}

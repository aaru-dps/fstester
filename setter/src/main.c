/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : main.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains global definitions

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

#include <stddef.h>
#include <stdio.h>

#include "main.h"

#include "include/defs.h"

#if defined(macintosh) && defined(__MWERKS__)
#include <SIOUX.h>
#include <console.h>
#endif

int main(int argc, char** argv)
{
    size_t clusterSize = 0;

#if defined(macintosh) && defined(__MWERKS__)
    argc = ccommand(&argv);
#endif

    printf("Aaru Filesystem Tester (Setter) %s\n", AARU_FSTESTER_VERSION);
    printf("%s\n", AARU_COPYRIGHT);

    printf("Running in %s (%s)\n", OS_NAME, OS_ARCH);
    printf("\n");

    if(argc != 2)
    {
        printf("Usage %s <path>\n", argv[0]);
        return -1;
    }

    GetOsInfo();
    GetVolumeInfo(argv[1], &clusterSize);
    FileAttributes(argv[1]);
    FilePermissions(argv[1]);
    ExtendedAttributes(argv[1]);
    ResourceFork(argv[1]);
    Filenames(argv[1]);
    Timestamps(argv[1]);
    Links(argv[1]);
    DirectoryDepth(argv[1]);
    Fragmentation(argv[1], clusterSize);
    Sparse(argv[1]);
    MillionFiles(argv[1]);
    DeleteFiles(argv[1]);
    GetVolumeInfo(argv[1], &clusterSize);

    return 0;
}

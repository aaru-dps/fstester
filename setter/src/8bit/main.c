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

#include "../main.h"

#include "../include/defs.h"

#ifdef USE_FOLDERS
#define NO_DISKS 3
#define DISK_NAMES_TAIL " and \"DEPTH\","
#else
#define NO_DISKS 2
#define DISK_NAMES_TAIL ","
#endif

#ifdef __APPLE2__
#include <apple2_filetype.h>
#endif

int main(int argc, char** argv)
{
    int c;

    // Set ProDOS filetype to TEXT
#ifdef __APPLE2__
    _filetype = PRODOS_T_TXT;
#endif

    printf("Aaru Filesystem Tester (Setter)\n%s\n", AARU_FSTESTER_VERSION);
    printf("%s\n", AARU_COPYRIGHT);
    printf("Running in %s (%s)\n", OS_NAME, OS_ARCH);
    printf("\n");

    // Limit output to 40 columns
    printf("This software needs %d disks labeled\n", NO_DISKS);
    printf("\"FILES\", \"FILENAME\"%s\n", DISK_NAMES_TAIL);
    printf("to be inserted into the drive where\n");
    printf("this disk is now.\n");
    printf("Press the Y key to continue\n");
    printf("any other key exists.\n");

    c = getchar();

    if(c != 'Y' && c != 'y') return 1;

    MillionFiles("");
    Filenames("");
    DirectoryDepth("");

    printf("Press any key to exit.\n");

    getchar();

    return 0;
}

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

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

#include "include/defs.h"
#include "log.h"

#if defined(macintosh) && defined(__MWERKS__)
#include <SIOUX.h>
#include <console.h>
#endif

int main(int argc, char** argv)
{
    size_t clusterSize = 0;
    int    i;
    int    quiet  = 0;
    int    log    = 0;
    char*  target = NULL;

#if defined(macintosh) && defined(__MWERKS__)
    argc = ccommand(&argv);
#endif

    log_write("Aaru Filesystem Tester (Setter) %s\n", AARU_FSTESTER_VERSION);
    log_write("%s\n", AARU_COPYRIGHT);

    for(i = 1; i < argc; i++)
    {
        if(strncmp(argv[i], "--log", 5) == 0 || strncmp(argv[i], "-l", 2) == 0) log = 1;
        else if(strncmp(argv[i], "--quiet", 7) == 0 || strncmp(argv[i], "-q", 2) == 0)
            quiet = 1;
        else if(argv[i][0] == '-')
        {
            fprintf(stderr, "Unknown parameter %s.\n", argv[i]);
            fprintf(stderr, "Usage %s [--log] [--quiet] <path>\n", argv[0]);
            return -1;
        }
        else if(target != NULL)
        {
            fprintf(stderr, "Cannot set more than one target.\n");
            fprintf(stderr, "Usage %s [--log] [--quiet] <path>\n", argv[0]);
            return -2;
        }
        else
            target = argv[i];
    }

    if(target == NULL)
    {
        fprintf(stderr, "Please specify a target path.\n");
        fprintf(stderr, "Usage %s [--log] [--quiet] <path>\n", argv[0]);
        return -3;
    }

    log_set_quiet(quiet);

    if(log)
    {
        log = !log_open(quiet);

        if(log)
        {
            log_write("Parameters:");
            for(i = 0; i < argc; i++) log_write(" %s", argv[i]);
            log_write("\n");
        }
    }

    log_write("Running in %s (%s)\n", OS_NAME, OS_ARCH);
    log_write("\n");

    GetOsInfo();
    GetVolumeInfo(target, &clusterSize);
    FileAttributes(target);
    FilePermissions(target);
    ExtendedAttributes(target);
    ResourceFork(target);
    Filenames(target);
    Timestamps(target);
    Links(target);
#ifndef __atarist__ // Because this prevents us from generation more folders
    DirectoryDepth(target);
#endif
    Fragmentation(target, clusterSize);
    Sparse(target);
    MillionFiles(target);
    DeleteFiles(target);
#ifdef __atarist__ // Because this prevents us from generation more folders
    DirectoryDepth(target);
#endif
    GetVolumeInfo(target, &clusterSize);

    log_close();
    return 0;
}

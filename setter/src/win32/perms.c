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

// ReSharper disable CppJoinDeclarationAndAssignment
// ReSharper disable CppDeprecatedEntity

#ifdef __CYGWIN__
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/cygwin.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#include "perms.h"
#endif // __CYGWIN__

#include "../include/defs.h"
#include "../log.h"

void FilePermissions(const char* path)
{
    // Only supported by Cygwin, Windows uses normal attributes
#ifdef __CYGWIN__
    int   ret;
    FILE* file;
    int   rc;
    int   cRc;
    int   i;
    char  cyg_path[PATH_MAX];

    memset(cyg_path, 0, PATH_MAX);

    cygwin_conv_path(CCP_WIN_A_TO_POSIX, path, cyg_path, PATH_MAX);

    ret = chdir(cyg_path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("PERMS", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("PERMS");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);
        return;
    }

    log_write("Creating attributes files.\n");

    for(i = 0; i < KNOWN_CYGWIN_PERMS; i++)
    {
        file = fopen(cygwin_perms[i].filename, "w+");
        rc   = 0;
        cRc  = 0;

        if(!file) rc = errno;
        else
        {
            fprintf(file, "%s.\n", cygwin_perms[i].description);
            fclose(file);
            cRc = chmod(cygwin_perms[i].filename, cygwin_perms[i].mode);
        }

        log_write(
            "\t%s: name = \"%s\", rc = %d, cRc = %d\n", cygwin_perms[i].description, cygwin_perms[i].filename, rc, cRc);
    }
#endif
}

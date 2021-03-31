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

#include <TypeConstants.h>
#include <errno.h>
#include <fs_attr.h>
#include <stdio.h>
#include <stdio_pre.h>
#include <sys/stat.h>
#include <unistd.h>

#include "xattr.h"

#include "../include/defs.h"
#include "../log.h"

void ExtendedAttributes(const char* path)
{
    int   ret;
    FILE* file;
    int   rc;
    int   cRc;
    int   attr_fd;

    ret = chdir(path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("XATTRS", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("XATTRS");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);
        return;
    }

    log_write("Creating files with extended attributes.\n");

    rc   = 0;
    cRc  = 0;
    file = fopen("comment", "w+");
    if(file == NULL) rc = errno;
    else
    {
        fprintf(file, "This file has an extended attribute called \"comment\" that is 34 bytes long.\n");
        fclose(file);
        attr_fd = fs_open_attr("comment", "comment", B_STRING_TYPE, O_RDWR);

        if(attr_fd >= 0)
        {
            cRc = fs_write_attr(attr_fd, "comment", B_STRING_TYPE, 0, stringAttribute, 34);

            cRc = cRc < 0 ? errno : 0;

            fs_close_attr(attr_fd);
        }
        else
            rc = errno;
    }
    log_write("\tFile with an extended attribute called \"comment\", rc = %d, cRc = %d\n", rc, cRc);

    rc   = 0;
    cRc  = 0;
    file = fopen("icon", "w+");
    if(file == NULL) rc = errno;
    else
    {
        fprintf(file, "This file has an extended attribute called \"comment\" that is 34 bytes long.\n");
        fclose(file);
        attr_fd = fs_open_attr("icon", "BEOS:L:STD_ICON", B_LARGE_ICON_TYPE, O_RDWR);

        if(attr_fd >= 0)
        {
            cRc = fs_write_attr(attr_fd, "BEOS:L:STD_ICON", B_LARGE_ICON_TYPE, 0, iconAttribute, 1024);

            cRc = cRc < 0 ? errno : 0;

            fs_close_attr(attr_fd);
        }
        else
            rc = errno;
    }
    log_write("\tFile with an extended attribute called \"BEOS:L:STD_ICON\", rc = %d, cRc = %d\n", rc, cRc);
}

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
#include <features.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../log.h"
#include "linux.h"

#if((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 3)) || (__GLIBC__ > 2)
#include <sys/xattr.h>
#endif

void LinuxExtendedAttributes(const char* path)
{
#if((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 3)) || (__GLIBC__ > 2)
    int   ret;
    FILE* file;
    int   rc;
    int   cRc;

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
    file = fopen("com.ibm.os2.comment", "w+");
    if(file == NULL) rc = errno;
    else
    {
        fprintf(file, "This file has an extended attribute called \"com.ibm.os2.comment\" that is 72 bytes long.\n");
        fclose(file);
        ret = setxattr("com.ibm.os2.comment", "user.com.ibm.os2.comment", CommentsEA, 72, XATTR_CREATE);

        if(ret) cRc = errno;
    }
    log_write("\tFile with an extended attribute called \"com.ibm.os2.comment\", rc = %d, cRc = %d\n", rc, cRc);

    rc   = 0;
    cRc  = 0;
    file = fopen("com.ibm.os2.icon", "w+");
    if(file == NULL) rc = errno;
    else
    {
        fprintf(file, "This file has an extended attribute called \"com.ibm.os2.icon\" that is 3516 bytes long.\n");
        fclose(file);
        ret = setxattr("com.ibm.os2.icon", "user.com.ibm.os2.icon", IconEA, 3516, XATTR_CREATE);

        if(ret) cRc = errno;
    }
    log_write("\tFile with an extended attribute called \"com.ibm.os2.icon\", rc = %d, cRc = %d\n", rc, cRc);
#endif
}

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
#include <eti.h>
#include <mint/cookie.h>
#include <mint/mintbind.h>
#include <mint/osbind.h>
#include <mint/sysvars.h>
#include <stdio.h>

#include "../include/defs.h"
#include "../log.h"

void Links(const char* path)
{
    long* cookieJar;
    long  cookie;
    int   rc;
    FILE* h;
    char  driveNo = path[0] - '@';
    long  savessp;

    // Retrieve pointer to cookie jar in Supervisor mode
    savessp   = Super(0L);
    cookieJar = *_p_cookies;
    Super((void*)savessp);

    // Check for a cookie jar
    if(cookieJar == 0) return;

    // Check if MiNT or MagiC
    rc = (Getcookie(C_MiNT, &cookie) == E_OK) || (Getcookie(C_MagX, &cookie) == E_OK) ||
         (Getcookie(C_MgMc, &cookie) == E_OK) || (Getcookie(C_MgMx, &cookie) == E_OK) ||
         (Getcookie(C_MgPC, &cookie) == E_OK);

    if(rc == 0) return;

    if(driveNo > 32) driveNo -= 32;

    Dsetdrv(driveNo);
    Dsetpath("\\");

    rc = Dcreate("LINKS");

    if(rc != E_OK)
    {
        log_write("Error %d creating working directory.\n", rc);
        return;
    }

    rc = Dsetpath("LINKS");

    if(rc != E_OK)
    {
        log_write("Error %d changing to working directory.\n", rc);
        return;
    }

    log_write("Creating links.\n");

    h = fopen("TARGET", "w+");

    if(h == NULL)
    {
        log_write("Error %d creating target file.\n", errno);
        return;
    }

    fprintf(h, "This is the target for the links.\n");

    fclose(h);

    rc = Flink("TARGET", "HARD");

    if(rc != E_OK) log_write("Error %d creating hard link.\n", errno);

    rc = Fsymlink("TARGET", "SYMBOLIC");

    if(rc != E_OK) log_write("Error %d creating symbolic link.\n", errno);
}

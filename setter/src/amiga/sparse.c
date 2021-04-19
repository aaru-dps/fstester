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

#include <proto/dos.h>

#include "../include/consts.h"
#include "../include/defs.h"
#include "../log.h"

void Sparse(const char* path)
{
    BPTR pathLock;
    BPTR dirLock;
    int  ret;
    int  rc, wRc, cRc;
    BPTR h;
    int  i;

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        log_write("Error %d changing to specified path.\n", IoErr());
        return;
    }

    CurrentDir(pathLock);

    dirLock = CreateDir((CONST_STRPTR) "SPARSE");

    if(!dirLock)
    {
        log_write("Error %d creating working directory.\n", IoErr());
        return;
    }

    CurrentDir(dirLock);

    log_write("Creating sparse files.\n");

    h   = Open((CONST_STRPTR) "SMALL", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        for(i = 0; i < 4096; i += CLAUNIA_SIZE)
        {
            ret = Write(h, clauniaBytes, CLAUNIA_SIZE);
            if(ret < 0)
            {
                wRc = IoErr();
                break;
            }
        }

        Seek(h, 8192, OFFSET_CURRENT);

        for(i = 4096 + 8192; i < 4096 * 4; i += CLAUNIA_SIZE)
        {
            ret = Write(h, clauniaBytes, CLAUNIA_SIZE);
            if(ret < 0)
            {
                wRc = IoErr();
                break;
            }
        }

        ret = Close(h);
        if(!ret) cRc = IoErr();
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "SMALL", 4096 * 4, rc, wRc, cRc);

    h   = Open((CONST_STRPTR) "BIG", MODE_NEWFILE);
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(!h) rc = IoErr();
    else
    {
        for(i = 0; i < 4096 * 8; i += CLAUNIA_SIZE)
        {
            ret = Write(h, clauniaBytes, CLAUNIA_SIZE);
            if(ret < 0)
            {
                wRc = IoErr();
                break;
            }
        }

        Seek(h, 81920, OFFSET_CURRENT);

        for(i = 32768 + 81920; i < 4096 * 30; i += CLAUNIA_SIZE)
        {
            ret = Write(h, clauniaBytes, CLAUNIA_SIZE);
            if(ret < 0)
            {
                wRc = IoErr();
                break;
            }
        }
    }

    log_write("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "BIG", 4096 * 30, rc, wRc, cRc);
}

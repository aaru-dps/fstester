/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : os2_16.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains 16-bit OS/2 code

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

#if(defined(__I86__) || defined(__i86__) || defined(_M_I86)) && (defined(__OS2__) || defined(__os2__)) &&              \
    !defined(__DOS__)

#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../os2.h"
#include "include/consts.h"
#include "include/defs.h"

void FileAttributes(const char* path)
{
    char   drivePath[4];
    USHORT rc = 0, wRc = 0, cRc = 0;
    USHORT actionTaken = 0;
    HFILE  handle;

    drivePath[0] = path[0];
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    rc = DosChDir(drivePath, 0);

    if(rc)
    {
        printf("Cannot change to specified path, not continuing.\n");
        return;
    }

    rc = DosMkDir("ATTRS", 0);

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    rc = DosChDir("ATTRS", 0);

    printf("Creating attributes files.\n");

    rc = DosOpen("NONE",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)noAttributeText, strlen(noAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("NONE", FILE_NORMAL, 0);
    }

    printf("\tFile with no attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "NONE", rc, wRc, cRc);

    rc = DosOpen("ARCHIVE",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARCHIVE", FILE_ARCHIVED, 0);
    }

    printf("\tFile with archived attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "ARCHIVE", rc, wRc, cRc);

    rc = DosOpen("SYSTEM",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("SYSTEM", FILE_SYSTEM, 0);
    }

    printf("\tFile with system attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "SYSTEM", rc, wRc, cRc);

    rc = DosOpen("HIDDEN",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("HIDDEN", FILE_HIDDEN, 0);
    }

    printf("\tFile with hidden attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "HIDDEN", rc, wRc, cRc);

    rc = DosOpen("READONLY",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("READONLY", FILE_READONLY, 0);
    }

    printf("\tFile with read-only attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "READONLY", rc, wRc, cRc);

    rc = DosOpen("HIDDREAD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("HIDDREAD", FILE_HIDDEN | FILE_READONLY, 0);
    }

    printf("\tFile with hidden, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "HIDDREAD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("SYSTREAD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("SYSTREAD", FILE_SYSTEM | FILE_READONLY, 0);
    }

    printf("\tFile with system, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "SYSTREAD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("SYSTHIDD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("SYSTHIDD", FILE_SYSTEM | FILE_HIDDEN, 0);
    }

    printf("\tFile with system, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "SYSTHIDD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("SYSRDYHD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("SYSRDYHD", FILE_SYSTEM | FILE_READONLY | FILE_HIDDEN, 0);
    }

    printf("\tFile with system, read-only, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "SYSRDYHD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARCHREAD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARCHREAD", FILE_ARCHIVED | FILE_READONLY, 0);
    }

    printf("\tFile with archived, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHREAD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARCHHIDD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARCHHIDD", FILE_ARCHIVED | FILE_HIDDEN, 0);
    }

    printf("\tFile with archived, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHHIDD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARCHDRDY",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARCHDRDY", FILE_ARCHIVED | FILE_HIDDEN | FILE_READONLY, 0);
    }

    printf("\tFile with archived, hidden, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHDRDY",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARCHSYST",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARCHSYST", FILE_ARCHIVED | FILE_SYSTEM, 0);
    }

    printf("\tFile with archived, system attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHSYST",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARSYSRDY",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARSYSRDY", FILE_ARCHIVED | FILE_SYSTEM | FILE_READONLY, 0);
    }

    printf("\tFile with archived, system, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARSYSRDY",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARCSYSHD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARCSYSHD", FILE_ARCHIVED | FILE_SYSTEM | FILE_HIDDEN, 0);
    }

    printf("\tFile with archived, system, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCSYSHD",
           rc,
           wRc,
           cRc);

    rc = DosOpen("ARSYHDRD",
                 &handle,
                 &actionTaken,
                 0,
                 FILE_NORMAL,
                 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE | OPEN_ACCESS_READWRITE,
                 0);

    if(!rc)
    {
        wRc = DosWrite(handle, (PVOID)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        wRc = DosWrite(handle, (PVOID)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = DosClose(handle);
        rc  = DosSetFileMode("ARSYHDRD", FILE_ARCHIVED | FILE_SYSTEM | FILE_HIDDEN | FILE_READONLY, 0);
    }

    printf("\tFile with all (archived, system, hidden, read-only) attributes: name = \"%s\", rc = %d, wRc = %d, cRc = "
           "%d\n",
           "ARSYHDRD",
           rc,
           wRc,
           cRc);
}

#endif

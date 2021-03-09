/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : dos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains DOS code

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

#if defined(__DOS__) || defined(MSDOS)

#include <direct.h>
#include <dos.h>
#include <i86.h>
#include <io.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dos.h"

#include "../include/dosos2.h"
#include "../include/consts.h"
#include "../include/defs.h"

void FileAttributes(const char* path)
{
    char     driveNo = path[0] - '@';
    unsigned total, actionTaken;
    int      rc, wRc, cRc, handle;

    if(driveNo > 32) driveNo -= 32;

    _dos_setdrive(driveNo, &total);
    chdir("\\");

    rc = mkdir("ATTRS");

    if(rc)
    {
        printf("Cannot create working directory.\n");
        return;
    }

    chdir("ATTRS");

    printf("Creating attributes files.\n");

    rc = _dos_creat("NONE", 0, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)noAttributeText, strlen(noAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("NONE", _A_NORMAL);
    }

    printf("\tFile with no attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "NONE", rc, wRc, cRc);

    rc = _dos_creat("ARCHIVE", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARCHIVE", _A_ARCH);
    }

    printf("\tFile with archived attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "ARCHIVE", rc, wRc, cRc);

    rc = _dos_creat("SYSTEM", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("SYSTEM", _A_SYSTEM);
    }

    printf("\tFile with system attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "SYSTEM", rc, wRc, cRc);

    rc = _dos_creat("HIDDEN", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("HIDDEN", _A_HIDDEN);
    }

    printf("\tFile with hidden attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "HIDDEN", rc, wRc, cRc);

    rc = _dos_creat("READONLY", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("READONLY", _A_RDONLY);
    }

    printf("\tFile with read-only attribute: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", "READONLY", rc, wRc, cRc);

    rc = _dos_creat("HIDDREAD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("HIDDREAD", _A_HIDDEN | _A_RDONLY);
    }

    printf("\tFile with hidden, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "HIDDREAD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("SYSTREAD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("SYSTREAD", _A_SYSTEM | _A_RDONLY);
    }

    printf("\tFile with system, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "SYSTREAD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("SYSTHIDD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("SYSTHIDD", _A_SYSTEM | _A_HIDDEN);
    }

    printf("\tFile with system, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "SYSTHIDD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("SYSRDYHD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("SYSRDYHD", _A_SYSTEM | _A_RDONLY | _A_HIDDEN);
    }

    printf("\tFile with system, read-only, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "SYSRDYHD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARCHREAD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARCHREAD", _A_ARCH | _A_RDONLY);
    }

    printf("\tFile with archived, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHREAD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARCHHIDD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARCHHIDD", _A_ARCH | _A_HIDDEN);
    }

    printf("\tFile with archived, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHHIDD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARCHDRDY", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARCHDRDY", _A_ARCH | _A_HIDDEN | _A_RDONLY);
    }

    printf("\tFile with archived, hidden, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHDRDY",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARCHSYST", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARCHSYST", _A_ARCH | _A_SYSTEM);
    }

    printf("\tFile with archived, system attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCHSYST",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARSYSRDY", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARSYSRDY", _A_ARCH | _A_SYSTEM | _A_RDONLY);
    }

    printf("\tFile with archived, system, read-only attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARSYSRDY",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARCSYSHD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARCSYSHD", _A_ARCH | _A_SYSTEM | _A_HIDDEN);
    }

    printf("\tFile with archived, system, hidden attributes: name = \"%s\", rc = %d, wRc = %d, cRc = %d\n",
           "ARCSYSHD",
           rc,
           wRc,
           cRc);

    rc = _dos_creat("ARSYHDRD", _A_NORMAL, &handle);

    if(!rc)
    {
        wRc = _dos_write(handle, (void*)archivedAttributeText, strlen(archivedAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)systemAttributeText, strlen(systemAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)hiddenAttributeText, strlen(hiddenAttributeText), &actionTaken);
        wRc = _dos_write(handle, (void*)readonlyAttributeText, strlen(readonlyAttributeText), &actionTaken);
        cRc = _dos_close(handle);
        rc  = _dos_setfileattr("ARSYHDRD", _A_ARCH | _A_SYSTEM | _A_HIDDEN | _A_RDONLY);
    }

    printf("\tFile with all (archived, system, hidden, read-only) attributes: name = \"%s\", rc = %d, wRc = %d, cRc = "
           "%d\n",
           "ARSYHDRD",
           rc,
           wRc,
           cRc);
}

#endif
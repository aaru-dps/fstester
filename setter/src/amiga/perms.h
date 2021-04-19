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

#ifndef AARU_FSTESTER_SETTER_SRC_AMIGA_PERMS_H_
#define AARU_FSTESTER_SETTER_SRC_AMIGA_PERMS_H_

#include <dos/dos.h>

typedef struct
{
    char   filename[256];
    char   description[256];
    LONG   mode;
} amiga_perms_tests_t;

#define KNOWN_AMIGA_PERMS 16

static const amiga_perms_tests_t amiga_perms[KNOWN_AMIGA_PERMS] = {
    {"NONE", "File with no permissions set", 0},
    {"OR", "File can be read by others", FIBF_OTR_READ},
    {"OW", "File can be written by others", FIBF_OTR_WRITE},
    {"OE", "File can be executed by others", FIBF_OTR_EXECUTE},
    {"OD", "File can be deleted by others", FIBF_OTR_DELETE},
    {"GR", "File can be read by group", FIBF_GRP_READ},
    {"GW", "File can be written by group", FIBF_GRP_WRITE},
    {"GE", "File can be executed by group", FIBF_GRP_EXECUTE},
    {"GD", "File can be deleted by group", FIBF_GRP_DELETE},
    {"SCRIPT", "File is a script", FIBF_SCRIPT},
    {"PURE", "File is reentrant and re-executable", FIBF_PURE},
    {"ARCHIVE", "File has been archived", FIBF_ARCHIVE},
    {"READ", "File cannot be read", FIBF_READ},
    {"WRITE", "File cannot be written", FIBF_WRITE},
    {"EXECUTE", "File cannot be executed", FIBF_EXECUTE},
    {"DELETE", "File cannot be deleted", FIBF_DELETE},
};

#endif // AARU_FSTESTER_SETTER_SRC_AMIGA_PERMS_H_

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

#ifndef AARU_FSTESTER_SETTER_SRC_OS2_ATTR_H_
#define AARU_FSTESTER_SETTER_SRC_OS2_ATTR_H_

#ifndef OS2_INCLUDED
#define INCL_DOSMISC
#define INCL_DOSFILEMGR

#include <os2.h>
#endif

typedef struct
{
    char   filename[9];
    char   contents[170];
    char   description[63];
    USHORT attr;
} os2_attr_tests_t;

#define KNOWN_OS2_ATTRS 16

static const os2_attr_tests_t os2_attrs[KNOWN_OS2_ATTRS] = {
    {"NONE", "This file has no attribute set.\n", "File with no attributes", FILE_NORMAL},
    {"ARCHIVE", "This file has the archived attribute set.\n", "File with archived attribute", FILE_ARCHIVED},
    {"SYSTEM", "This file has the system attribute set.\n", "File with system attribute", FILE_SYSTEM},
    {"HIDDEN", "This file has the hidden attribute set.\n", "File with hidden attribute", FILE_HIDDEN},
    {"READONLY", "This file has the read-only attribute set.\n", "File with read-only attribute", FILE_READONLY},
    {"HIDDREAD",
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with hidden, read-only attributes",
     FILE_HIDDEN | FILE_READONLY},
    {"SYSTREAD",
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with system, read-only attributes",
     FILE_SYSTEM | FILE_READONLY},
    {"SYSTHIDD",
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with system, hidden attributes",
     FILE_SYSTEM | FILE_HIDDEN},
    {"SYSRDYHD",
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with system, read-only, hidden attributes",
     FILE_SYSTEM | FILE_READONLY | FILE_HIDDEN},
    {"ARCHREAD",
     "This file has the archived attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, read-only attributes",
     FILE_ARCHIVED | FILE_READONLY},
    {"ARCHHIDD",
     "This file has the archived attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with archived, hidden attributes",
     FILE_ARCHIVED | FILE_HIDDEN},
    {"ARCHDRDY",
     "This file has the archived attribute set.\n"
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, hidden, read-only attributes",
     FILE_ARCHIVED | FILE_HIDDEN | FILE_READONLY},
    {"ARCHSYST",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n",
     "File with archived, system attributes",
     FILE_ARCHIVED | FILE_SYSTEM},
    {"ARSYSRDY",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, system, read-only attributes",
     FILE_ARCHIVED | FILE_SYSTEM | FILE_READONLY},
    {"ARCSYSHD",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with archived, system, hidden attributes",
     FILE_ARCHIVED | FILE_SYSTEM | FILE_HIDDEN},
    {"ARSYHDRD",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with all (archived, system, hidden, read-only) attributes",
     FILE_ARCHIVED | FILE_SYSTEM | FILE_HIDDEN | FILE_READONLY},
};

#endif // AARU_FSTESTER_SETTER_SRC_OS2_ATTR_H_


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

#ifndef SETTER_SRC_DOS_ATTR_H_
#define SETTER_SRC_DOS_ATTR_H_

#include <dos.h>

typedef struct
{
    char         filename[9];
    char         contents[170];
    char         description[63];
    unsigned int attr;
} dos_attr_tests_t;

#define KNOWN_DOS_ATTRS 16

static const dos_attr_tests_t dos_attrs[KNOWN_DOS_ATTRS] = {
    {"NONE", "This file has no attribute set.\n", "File with no attributes", _A_NORMAL},
    {"ARCHIVE", "This file has the archived attribute set.\n", "File with archived attribute", _A_ARCH},
    {"SYSTEM", "This file has the system attribute set.\n", "File with system attribute", _A_SYSTEM},
    {"HIDDEN", "This file has the hidden attribute set.\n", "File with hidden attribute", _A_HIDDEN},
    {"READONLY", "This file has the read-only attribute set.\n", "File with read-only attribute", _A_RDONLY},
    {"HIDDREAD",
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with hidden, read-only attributes",
     _A_HIDDEN | _A_RDONLY},
    {"SYSTREAD",
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with system, read-only attributes",
     _A_SYSTEM | _A_RDONLY},
    {"SYSTHIDD",
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with system, hidden attributes",
     _A_SYSTEM | _A_HIDDEN},
    {"SYSRDYHD",
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with system, read-only, hidden attributes",
     _A_SYSTEM | _A_RDONLY | _A_HIDDEN},
    {"ARCHREAD",
     "This file has the archived attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, read-only attributes",
     _A_ARCH | _A_RDONLY},
    {"ARCHHIDD",
     "This file has the archived attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with archived, hidden attributes",
     _A_ARCH | _A_HIDDEN},
    {"ARCHDRDY",
     "This file has the archived attribute set.\n"
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, hidden, read-only attributes",
     _A_ARCH | _A_HIDDEN | _A_RDONLY},
    {"ARCHSYST",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n",
     "File with archived, system attributes",
     _A_ARCH | _A_SYSTEM},
    {"ARSYSRDY",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, system, read-only attributes",
     _A_ARCH | _A_SYSTEM | _A_RDONLY},
    {"ARCSYSHD",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with archived, system, hidden attributes",
     _A_ARCH | _A_SYSTEM | _A_HIDDEN},
    {"ARSYHDRD",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with all (archived, system, hidden, read-only) attributes",
     _A_ARCH | _A_SYSTEM | _A_HIDDEN | _A_RDONLY},
};

#endif // SETTER_SRC_DOS_ATTR_H_

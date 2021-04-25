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

#ifndef AARU_FSTESTER_SETTER_SRC_ATARI_ATTR_H_
#define AARU_FSTESTER_SETTER_SRC_ATARI_ATTR_H_

#include <mint/ostruct.h>

typedef struct
{
    char         filename[9];
    char         contents[170];
    char         description[63];
    unsigned int attr;
} atari_attr_tests_t;

#define KNOWN_ATARI_ATTRS 16

static const atari_attr_tests_t atari_attrs[KNOWN_ATARI_ATTRS] = {
    {"NONE", "This file has no attribute set.\n", "File with no attributes", 0},
    {"ARCHIVE", "This file has the archived attribute set.\n", "File with archived attribute", FA_CHANGED},
    {"SYSTEM", "This file has the system attribute set.\n", "File with system attribute", FA_SYSTEM},
    {"HIDDEN", "This file has the hidden attribute set.\n", "File with hidden attribute", FA_HIDDEN},
    {"READONLY", "This file has the read-only attribute set.\n", "File with read-only attribute", FA_RDONLY},
    {"HIDDREAD",
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with hidden, read-only attributes",
     FA_HIDDEN | FA_RDONLY},
    {"SYSTREAD",
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with system, read-only attributes",
     FA_SYSTEM | FA_RDONLY},
    {"SYSTHIDD",
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with system, hidden attributes",
     FA_SYSTEM | FA_HIDDEN},
    {"SYSRDYHD",
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with system, read-only, hidden attributes",
     FA_SYSTEM | FA_RDONLY | FA_HIDDEN},
    {"ARCHREAD",
     "This file has the archived attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, read-only attributes",
     FA_CHANGED | FA_RDONLY},
    {"ARCHHIDD",
     "This file has the archived attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with archived, hidden attributes",
     FA_CHANGED | FA_HIDDEN},
    {"ARCHDRDY",
     "This file has the archived attribute set.\n"
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, hidden, read-only attributes",
     FA_CHANGED | FA_HIDDEN | FA_RDONLY},
    {"ARCHSYST",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n",
     "File with archived, system attributes",
     FA_CHANGED | FA_SYSTEM},
    {"ARSYSRDY",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with archived, system, read-only attributes",
     FA_CHANGED | FA_SYSTEM | FA_RDONLY},
    {"ARCSYSHD",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n",
     "File with archived, system, hidden attributes",
     FA_CHANGED | FA_SYSTEM | FA_HIDDEN},
    {"ARSYHDRD",
     "This file has the archived attribute set.\n"
     "This file has the system attribute set.\n"
     "This file has the hidden attribute set.\n"
     "This file has the read-only attribute set.\n",
     "File with all (archived, system, hidden, read-only) attributes",
     FA_CHANGED | FA_SYSTEM | FA_HIDDEN | FA_RDONLY},
};

#endif // AARU_FSTESTER_SETTER_SRC_ATARI_ATTR_H_

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

#ifndef AARU_FSTESTER_SETTER_SRC_DARWIN_ATTR_H_
#define AARU_FSTESTER_SETTER_SRC_DARWIN_ATTR_H_

#include <sys/stat.h>

typedef struct
{
    char         filename[16];
    char         contents[256];
    char         description[256];
    unsigned int attr;
} darwin_attr_tests_t;

#define KNOWN_DARWIN_ATTRS 9

#ifndef UF_NODUMP
#define UF_NODUMP 0x00000001 /* Do not dump the file. */
#endif
#ifndef UF_IMMUTABLE
#define UF_IMMUTABLE 0x00000002 /* The file may not be changed. */
#endif

#ifndef UF_APPEND
#define UF_APPEND 0x00000004 /* The file may only be appended to. */
#endif

#ifndef UF_OPAQUE
#define UF_OPAQUE 0x00000008 /* The directory is opaque when viewed through a union stack. */
#endif

#ifndef UF_HIDDEN
#define UF_HIDDEN 0x00000010 /* The file or directory is not intended to be displayed to the user. */
#endif

#ifndef SF_ARCHIVED
#define SF_ARCHIVED 0x00000020 /* The file has been archived. */
#endif

#ifndef SF_IMMUTABLE
#define SF_IMMUTABLE 0x00000040 /* The file may not be changed. */
#endif

#ifndef SF_APPEND
#define SF_APPEND 0x00000080 /* The file may only be appended to. */
#endif

#ifndef SF_DATALESS
#define SF_DATALESS 0x00004000 /* The file is a dataless placeholder. */
#endif

static const darwin_attr_tests_t darwin_attrs[KNOWN_DARWIN_ATTRS] = {
    {"NODUMP", "This file is now not dumpable", "File with no dump flag", UF_NODUMP},
    {"IMMUTABLE", "This file is now immutable", "File with immutable flag", UF_IMMUTABLE},
    {"APPEND", "This file is now append only", "File with append only flag", UF_APPEND},
    {"OPAQUE", "This directory is opaque when viewed through a union stack", "File with opaque flag", UF_OPAQUE},
    {"HIDDEN", "This file is hidden from user view", "File with hidden flag", UF_HIDDEN},
    {"ARCHIVED", "This file is now archived", "File with archived flag", SF_ARCHIVED},
    {"SF_IMMUTABLE",
     "This file is now immutable, and only the super-user change change that",
     "File with super-usr immutable flag",
     SF_IMMUTABLE},
    {"SF_APPEND",
     "This file is now append only, and only the super-user change change that",
     "File with super-user append only flag",
     SF_APPEND},
    {"SF_DATALESS", "This file is a dataless placeholder", "File with dataless flag", SF_DATALESS},
};

#endif // AARU_FSTESTER_SETTER_SRC_DARWIN_ATTR_H_

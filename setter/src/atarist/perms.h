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

#ifndef AARU_FSTESTER_SETTER_SRC_ATARI_PERMS_H_
#define AARU_FSTESTER_SETTER_SRC_ATARI_PERMS_H_

typedef struct
{
    char   filename[256];
    char   description[256];
    short  mode;
} atari_perms_tests_t;

#define KNOWN_ATARI_PERMS 14

static const atari_perms_tests_t atari_perms[KNOWN_ATARI_PERMS] = {
    {"NONE", "File with no permissions", 0},
    {"04000", "File with set-user-ID", 04000},
    {"02000", "File with set-group-ID", 02000},
    {"01000", "File with sticky bit", 01000},
    {"00400", "File with read by owner", 00400},
    {"00200", "File with write by owner", 00200},
    {"00100", "File with execute by owner", 00100},
    {"00040", "File with read by group", 00040},
    {"00020", "File with write by group", 00020},
    {"00010", "File with execute by group", 00010},
    {"00004", "File with read by others", 00004},
    {"00002", "File with write by others", 00002},
    {"00001", "File with execute by others", 00001},
};

#endif // AARU_FSTESTER_SETTER_SRC_ATARI_PERMS_H_

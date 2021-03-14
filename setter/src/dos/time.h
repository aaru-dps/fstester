/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : time.h
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains DOS definitions

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

#ifndef SETTER_SRC_DOS_TIME_H_
#define SETTER_SRC_DOS_TIME_H_

#include <dos.h>

#define DATETIME_FORMAT "This file is dated %04d/%02d/%02d %02d:%02d:%02d for %s\n"

typedef struct
{
  char filename[9];
  unsigned short date;
  unsigned short time;
  unsigned short function;
  char definition[13];
} dos_time_tests_t;

#define KNOWN_DOS_TIMES 12

#define WIN_SET_CREATION_DATE_AND_TIME 0x5707
#define DOS_SET_LAST_WRITTEN_DATE_AND_TIME 0x5701
#define WIN_SET_LAST_ACCESS_DATE_AND_TIME 0x5705

#define MAX_TIME 0xBF7D
#define MAX_DATE 0xFF9F
#define Y1K_DATE 0x2621
#define Y2K_DATE 0x2821
#define MIN_DATE 0x0021

static const dos_time_tests_t dos_times[KNOWN_DOS_TIMES] = {
    {"MAXCTIME",MAX_DATE, MAX_TIME, WIN_SET_CREATION_DATE_AND_TIME, "creation"},
    {"MINCTIME",MIN_DATE, 0, WIN_SET_CREATION_DATE_AND_TIME, "creation"},
    {"Y19CTIME",Y1K_DATE, MAX_TIME, WIN_SET_CREATION_DATE_AND_TIME, "creation"},
    {"Y2KCTIME",Y2K_DATE, MAX_TIME, WIN_SET_CREATION_DATE_AND_TIME, "creation"},
    {"MAXWTIME",MAX_DATE, MAX_TIME, DOS_SET_LAST_WRITTEN_DATE_AND_TIME, "last written"},
    {"MINWTIME",MIN_DATE, 0, DOS_SET_LAST_WRITTEN_DATE_AND_TIME, "last written"},
    {"Y19WTIME",Y1K_DATE, MAX_TIME, DOS_SET_LAST_WRITTEN_DATE_AND_TIME, "last written"},
    {"Y2KWTIME",Y2K_DATE, MAX_TIME, DOS_SET_LAST_WRITTEN_DATE_AND_TIME, "last written"},
    {"MAXATIME",MAX_DATE, MAX_TIME, WIN_SET_LAST_ACCESS_DATE_AND_TIME, "last access"},
    {"MINATIME",MIN_DATE, 0, WIN_SET_LAST_ACCESS_DATE_AND_TIME, "last access"},
    {"Y19ATIME",Y1K_DATE, MAX_TIME, WIN_SET_LAST_ACCESS_DATE_AND_TIME, "last access"},
    {"Y2KATIME",Y2K_DATE, MAX_TIME, WIN_SET_LAST_ACCESS_DATE_AND_TIME, "last access"},
};

#endif // SETTER_SRC_DOS_TIME_H_

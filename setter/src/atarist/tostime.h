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

#ifndef AARU_FSTESTER_SETTER_SRC_ATARI_TIME_H_
#define AARU_FSTESTER_SETTER_SRC_ATARI_TIME_H_

#define DATETIME_FORMAT "This file is dated %04d/%02d/%02d %02d:%02d:%02d for %s\n"

#define YEAR(t) ((((t)&0xFE00) >> 9) + 1980)
#define MONTH(t) (((t)&0x01E0) >> 5)
#define DAY(t) ((t)&0x001F)
#define HOUR(t) (((t)&0xF800) >> 11)
#define MINUTE(t) (((t)&0x07E0) >> 5)
#define SECOND(t) (((t)&0x001F) << 1)

typedef struct
{
    char           filename[9];
    unsigned short date;
    unsigned short time;
    char           definition[13];
} atari_time_tests_t;

#define KNOWN_ATARI_TIMES 4

#define MAX_TIME 0xBF7D
#define MAX_DATE 0xFF9F
#define Y1K_DATE 0x2621
#define Y2K_DATE 0x2821
#define MIN_DATE 0x0021

static const atari_time_tests_t atari_times[KNOWN_ATARI_TIMES] = {
    {"MAXWTIME", MAX_DATE, MAX_TIME, "last written"},
    {"MINWTIME", MIN_DATE, 0, "last written"},
    {"Y19WTIME", Y1K_DATE, MAX_TIME, "last written"},
    {"Y2KWTIME", Y2K_DATE, MAX_TIME, "last written"},
};

#endif // AARU_FSTESTER_SETTER_SRC_ATARI_TIME_H_

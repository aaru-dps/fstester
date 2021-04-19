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

#ifndef AARU_FSTESTER_SETTER_SRC_AMIGA_TIME_H_
#define AARU_FSTESTER_SETTER_SRC_AMIGA_TIME_H_

#define DATETIME_FORMAT "This file is dated %s\n"
#define MAXDATETIME "5881588/01/20 23:59:59.98"
#define MINDATETIME "-5877633/01/01 00:00:00"
#define ZERODATETIME "1978/01/01 00:00:00"
#define Y2KDATETIME "2000/01/01 00:00:00"
#define Y1KDATETIME "1999/12/31 23:59:59"

typedef struct
{
    char* filename;
    char  message[32];
    LONG  days;
    LONG  minutes;
    LONG  ticks;
} amiga_time_tests_t;

#define KNOWN_AMIGA_TIMES 5

static const amiga_time_tests_t amiga_times[KNOWN_AMIGA_TIMES] = {
    "MAX", MAXDATETIME, 0x7FFFFFFF,   1439,        2999, "MIN", MINDATETIME, 0xFFFFFFFF,  0,
    0,     "ZERO",      ZERODATETIME, 0,           0,    0,     "Y2K",       Y2KDATETIME, 8035,
    0,     0,           "Y1K",        Y1KDATETIME, 8034, 1439,  2950};

#endif // AARU_FSTESTER_SETTER_SRC_AMIGA_TIME_H_

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

#ifndef AARU_FSTESTER_SETTER_SRC_UNIX_TIME_H_
#define AARU_FSTESTER_SETTER_SRC_UNIX_TIME_H_

#define DATETIME_FORMAT "This file is dated %s for %s\n"
#define LESSDATETIME "2106/02/07 06:28:15 or unknown"
#define MAXDATETIME "2038/01/19 03:14:07"
#define MINDATETIME "1970/01/01 00:00:00"
#define Y2KDATETIME "2000/01/01 00:00:00"
#define Y1KDATETIME "1999/12/31 23:59:59"
#define LESSTIMESTAMP 0xFFFFFFFF
#define MAXTIMESTAMP 0x7FFFFFFF
#define MINTIMESTAMP 0x00000000
#define Y2KTIMESTAMP 0x386D4380
#define Y1KTIMESTAMP 0x386D437F

typedef struct
{
  char*   filename;
  time_t access;
  time_t modification;
  char    type[13];
  char    message[32];
} unix_time_tests_t;

#define KNOWN_UNIX_TIMES 10

static const unix_time_tests_t unix_times[KNOWN_UNIX_TIMES] = {
    "MAXATIME", MAXTIMESTAMP, 0, "access", MAXDATETIME,
    "MAXMTIME", 0, MAXTIMESTAMP, "modification", MAXDATETIME,
    "MINATIME", MINTIMESTAMP, 0, "access", MINDATETIME,
    "MINMTIME", 0, MINTIMESTAMP, "modification", MINDATETIME,
    "Y1KATIME", Y1KTIMESTAMP, 0, "access", Y1KDATETIME,
    "Y1KMTIME", 0, Y1KTIMESTAMP, "modification", Y1KDATETIME,
    "Y2KATIME", Y2KTIMESTAMP, 0, "access", Y2KDATETIME,
    "Y2KMTIME", 0, Y2KTIMESTAMP, "modification", Y2KDATETIME,
    "LESSATIME", LESSTIMESTAMP, 0, "access", LESSDATETIME,
    "LESSMTIME", 0, LESSTIMESTAMP, "modification", LESSDATETIME
};

#endif // AARU_FSTESTER_SETTER_SRC_UNIX_TIME_H_

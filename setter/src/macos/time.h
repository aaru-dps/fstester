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

#ifndef AARU_FSTESTER_SETTER_SRC_MACOS_TIME_H_
#define AARU_FSTESTER_SETTER_SRC_MACOS_TIME_H_

#define DATETIME_FORMAT "This file is dated %s for %s\r"
#define MAXDATETIME "2040/02/06 06:28:15"
#define MINDATETIME "1904/01/01 00:00:01"
#define NONDATETIME "1904/01/01 00:00:00"
#define Y2KDATETIME "2000/01/01 00:00:00"
#define Y1KDATETIME "1999/12/31 23:59:59"
#define MAXTIMESTAMP 0xFFFFFFFF
#define MINTIMESTAMP 0x00000001
#define NONTIMESTAMP 0x00000000
#define Y2KTIMESTAMP 0xB492F400
#define Y1KTIMESTAMP 0xB492F3FF

typedef struct
{
    char*   filename;
    LONGINT creation;
    LONGINT modification;
    LONGINT backup;
    char    type[13];
    char    message[20];
} mac_time_tests_t;

#define KNOWN_MAC_TIMES 17

static const mac_time_tests_t mac_times[KNOWN_MAC_TIMES] = {
    "\pMAXCTIME",   MAXTIMESTAMP,   NONTIMESTAMP, NONTIMESTAMP,   "creation",     MAXDATETIME,  "\pMAXMTIME",
    NONTIMESTAMP,   MAXTIMESTAMP,   NONTIMESTAMP, "modification", MAXDATETIME,    "\pMAXBTIME", NONTIMESTAMP,
    NONTIMESTAMP,   MAXTIMESTAMP,   "backup",     MAXDATETIME,    "\pMINCTIME",   MINTIMESTAMP, NONTIMESTAMP,
    NONTIMESTAMP,   "creation",     MINDATETIME,  "\pMINMTIME",   NONTIMESTAMP,   MINTIMESTAMP, NONTIMESTAMP,
    "modification", MINDATETIME,    "\pMINBTIME", NONTIMESTAMP,   NONTIMESTAMP,   MINTIMESTAMP, "backup",
    MINDATETIME,    "\pY2KCTIME",   Y2KTIMESTAMP, NONTIMESTAMP,   NONTIMESTAMP,   "creation",   Y2KDATETIME,
    "\pY2KMTIME",   NONTIMESTAMP,   Y2KTIMESTAMP, NONTIMESTAMP,   "modification", Y2KDATETIME,  "\pY2KBTIME",
    NONTIMESTAMP,   NONTIMESTAMP,   Y2KTIMESTAMP, "backup",       Y2KDATETIME,    "\pY1KCTIME", Y1KTIMESTAMP,
    NONTIMESTAMP,   NONTIMESTAMP,   "creation",   Y1KDATETIME,    "\pY1KMTIME",   NONTIMESTAMP, Y1KTIMESTAMP,
    NONTIMESTAMP,   "modification", Y1KDATETIME,  "\pY1KBTIME",   NONTIMESTAMP,   NONTIMESTAMP, Y1KTIMESTAMP,
    "backup",       Y1KDATETIME,    "\pMAXTIME",  MAXTIMESTAMP,   MAXTIMESTAMP,   MAXTIMESTAMP, "all",
    MAXDATETIME,    "\pMINTIME",    MINTIMESTAMP, MINTIMESTAMP,   MINTIMESTAMP,   "all",        MINDATETIME,
    "\pNOTIME",     NONTIMESTAMP,   NONTIMESTAMP, NONTIMESTAMP,   "all",          NONDATETIME,  "\pY1KTIME",
    Y1KTIMESTAMP,   Y1KTIMESTAMP,   Y1KTIMESTAMP, "all",          Y1KDATETIME,    "\pY2KTIME",  Y2KTIMESTAMP,
    Y2KTIMESTAMP,   Y2KTIMESTAMP,   "all",        Y2KDATETIME,
};

#endif // AARU_FSTESTER_SETTER_SRC_MACOS_TIME_H_

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

#ifndef SETTER_SRC_WIN32_TIME_H_
#define SETTER_SRC_WIN32_TIME_H_

#include <windows.h>

#define DATETIME_FORMAT "This file is dated %s for %s\r"
#define MAXDATETIME "60056/05/28 05:36:11"
#define MINDATETIME "1601/01/01 00:00:00"
#define Y2KDATETIME "2000/01/01 00:00:00"
#define Y1KDATETIME "1999/12/31 23:59:59"
#define MAXTIMESTAMP 0xFFFFFFFF
#define MINTIMESTAMP 0x00000000
#define TIMESTAMP_HI 0x01BF53EB
#define Y2KTIMESTAMP_LO 0x256D4000
#define Y1KTIMESTAMP_LO 0x24D4A980

typedef struct
{
    char     filename[9];
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    char     type[13];
    char     message[21];
} win32_time_tests_t;

#define KNOWN_WIN32_TIMESTAMPS 12

static const win32_time_tests_t win32_timestamps[KNOWN_WIN32_TIMESTAMPS] = {
    {"MAXCTIME", {MAXTIMESTAMP, MAXTIMESTAMP}, {0, 0}, {0, 0}, "creation", MAXDATETIME},
    {"MAXATIME", {0, 0}, {MAXTIMESTAMP, MAXTIMESTAMP}, {0, 0}, "access", MAXDATETIME},
    {"MAXMTIME", {0, 0}, {0, 0}, {MAXTIMESTAMP, MAXTIMESTAMP}, "modification", MAXDATETIME},
    {"MINCTIME", {MINTIMESTAMP, MINTIMESTAMP}, {0, 0}, {0, 0}, "creation", MINDATETIME},
    {"MINATIME", {0, 0}, {MINTIMESTAMP, MINTIMESTAMP}, {0, 0}, "access", MINDATETIME},
    {"MINMTIME", {0, 0}, {0, 0}, {MINTIMESTAMP, MINTIMESTAMP}, "modification", MINDATETIME},
    {"Y1KCTIME", {Y1KTIMESTAMP_LO, TIMESTAMP_HI}, {0, 0}, {0, 0}, "creation", Y1KDATETIME},
    {"Y1KATIME", {0, 0}, {Y1KTIMESTAMP_LO, TIMESTAMP_HI}, {0, 0}, "access", Y1KDATETIME},
    {"Y1KMTIME", {0, 0}, {0, 0}, {Y1KTIMESTAMP_LO, TIMESTAMP_HI}, "modification", Y1KDATETIME},
    {"Y2KCTIME", {Y2KTIMESTAMP_LO, TIMESTAMP_HI}, {0, 0}, {0, 0}, "creation", Y2KDATETIME},
    {"Y2KATIME", {0, 0}, {Y2KTIMESTAMP_LO, TIMESTAMP_HI}, {0, 0}, "access", Y2KDATETIME},
    {"Y2KMTIME", {0, 0}, {0, 0}, {Y2KTIMESTAMP_LO, TIMESTAMP_HI}, "modification", Y2KDATETIME},
};

#endif // SETTER_SRC_WIN32_TIME_H_

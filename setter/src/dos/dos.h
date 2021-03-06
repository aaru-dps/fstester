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

#if defined(__DOS__) || defined(MSDOS)

#ifndef AARU_FSTESTER_SETTER_SRC_DOS_H
#define AARU_FSTESTER_SETTER_SRC_DOS_H

#if defined(__WATCOM__)
#include <direct.h>
#define __dos_mkdir(a) mkdir(a)
#elif defined(__DJGPP__)
#include <sys/stat.h>
#define __dos_mkdir(path) mkdir(path, 0)
#endif

#if defined(__WATCOM__)
#pragma pack(__push, 1)
#else
#pragma pack(push, 1)
#endif

typedef struct diskfree_ex_t
{
    unsigned short size;
    unsigned short version;
    unsigned long  sectorsPerCluster;
    unsigned long  bytesPerSector;
    unsigned long  freeClusters;
    unsigned long  totalClusters;
    unsigned long  freeSectors;
    unsigned long  totalSectors;
    unsigned long  freeUnits;
    unsigned long  totalUnits;
    unsigned char  reserved[8];
} diskfree_ex;

unsigned int _dos_getdiskfree_ex(unsigned int drive, struct diskfree_ex_t* diskspace);

#if defined(__WATCOM__)
#pragma pack(__pop)
#else
#pragma pack(pop)
#endif

#define YEAR(t) (((t & 0xFE00) >> 9) + 1980)
#define MONTH(t) ((t & 0x01E0) >> 5)
#define DAY(t) (t & 0x001F)
#define HOUR(t) ((t & 0xF800) >> 11)
#define MINUTE(t) ((t & 0x07E0) >> 5)
#define SECOND(t) ((t & 0x001F) << 1)

#endif

#endif

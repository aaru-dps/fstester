/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : os2_16.h
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains 16-bit OS/2 definitions

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

#ifndef AARU_FSTESTER_SETTER_OS2_H
#define AARU_FSTESTER_SETTER_OS2_H

#include <os2.h>

#if(defined(__I86__) || defined(__i86__) || defined(_M_I86)) // 16 bit

#ifndef APIRET
#define APIRET USHORT
#endif

#define ACTION_RET USHORT

#else // 32 bit

#define ACTION_RET ULONG

#endif

/* Information level types (defins method of query) */
#ifndef FSAIL_QUERYNAME
#define FSAIL_QUERYNAME 1 /* Return data for a Drive or Device */
#endif

#ifndef FSAIL_DEVNUMBER
#define FSAIL_DEVNUMBER 2 /* Return data for Ordinal Device # */
#endif

#ifndef FSAIL_DRVNUMBER
#define FSAIL_DRVNUMBER 3 /* Return data for Ordinal Drive # */
#endif

/* Item types (from data structure item "iType") */
#ifndef FSAT_CHARDEV
#define FSAT_CHARDEV 1 /* Resident character device */
#endif

#ifndef FSAT_PSEUDODEV
#define FSAT_PSEUDODEV 2 /* Pseudo-character device */
#endif

#ifndef FSAT_LOCALDRV
#define FSAT_LOCALDRV 3 /* Local drive */
#endif

#ifndef FSAT_REMOTEDRV
#define FSAT_REMOTEDRV 4 /* Remote drive attached to FSD */
#endif

#if(defined(__I86__) || defined(__i86__) || defined(_M_I86)) // 16 bit

#define __os2_chdir(path) DosChDir(path, 0)
#define __os2_mkdir(path) DosMkDir(path, 0)
#define __os2_delete(path) DosDelete(path, 0);

#else // 32 bit

#define __os2_chdir(path) DosSetCurrentDir(path)
#define __os2_mkdir(path) DosCreateDir(path, NULL)
#define __os2_delete(path) DosDelete(path)

#endif

#endif

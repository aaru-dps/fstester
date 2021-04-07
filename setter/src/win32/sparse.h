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

#ifndef AARU_FSTESTER_SETTER_SRC_WIN32_SPARSE_H_
#define AARU_FSTESTER_SETTER_SRC_WIN32_SPARSE_H_

#include <windows.h>

#include "win32.h"

#ifndef FSCTL_SET_SPARSE
#define FSCTL_SET_SPARSE 0x000900C4
#endif

#ifndef FSCTL_SET_ZERO_DATA
#define FSCTL_SET_ZERO_DATA 0x000900C8
#endif

#define FSCTL_SET_SPARSE_OLD 0x000980C4
#define FSCTL_SET_ZERO_DATA_OLD 0x000980C8

typedef struct _WINNT_FILE_ZERO_DATA_INFORMATION
{
    LARGE_INTEGER FileOffset;
    LARGE_INTEGER BeyondFinalZero;
} WINNT_FILE_ZERO_DATA_INFORMATION, *PWINNT_FILE_ZERO_DATA_INFORMATION;

#ifndef FILE_SUPPORTS_SPARSE_FILES
#define FILE_SUPPORTS_SPARSE_FILES 0x0000040
#endif

#endif // AARU_FSTESTER_SETTER_SRC_WIN32_SPARSE_H_

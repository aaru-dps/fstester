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

#ifndef AARU_FSTESTER_SETTER_SRC_MACOS_H
#define AARU_FSTESTER_SETTER_SRC_MACOS_H

// Things not included in Retro68
#if defined(HAVE_MULTIVERSE_H)
#include "retro68.h"
#endif

#if !defined(FOUR_CHAR_CODE)
#if __option(enumsalwaysint) && __option(ANSI_strict)
#define FOUR_CHAR_CODE(x) ((long)x)
#else
#define FOUR_CHAR_CODE(x) (x)
#endif
#endif

enum
{
    gestaltMacOSCompatibilityBoxAttr = FOUR_CHAR_CODE('bbox'),
    ostAaru                          = FOUR_CHAR_CODE('aaru'),
    ostSimpleText                    = FOUR_CHAR_CODE('ttxt'),
    ostUnknown                       = FOUR_CHAR_CODE('????'),
    rtIcons                          = FOUR_CHAR_CODE('icns'),
    rtVersion                        = FOUR_CHAR_CODE('vers'),
};

#if __MWERKS__ <= 0x2100

// There's no MacTypes.h in old CodeWarrior
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

#define kHasNoINITs (0x0080) /* Files only (Extensions/Control Panels only) */

#if __MWERKS__ <= 0x1800
// Old CodeWarrior C library does not include snprintf()
int snprintf(char *str, size_t size, const char *format, ...);
#endif

enum
{
    gestaltHasHFSPlusAPIs = 12 /* file system supports HFS Plus APIs */
};

#define PBXGetVolInfo(pb, async) ((async) ? PBXGetVolInfoAsync(pb) : PBXGetVolInfoSync(pb))

#else
#include <MacTypes.h>
#endif

#endif

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

#include <MacTypes.h>

// Things not included in Retro68
#if defined(HAVE_MULTIVERSE_H)
#include "retro68.h"
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

#endif

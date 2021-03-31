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

#ifndef SETTER_SRC_BSD_H_
#define SETTER_SRC_BSD_H_

void BsdExtendedAttributes(const char* path);
void BsdFileAttributes(const char* path);

#if defined(__NetBSD__)
void NetBsdPrintStatvfsFlags(unsigned long flags);
#elif defined(__FreeBSD__)
#include <stdint.h>

void FreeBsdPrintStatfsFlags(uint64_t flags);
#endif

#endif // SETTER_SRC_BSD_H_

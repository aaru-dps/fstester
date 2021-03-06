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

#ifndef AARU_FSTESTER_SETTER_SRC_WIN32_LINKS_H_
#define AARU_FSTESTER_SETTER_SRC_WIN32_LINKS_H_

#include "win32.h"

static BOOL(WINAPI* WinNtCreateHardLinkA)(LPCSTR, LPCSTR, LPSECURITY_ATTRIBUTES);
static BOOL(WINAPI* WinNtCreateSymbolicLinkA)(LPCSTR, LPCSTR, DWORD);

#endif // AARU_FSTESTER_SETTER_SRC_WIN32_LINKS_H_

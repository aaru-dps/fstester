/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : xattr.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains common implementations for UNIX family and compatibles

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

#if defined(unix) || defined(UNIX) || defined(__unix) || defined(__unix__) || defined(__UNIX__)

#include "../include/defs.h"

#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)
#include "../linux/linux.h"
#endif

void ExtendedAttributes(const char* path)
{
#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)
    LinuxExtendedAttributes(path);
#endif
}

#endif

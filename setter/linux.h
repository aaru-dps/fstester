/****************************************************************************
The Disc Image Chef
-----------------------------------------------------------------------------

Filename       : linux.c
Author(s)      : Natalia Portillo

Component      : fstester.setter

--[ Description ] -----------------------------------------------------------

Contains Linux definitions

--[ License ] ---------------------------------------------------------------
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as
     published by the Free Software Foundation, either version 3 of the
     License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warraty of
     MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
Copyright (C) 2011-2018 Natalia Portillo
*****************************************************************************/

#ifndef SETTER_LINUX_H
#define SETTER_LINUX_H

#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)

void LinuxExtendedAttributes(const char *path);

#endif

#endif // SETTER_LINUX_H
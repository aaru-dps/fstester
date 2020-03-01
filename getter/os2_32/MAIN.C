/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : main.c
Author(s)      : Natalia Portillo

Component      : fstester.getter.os2

--[ Description ] -----------------------------------------------------------

Contains global definitions

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
Copyright (C) 2011-2020 Natalia Portillo
*****************************************************************************/

#include "dir.h"
#include "main.h"

#include <os2.h>
#include <stdio.h>

int main()
{
    ULONG eaCounter = 0;
    printf("Aaru Filesystem Tester (Getter) for OS/2 %s\n", DIC_FSTESTER_VERSION);
    printf("%s\n", DIC_COPYRIGHT);

    return GetAllInDir("C:", &eaCounter);
}

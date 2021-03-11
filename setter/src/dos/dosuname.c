/************************************************************************
  Claunia.com
 ------------------------------------------------------------------------

        Filename   : dosuname.c
        Version    : 0.09
        Author(s)  : Natalia Portillo

        Component : UNAME for DOS

 --[ Description ]-------------------------------------------------------

        Says the DOS type and version.

 --[ History ] ----------------------------------------------------------

        0.00: Original file by Natalia Portillo. No DOS type.
        0.01: Tested with following DOSes obtaining:
              DOS             DOS Version     DOS OEM Code
              DR-DOS 7.03     6.0             0x00
              FreeDOS Beta 4  6.22            0xFD
              MS-DOS 3.20     3.20            0x00
              MS-DOS 3.30     3.30            0x00
              MS-DOS 4.01     4.0             0xFF
              MS-DOS 5.00     5.0             0xFF
              PC-DOS 3.30     3.30            0x00
              Windows 98 S.E. 7.10            0xFF
              Windows 2000    5.0             0xFF
        0.02: Tested with the following DOSes obtaining:
              DOS             DOS Version     DOS OEM Code
              PTS-DOS 2000    6.22            0x66
              RxDOS 7.1.5     7.0             0x5E
        0.03: Almost remade from zero.
              Now uses four functions of INT-21h to get almost all
              DOS version information.
              All detect stuff moved to int21h.c.
              All defines moved to ver.h
        0.04: Implemented detection of DESQview, 4DOS and NDOS.
              Implemented detection of the Windows version.
              Implemented detection of OS/2.
              Implemented detection of Windows Millenium (tested with beta 3).
        0.05: Corrected an error with minor versions of OS/2 2.x and 1.x
              Implemented SoftICE debugger detection. But not tested.
              Translated to spanish and french.
              Corrected an error with DOS versions prior to 5.x when testing
              the true DOS version
        0.06: Implemented detection of Windows XP.
              Corrected an error with OS/2 2.x versions.
        0.07: Implemented a workaround so OS/2 3.x and upper versions can be
              easily detected, without exact knowledge of the versions by
              this program.
        0.08: Changed function parameters to use a struct.
        0.09: Use an enumeration for DOS flavor.

 --[ How to compile ]----------------------------------------------------

        Recommended compiler Borland Turbo C++ 1.01
                http://community.borland.com/museum

 --[ Where to get help/information ]-------------------------------------

        This archaic and abandoned software is opensource with no warranty
    or help of any kind.
    For inquiries contact claunia@claunia.com.

 --[ License ] ----------------------------------------------------------

        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License,or (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not,write to the Free Software
        Foundation,Inc.,59 Temple Place - Suite 330,Boston,MA  02111-1307,USA.

 ------------------------------------------------------------------------
 Copyright (c) 2001-2021 Natalia Portillo
*************************************************************************/

#include <dos.h>

#include "dosuname.h"

void getdosver(struct dosuname_version_t* version)
{
    union REGS regs;
    int        dos_temp, nt_flag;
    nt_flag         = 0;
    version->flavor = DOS_FLAVOR_UNKNOWN;

    regs.x.ax = 0x3306;        /* Set function 3306h */
    int86(0x21, &regs, &regs); /* Call INT 21h */
    if(regs.h.al != 255)       /* If DOS >= 5.0 */
    {
        version->major = regs.h.bl; /* Major True version */
        version->minor = regs.h.bh; /* Minor True version */
        if(regs.h.bh == 50)
        {
            version->minor = 0;
            nt_flag        = 1;
        }

        regs.h.ah = 0x30;
        regs.h.al = 0x00;
        int86(0x21, &regs, &regs);
        dos_temp = regs.h.bh; /* Set DOS type */
        if(dos_temp == 253)   /* Checks for FreeDOS */
        {
            version->major = regs.h.bl; /* Get FreeDOS kernel version */
            version->minor = 0;         /* Put minor version to zero */
        }
        version->simulated_major = regs.h.al; /* Set the simulated major version */
        version->simulated_minor = regs.h.ah; /* Set the simulated minor version */
    }
    else
    {
        regs.h.ah = 0x30;
        regs.h.al = 0x00;
        int86(0x21, &regs, &regs);
        dos_temp           = regs.h.bh; /* Set DOS type */
        version->major     = regs.h.al; /* Set the simulated major version */
        version->minor     = regs.h.ah; /* Set the simulated minor version */
        version->simulated_major = version->major;
        version->simulated_minor = version->minor;
    }

    /* Set DOS to DOS type */
    if(dos_temp == 0 && version->major <= 3) { version->flavor = DOS_FLAVOR_MSPCDOS; }
    if(dos_temp == 0 && version->major >= 4) { version->flavor = DOS_FLAVOR_PCDOS; }
    if(dos_temp == 0 && version->major >= 10) { version->flavor = DOS_FLAVOR_OS2; }
    if(dos_temp == 0xff && version->major <= 6) { version->flavor = DOS_FLAVOR_MSDOS; }
    if(dos_temp == 0xff && version->major == 7)
    {
        if(version->minor == 0) { version->flavor = DOS_FLAVOR_WIN95; }
        if(version->minor == 10) { version->flavor = DOS_FLAVOR_WIN9X; }
    }
    if(dos_temp == 0xff && version->major == 8) { version->flavor = DOS_FLAVOR_WINME; }
    if(dos_temp == 253) { version->flavor = DOS_FLAVOR_FREEDOS; }
    if(dos_temp == 0xff && nt_flag == 1) { version->flavor = DOS_FLAVOR_WINNT; }
    if(dos_temp == 0x66) { version->flavor = DOS_FLAVOR_PTSDOS; }
    if(dos_temp == 0x5E) { version->flavor = DOS_FLAVOR_RXDOS; }

    /* Check for Concurrent DOS versions */
    regs.x.ax = 0x4451;        /* Set function 4451h */
    int86(0x21, &regs, &regs); /* Call INT 21h */
    if(regs.h.al == 0x32)
    {
        version->major  = 3;
        version->minor  = 2;
        version->flavor = DOS_FLAVOR_CONCURRENTDOS;
    }
    if(regs.h.al == 0x41)
    {
        version->major  = 4;
        version->minor  = 1;
        version->flavor = DOS_FLAVOR_CONCURRENTDOS;
    }
    if(regs.h.al == 0x50)
    {
        version->major  = 5;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_CONCURRENTDOS;
    }
    if(regs.h.al == 0x60)
    {
        version->major  = 6;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_CONCURRENTDOS;
    }
    if(regs.h.al == 0x62)
    {
        version->major  = 6;
        version->minor  = 2;
        version->flavor = DOS_FLAVOR_CONCURRENTDOS;
    }
    if(regs.h.al == 0x66)
    {
        version->major  = 5;
        version->minor  = 1;
        version->flavor = DOS_FLAVOR_WINNT;
    }
    if(regs.h.al == 0x67)
    {
        version->major  = 5;
        version->minor  = 1;
        version->flavor = DOS_FLAVOR_CONCURRENTDOS;
    }
    /* End of check for Concurrent DOS versions */

    /* Check for DR-DOS versions */
    regs.x.ax = 0x4452;        /* Set function 4452h */
    int86(0x21, &regs, &regs); /* Call INT 21h */
    if(regs.h.al == 0x41)
    {
        version->major  = 1;
        version->minor  = 2;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x60)
    {
        version->major  = 2;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x63)
    {
        version->major  = 3;
        version->minor  = 41;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x64)
    {
        version->major  = 3;
        version->minor  = 42;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x65)
    {
        version->major  = 5;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x67)
    {
        version->major  = 6;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x71)
    {
        version->major  = 6;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    if(regs.h.al == 0x72)
    {
        version->major  = 7;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_NOVELLDOS;
    }
    if(regs.h.al == 0x73)
    {
        version->major  = 7;
        version->minor  = 0;
        version->flavor = DOS_FLAVOR_DRDOS;
    }
    /* End of check for DR-DOS_FLAVOR versions */
    version->dos_oem        = dos_temp;
    version->desqview_major = 0;
    version->desqview_minor = 0;
    regs.h.ah               = 0x2b;   /* Set function */
    regs.x.cx               = 0x4445; /* Set function */
    regs.x.dx               = 0x5351; /* Set function */
    regs.h.al               = 0x01;   /* Set function */
    int86(0x21, &regs, &regs);        /* Call INT 21h */
    if(regs.h.al != 0xFF)
    {
        version->desqview_major = regs.h.bh;
        version->desqview_minor = regs.h.bl;
    }
    version->_4dos_major = 0;
    version->_4dos_minor = 0;
    regs.h.bh            = 0x00;   /* Set function */
    regs.x.ax            = 0xD44D; /* Set 4DOS API */
    int86(0x2F, &regs, &regs);     /* Call INT 2Fh */
    if(regs.x.ax == 0x44DD)
    {
        version->_4dos_major = regs.h.bl;
        version->_4dos_minor = regs.h.bh;
    }
    version->ndos_major = 0;
    version->ndos_minor = 0;
    regs.h.bh           = 0x00;   /* Set function */
    regs.x.ax           = 0xE44D; /* Set 4DOS API (Well, NDOS is the Norton version of 4DOS */
    int86(0x2F, &regs, &regs);    /* Call INT 2Fh */
    if(regs.x.ax == 0x44EE)
    {
        version->ndos_major = regs.h.bl;
        version->ndos_minor = regs.h.bh;
    }
    version->windows_major = 0;
    version->windows_minor = 0;
    version->windows_mode  = 0;
    regs.x.ax              = 0x160A; /* Set function (Windows 3.1 or upper) */
    int86(0x2F, &regs, &regs);       /* Call INT 2Fh */
    if(regs.x.ax == 0x0000)
    {
        version->windows_major = regs.h.bh;
        version->windows_minor = regs.h.bl;
        version->windows_mode  = regs.x.cx;
    }
    else
    {
        regs.x.ax = 0x1600;        /* Set function (Windows/386 or upper in enhanced mode)*/
        int86(0x2F, &regs, &regs); /* Call INT 2Fh */
        if(regs.h.al == 0x01 || regs.h.al == 0xFF)
        {
            version->windows_major = 2;
            version->windows_minor = regs.h.ah;
            version->windows_mode  = 3;
        }
        else if(regs.h.al >= 3)
        {
            version->windows_major = regs.h.al;
            version->windows_minor = regs.h.ah;
            version->windows_mode  = 3;
        }
        else
            version->windows_major = version->windows_minor = 0;
    }
    regs.x.ax = 0x0000;        /* SoftICE detection function */
    regs.x.si = 0x4647;        /* SoftICE detection function */
    regs.x.di = 0x4A4D;        /* SoftICE detection function */
    int86(0x03, &regs, &regs); /* Call INT 03h */
    if(regs.x.si != 0x4647)
    {
        version->softice_major = 1; // SoftICE version detection not yet implemented
        version->softice_minor = 1; // SoftICE version detection not yet implemented
    }
    else
    {
        version->softice_major = 0; // SoftICE not detected
        version->softice_minor = 0; // SoftICE not detected
    }
}
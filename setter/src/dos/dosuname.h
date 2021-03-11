/************************************************************************
  Claunia.com
 ------------------------------------------------------------------------

        Filename   : dosuname.h
        Version    : 0.09
        Author(s)  : Natalia Portillo

        Component : UNAME for DOS

 --[ Description ]-------------------------------------------------------

        Says the DOS type and version.

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

#ifndef DOS_DOSUNAME_H_
#define DOS_DOSUNAME_H_

typedef enum
{
    DOS_FLAVOR_UNKNOWN,
    DOS_FLAVOR_MSDOS,
    DOS_FLAVOR_PCDOS,
    DOS_FLAVOR_DRDOS,
    DOS_FLAVOR_FREEDOS,
    DOS_FLAVOR_WIN95,
    DOS_FLAVOR_WINNT,
    DOS_FLAVOR_OS2,
    DOS_FLAVOR_PTSDOS,
    DOS_FLAVOR_RXDOS,
    DOS_FLAVOR_CONCURRENTDOS,
    DOS_FLAVOR_NOVELLDOS,
    DOS_FLAVOR_MSPCDOS,
    DOS_FLAVOR_WIN9X,
    DOS_FLAVOR_WINME,

} dosuname_flavor;

struct dosuname_version_t
{
    dosuname_flavor flavor;
    int             major;
    int             minor;
    int             simulated_major;
    int             simulated_minor;
    int             dos_oem;
    int             desqview_major;
    int             desqview_minor;
    int             _4dos_major;
    int             _4dos_minor;
    int             ndos_major;
    int             ndos_minor;
    int             windows_major;
    int             windows_minor;
    int             windows_mode;
    int             softice_major;
    int             softice_minor;
};

#endif // DOS_DOSUNAME_H_

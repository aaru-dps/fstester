/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : dos.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains DOS code

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

#if defined(__NETWARE_386__)

#include "netware.h"

#include "include/consts.h"
#include "include/defs.h"

void GetOsInfo()
{
    // TODO: Implement
}

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    // TODO: Implement
    *clusterSize = 0;
}

void FileAttributes(const char* path)
{
    // TODO: Implement
}

void FilePermissions(const char* path)
{
    // TODO: Implement
}

void ExtendedAttributes(const char* path)
{
    // TODO: Implement
}

void ResourceFork(const char* path)
{
    // TODO: Implement
}

void Filenames(const char* path)
{
    // TODO: Implement
}

void Timestamps(const char* path)
{
    // TODO: Implement
}

void DirectoryDepth(const char* path)
{
    // TODO: Implement
}

void Fragmentation(const char* path, size_t clusterSize)
{
    // TODO: Implement
}

void Sparse(const char* path)
{
    // TODO: Implement
}

void Links(const char* path)
{
    // TODO: Implement
}

void MillionFiles(const char* path)
{
    // TODO: Implement
}

void DeleteFiles(const char* path)
{
    // TODO: Implement
}

#endif

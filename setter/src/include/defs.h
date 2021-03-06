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

#ifndef AARU_FSTESTER_SETTER_SRC_DEFS_H
#define AARU_FSTESTER_SETTER_SRC_DEFS_H

#include <stddef.h>

void GetOsInfo(void);

void GetVolumeInfo(const char* path, size_t* clusterSize);

void FileAttributes(const char* path);

void FilePermissions(const char* path);

void ExtendedAttributes(const char* path);

void ResourceFork(const char* path);

void Filenames(const char* path);

void Timestamps(const char* path);

void DirectoryDepth(const char* path);

void Fragmentation(const char* path, size_t clusterSize);

void Sparse(const char* path);

void MillionFiles(const char* path);

void DeleteFiles(const char* path);

void Links(const char* path);

#define FILENAME_FORMAT "This file should be named \"%s\".\n"

#endif

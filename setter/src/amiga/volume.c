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

#include <dos/dos.h>
#include <proto/dos.h>
#include <stdio.h>
#include <string.h>

#include "../include/defs.h"
#include "../log.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    BPTR            pathLock;
    struct InfoData info;
    int             rc;
    long long       total, free;
    unsigned char   type[255];
    int             pos = 0;
    unsigned char   typeByte;

    *clusterSize = 0;

    memset(&info, 0, sizeof(struct InfoData));

    pathLock = Lock((CONST_STRPTR)path, SHARED_LOCK);

    if(!pathLock)
    {
        printf("Error %ld obtaining lock for the requested path\n", IoErr());

        return;
    }

    rc = Info(pathLock, &info);

    if(!rc)
    {
        printf("Error %ld obtaining lock for the requested path\n", IoErr());

        return;
    }

    *clusterSize = info.id_BytesPerBlock;

    total = info.id_NumBlocks * (long long)info.id_BytesPerBlock;
    free  = (info.id_NumBlocks - info.id_NumBlocksUsed) * (long long)info.id_BytesPerBlock;

    memset(type, 0, 255);

    typeByte = info.id_DiskType >> 24;

    if(typeByte < 0x20)
    {
        type[pos++] = '\\';

        if(typeByte <= 7) type[pos++] = typeByte + 0x30;
        else
        {
            type[pos++] = (typeByte / 8) + 0x30;
            type[pos++] = (typeByte % 8) + 0x30;
        }
    }
    else
        type[pos++] = typeByte;

    typeByte = (info.id_DiskType >> 16) & 0xFF;

    if(typeByte < 0x20)
    {
        type[pos++] = '\\';

        if(typeByte <= 7) type[pos++] = typeByte + 0x30;
        else
        {
            type[pos++] = (typeByte / 8) + 0x30;
            type[pos++] = (typeByte % 8) + 0x30;
        }
    }
    else
        type[pos++] = typeByte;

    typeByte = (info.id_DiskType >> 8) & 0xFF;

    if(typeByte < 0x20)
    {
        type[pos++] = '\\';

        if(typeByte <= 7) type[pos++] = typeByte + 0x30;
        else
        {
            type[pos++] = (typeByte / 8) + 0x30;
            type[pos++] = (typeByte % 8) + 0x30;
        }
    }
    else
        type[pos++] = typeByte;

    typeByte = info.id_DiskType & 0xFF;

    if(typeByte < 0x20)
    {
        type[pos++] = '\\';

        if(typeByte <= 7) type[pos++] = typeByte + 0x30;
        else
        {
            type[pos++] = (typeByte / 8) + 0x30;
            type[pos++] = (typeByte % 8) + 0x30;
        }
    }
    else
        type[pos++] = typeByte;

    log_write("Volume information:\n");

    log_write("\tPath: %s\n", path);
    log_write("\tDOS type: '%s'\n", type);
    log_write("\t%d bytes per block\n", info.id_BytesPerBlock);
    log_write("\t%ld blocks (%lld bytes)\n", info.id_NumBlocks, total);
    log_write("\t%ld blocks free (%lld bytes)\n", info.id_NumBlocks - info.id_NumBlocksUsed, free);
}

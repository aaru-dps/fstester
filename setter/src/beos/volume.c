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

#include <fs_info.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "volume.h"

#include "../include/defs.h"
#include "../log.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    fs_info fsinfo;
    dev_t   dev_no;
    int     ret;
    *clusterSize = 0;

    memset(&fsinfo, 0, sizeof(fs_info));

    log_write("Volume information:\n");

    log_write("\tPath: %s\n", path);

    dev_no = dev_for_path(path);

    if(dev_no < 0)
    {
        log_write("An error occurred while trying to get device number for specified path: %d", dev_no);

        return;
    }

    ret = fs_stat_dev(dev_no, &fsinfo);

    if(ret != B_OK)
    {
        log_write("Error %d when trying to get filesystem information from volume.", ret);
        return;
    }

    printf("\tDevice number: %ld\n", fsinfo.dev);
    printf("\tRoot inode number: %" PRIu64, fsinfo.root);
    printf("\tDevice number: %ld\n", fsinfo.flags);
    printf("\tBlock size: %" PRIu64 " bytes\n", fsinfo.block_size);
    printf("\tTotal blocks: %" PRIu64 " (%" PRIu64 " bytes)\n",
           fsinfo.total_blocks,
           fsinfo.total_blocks * fsinfo.block_size);
    printf(
        "\tFree blocks: %" PRIu64 " (%" PRIu64 " bytes)\n", fsinfo.free_blocks, fsinfo.free_blocks * fsinfo.block_size);
    printf("\tOptimal I/O size: %" PRIu64 " bytes\n", fsinfo.io_size);
    printf("\tTotal nodes: %" PRIu64 "\n", fsinfo.total_nodes);
    printf("\tAvailable nodes: %" PRIu64 "\n", fsinfo.free_nodes);
    printf("\tDevice name: %s\n", fsinfo.device_name);
    printf("\tVolume name: %s\n", fsinfo.volume_name);
    printf("\tFilesystem: %s\n", fsinfo.fsh_name);
    printf("\tFlags:\n");

    if(fsinfo.flags & B_FS_IS_READONLY)
    {
        log_write("\t\tVolume is read-only.\n");
        fsinfo.flags -= B_FS_IS_READONLY;
    }

    if(fsinfo.flags & B_FS_IS_REMOVABLE)
    {
        log_write("\t\tVolume is removable.\n");
        fsinfo.flags -= B_FS_IS_REMOVABLE;
    }

    if(fsinfo.flags & B_FS_IS_PERSISTENT)
    {
        log_write("\t\tVolume written data persists when the device is off.\n");
        fsinfo.flags -= B_FS_IS_PERSISTENT;
    }

    if(fsinfo.flags & B_FS_IS_SHARED)
    {
        log_write("\t\tVolume is shared.\n");
        fsinfo.flags -= B_FS_IS_SHARED;
    }

    if(fsinfo.flags & B_FS_HAS_MIME)
    {
        log_write("\t\tVolume supports the MIME typing system.\n");
        fsinfo.flags -= B_FS_HAS_MIME;
    }

    if(fsinfo.flags & B_FS_HAS_ATTR)
    {
        log_write("\t\tVolume supports extended attributes.\n");
        fsinfo.flags -= B_FS_HAS_ATTR;
    }

    if(fsinfo.flags & B_FS_HAS_QUERY)
    {
        log_write("\t\tVolume supports queries.\n");
        fsinfo.flags -= B_FS_HAS_QUERY;
    }

    if(fsinfo.flags & B_FS_HAS_SELF_HEALING_LINKS)
    {
        log_write("\t\tVolume has self-healing links.\n");
        fsinfo.flags -= B_FS_HAS_SELF_HEALING_LINKS;
    }

    if(fsinfo.flags & B_FS_HAS_ALIASES)
    {
        log_write("\t\tVolume supports aliases.\n");
        fsinfo.flags -= B_FS_HAS_ALIASES;
    }

    if(fsinfo.flags & B_FS_SUPPORTS_NODE_MONITORING)
    {
        log_write("\t\tVolume supports monitoring a node.\n");
        fsinfo.flags -= B_FS_SUPPORTS_NODE_MONITORING;
    }

    if(fsinfo.flags & B_FS_SUPPORTS_MONITOR_CHILDREN)
    {
        log_write("\t\tVolume supports monitoring the children of a node.\n");
        fsinfo.flags -= B_FS_SUPPORTS_MONITOR_CHILDREN;
    }

    if(fsinfo.flags) log_write("\t\tRemaining flags: 0x%08lX\n", fsinfo.flags);

    *clusterSize = fsinfo.block_size;
}

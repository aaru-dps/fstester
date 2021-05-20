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

#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/attr.h>
#include <unistd.h>

#include "volume.h"

#include "../../log.h"

void DarwinPrintStatfsFlags(uint32_t flags)
{
    if(flags & MNT_RDONLY)
    {
        log_write("\t\tVolume is read-only.\n");
        flags -= MNT_RDONLY;
    }

    if(flags & MNT_SYNCHRONOUS)
    {
        log_write("\t\tVolume is written to synchronously.\n");
        flags -= MNT_SYNCHRONOUS;
    }

    if(flags & MNT_NOEXEC)
    {
        log_write("\t\tCannot exec from volume.\n");
        flags -= MNT_NOEXEC;
    }

    if(flags & MNT_NOSUID)
    {
        log_write("\t\tVolume does not honor setuid bits.\n");
        flags -= MNT_NOSUID;
    }

    if(flags & MNT_NODEV)
    {
        log_write("\t\tVolume doesn't interpret special files.\n");
        flags -= MNT_NODEV;
    }

    if(flags & MNT_UNION)
    {
        log_write("\t\tMount point is a union.\n");
        flags -= MNT_UNION;
    }

    if(flags & MNT_ASYNC)
    {
        log_write("\t\tVolume is written to asynchronously.\n");
        flags -= MNT_ASYNC;
    }

    if(flags & MNT_CPROTECT)
    {
        log_write("\t\tVolume supports per-file encryption.\n");
        flags -= MNT_CPROTECT;
    }

    if(flags & MNT_EXPORTED)
    {
        log_write("\t\tVolume is exported by NFS.\n");
        flags -= MNT_EXPORTED;
    }

    if(flags & MNT_REMOVABLE)
    {
        log_write("\t\tVolume is removable.\n");
        flags -= MNT_REMOVABLE;
    }

    if(flags & MNT_QUARANTINE)
    {
        log_write("\t\tVolume is quarantined.\n");
        flags -= MNT_QUARANTINE;
    }

    if(flags & MNT_LOCAL)
    {
        log_write("\t\tVolume is local.\n");
        flags -= MNT_LOCAL;
    }

    if(flags & MNT_QUOTA)
    {
        log_write("\t\tVolume supports quotas.\n");
        flags -= MNT_QUOTA;
    }

    if(flags & MNT_ROOTFS)
    {
        log_write("\t\tVolume is the root of the filesystem.\n");
        flags -= MNT_ROOTFS;
    }

    if(flags & MNT_DOVOLFS)
    {
        log_write("\t\tVolume supports volfs.\n");
        flags -= MNT_DOVOLFS;
    }

    if(flags & MNT_DONTBROWSE)
    {
        log_write("\t\tVolume is not appropriate for user data.\n");
        flags -= MNT_DONTBROWSE;
    }

    if(flags & MNT_IGNORE_OWNERSHIP)
    {
        log_write("\t\tVolume does not respect ownership.\n");
        flags -= MNT_IGNORE_OWNERSHIP;
    }

    if(flags & MNT_AUTOMOUNTED)
    {
        log_write("\t\tVolume was mounted by automounter.\n");
        flags -= MNT_AUTOMOUNTED;
    }

    if(flags & MNT_JOURNALED)
    {
        log_write("\t\tVolume is journaled.\n");
        flags -= MNT_JOURNALED;
    }

    if(flags & MNT_NOUSERXATTR)
    {
        log_write("\t\tVolume does not allow user extended attributes.\n");
        flags -= MNT_NOUSERXATTR;
    }

    if(flags & MNT_DEFWRITE)
    {
        log_write("\t\tVolume defers writes.\n");
        flags -= MNT_DEFWRITE;
    }

    if(flags & MNT_MULTILABEL)
    {
        log_write("\t\tVolume supports MAC for individual labels.\n");
        flags -= MNT_MULTILABEL;
    }

    if(flags & MNT_NOATIME)
    {
        log_write("\t\tVolume does not update access time.\n");
        flags -= MNT_NOATIME;
    }

    if(flags & MNT_SNAPSHOT)
    {
        log_write("\t\tMountpoint is a snapshot.\n");
        flags -= MNT_SNAPSHOT;
    }

    if(flags & MNT_STRICTATIME)
    {
        log_write("\t\tVolume strictly updates access time.\n");
        flags -= MNT_STRICTATIME;
    }

    if(flags) { log_write("\t\tRemaining flags: 0x%08lX\n", flags); }
}

typedef struct attrlist attrlist_t;

void DarwinVolumeAttributes(const char* path)
{
    int                     ret;
    attrlist_t              attrList;
    vol_capabilities_attr_t attrBuf;
    u_int32_t               capabilities_valid;

    memset(&attrList, 0, sizeof(attrList));
    memset(&attrBuf, 0, sizeof(vol_capabilities_attr_t));

    attrList.bitmapcount = ATTR_BIT_MAP_COUNT;
    attrList.volattr     = ATTR_VOL_CAPABILITIES;

    ret = getattrlist(path, &attrList, &attrBuf, sizeof(attrBuf), 0);
    if(ret)
    {
        log_write("Error %d retrieving volume capabilities.\n", errno);
        return;
    }

    log_write("Darwin volume capabilities:\n");

    capabilities_valid = attrBuf.valid[VOL_CAPABILITIES_FORMAT];

    if(capabilities_valid & VOL_CAP_FMT_PERSISTENTOBJECTIDS)
    {
        log_write("\tVolume has persistent object IDs.\n");
        capabilities_valid -= VOL_CAP_FMT_PERSISTENTOBJECTIDS;
    }

    if(capabilities_valid & VOL_CAP_FMT_SYMBOLICLINKS)
    {
        log_write("\tVolume supports symbolic links.\n");
        capabilities_valid -= VOL_CAP_FMT_SYMBOLICLINKS;
    }

    if(capabilities_valid & VOL_CAP_FMT_HARDLINKS)
    {
        log_write("\tVolume supports hard links\n");
        capabilities_valid -= VOL_CAP_FMT_HARDLINKS;
    }

    if(capabilities_valid & VOL_CAP_FMT_JOURNAL)
    {
        log_write("\tVolume support recovery journal\n");
        capabilities_valid -= VOL_CAP_FMT_JOURNAL;
    }

    if(capabilities_valid & VOL_CAP_FMT_JOURNAL_ACTIVE)
    {
        log_write("\tVolume is using a recovery journal\n");
        capabilities_valid -= VOL_CAP_FMT_JOURNAL_ACTIVE;
    }

    if(capabilities_valid & VOL_CAP_FMT_NO_ROOT_TIMES)
    {
        log_write("\tVolume does not store reliable times for the root directory\n");
        capabilities_valid -= VOL_CAP_FMT_NO_ROOT_TIMES;
    }

    if(capabilities_valid & VOL_CAP_FMT_SPARSE_FILES)
    {
        log_write("\tVolume supports sparse files\n");
        capabilities_valid -= VOL_CAP_FMT_SPARSE_FILES;
    }

    if(capabilities_valid & VOL_CAP_FMT_ZERO_RUNS)
    {
        log_write("\tVolume returns zeros for parts of a file that have never been written\n");
        capabilities_valid -= VOL_CAP_FMT_ZERO_RUNS;
    }

    if(capabilities_valid & VOL_CAP_FMT_CASE_SENSITIVE)
    {
        log_write("\tVolume uses case sensitive name comparison\n");
        capabilities_valid -= VOL_CAP_FMT_CASE_SENSITIVE;
    }

    if(capabilities_valid & VOL_CAP_FMT_CASE_PRESERVING)
    {
        log_write("\tVolume uses case insensitive name comparison but stores names with cases\n");
        capabilities_valid -= VOL_CAP_FMT_CASE_PRESERVING;
    }

    if(capabilities_valid & VOL_CAP_FMT_FAST_STATFS)
    {
        log_write("\tVolume returns from statfs(2) fast enough to not need to cache it\n");
        capabilities_valid -= VOL_CAP_FMT_FAST_STATFS;
    }

    if(capabilities_valid & VOL_CAP_FMT_2TB_FILESIZE)
    {
        log_write("\tVolume supports file sizes larger than 4Gb, up to AT LEAST 2Tb (or higher)\n");
        capabilities_valid -= VOL_CAP_FMT_2TB_FILESIZE;
    }

    if(capabilities_valid & VOL_CAP_FMT_OPENDENYMODES)
    {
        log_write("\tVolume support deny modes when opening files\n");
        capabilities_valid -= VOL_CAP_FMT_OPENDENYMODES;
    }

    if(capabilities_valid & VOL_CAP_FMT_HIDDEN_FILES)
    {
        log_write("\tVolume supports the hidden/invisible flag\n");
        capabilities_valid -= VOL_CAP_FMT_HIDDEN_FILES;
    }

    if(capabilities_valid & VOL_CAP_FMT_PATH_FROM_ID)
    {
        log_write("\tVolume can derive a path from an object ID\n");
        capabilities_valid -= VOL_CAP_FMT_PATH_FROM_ID;
    }

    if(capabilities_valid & VOL_CAP_FMT_NO_VOLUME_SIZES)
    {
        log_write("\tVolume sizes in blocks returned in statfs(2) are not valid\n");
        capabilities_valid -= VOL_CAP_FMT_NO_VOLUME_SIZES;
    }

    if(capabilities_valid & VOL_CAP_FMT_DECMPFS_COMPRESSION)
    {
        log_write("\tVolume transparently decompresses files\n");
        capabilities_valid -= VOL_CAP_FMT_DECMPFS_COMPRESSION;
    }

    if(capabilities_valid & VOL_CAP_FMT_64BIT_OBJECT_IDS)
    {
        log_write("\tVolume object IDs are 64-bit long\n");
        capabilities_valid -= VOL_CAP_FMT_64BIT_OBJECT_IDS;
    }

    if(capabilities_valid & VOL_CAP_FMT_DIR_HARDLINKS)
    {
        log_write("\tVolume supports directory hard links\n");
        capabilities_valid -= VOL_CAP_FMT_DIR_HARDLINKS;
    }

    if(capabilities_valid & VOL_CAP_FMT_DOCUMENT_ID)
    {
        log_write("\tVolume supports document IDs with revisions\n");
        capabilities_valid -= VOL_CAP_FMT_DOCUMENT_ID;
    }

    if(capabilities_valid & VOL_CAP_FMT_WRITE_GENERATION_COUNT)
    {
        log_write("\tVolume supports write generation count\n");
        capabilities_valid -= VOL_CAP_FMT_WRITE_GENERATION_COUNT;
    }

    if(capabilities_valid & VOL_CAP_FMT_NO_IMMUTABLE_FILES)
    {
        log_write("\tVolume does not support the immutable flag\n");
        capabilities_valid -= VOL_CAP_FMT_NO_IMMUTABLE_FILES;
    }

    if(capabilities_valid & VOL_CAP_FMT_NO_PERMISSIONS)
    {
        log_write("\tVolume does not support setting file permissions\n");
        capabilities_valid -= VOL_CAP_FMT_NO_PERMISSIONS;
    }

    if(capabilities_valid & VOL_CAP_FMT_SHARED_SPACE)
    {
        log_write("\tVolume support sharing space with multiple volumes\n");
        capabilities_valid -= VOL_CAP_FMT_SHARED_SPACE;
    }

    if(capabilities_valid & VOL_CAP_FMT_VOL_GROUPS)
    {
        log_write("\tVolume supports mounting several volumes at once\n");
        capabilities_valid -= VOL_CAP_FMT_VOL_GROUPS;
    }

    if(capabilities_valid & VOL_CAP_FMT_SEALED)
    {
        log_write("\tVolume is cryptographically sealed\n");
        capabilities_valid -= VOL_CAP_FMT_SEALED;
    }
}
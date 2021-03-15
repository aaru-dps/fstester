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

#include "volume.h"

#include "../log.h"

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
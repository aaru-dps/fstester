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

#ifdef HAVE_SYS_STATFS_H
#include <sys/statfs.h>
#elif defined(HAVE_SYS_VFS_H)
#include <sys/vfs.h>
#else
#warning statfs not found, will use custom redefinition of flags
#endif

#include "../../log.h"
#include "volume.h"

void LinuxPrintStatfsFlags(long flags)
{
    log_write("\tFlags:\n");

    if(flags & ST_RDONLY)
    {
        log_write("\t\tVolume is read-only.\n");
        flags -= ST_RDONLY;
    }

    if(flags & ST_NOSUID)
    {
        log_write("\t\tVolume ignores suid and sgid bits.\n");
        flags -= ST_NOSUID;
    }

    if(flags & ST_NODEV)
    {
        log_write("\t\tVolume disallows access to device special files.\n");
        flags -= ST_NODEV;
    }

    if(flags & ST_NOEXEC)
    {
        log_write("\t\tVolume disallows program execution.\n");
        flags -= ST_NOEXEC;
    }

    if(flags & ST_SYNCHRONOUS)
    {
        log_write("\t\tVolume writes are synced at once.\n");
        flags -= ST_SYNCHRONOUS;
    }

    if(flags & ST_MANDLOCK)
    {
        log_write("\t\tVolume allows mandatory locks.\n");
        flags -= ST_MANDLOCK;
    }

    if(flags & ST_WRITE)
    {
        log_write("\t\tVolume writes on file/directory/symlink.\n");
        flags -= ST_WRITE;
    }

    if(flags & ST_APPEND)
    {
        log_write("\t\tVolume appends.\n");
        flags -= ST_APPEND;
    }

    if(flags & ST_IMMUTABLE)
    {
        log_write("\t\tVolume is immutable.\n");
        flags -= ST_IMMUTABLE;
    }

    if(flags & ST_NOATIME)
    {
        log_write("\t\tVolume does not update access times.\n");
        flags -= ST_NOATIME;
    }

    if(flags & ST_NODIRATIME)
    {
        log_write("\t\tVolume does not update directory access times.\n");
        flags -= ST_NODIRATIME;
    }

    if(flags) { log_write("\t\tRemaining flags: 0x%08lX\n", flags); }
}
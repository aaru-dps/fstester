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

#ifdef HAVE_SYS_STATVFS_H
#include <sys/statvfs.h>
#endif

#include "../../log.h"
#include "volume.h"

#if defined(__NetBSD__)
void NetBsdPrintStatvfsFlags(unsigned long flags)
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

    if(flags & ST_NOATIME)
    {
        log_write("\t\tVolume does not update access times.\n");
        flags -= ST_NOATIME;
    }

    if(flags & ST_UNION)
    {
        log_write("\t\tVolume is a union.\n");
        flags -= ST_UNION;
    }

    if(flags & ST_ASYNC)
    {
        log_write("\t\tVolume is written asynchronously.\n");
        flags -= ST_ASYNC;
    }

    if(flags & ST_NOCOREDUMP)
    {
        log_write("\t\tVolume shall not have core dumps written.\n");
        flags -= ST_NOCOREDUMP;
    }

    if(flags & ST_RELATIME)
    {
        log_write("\t\tVolume only updates access time on changes.\n");
        flags -= ST_RELATIME;
    }

    if(flags & ST_IGNORE)
    {
        log_write("\t\tVolume does not appear in df.\n");
        flags -= ST_IGNORE;
    }

    if(flags & ST_SYMPERM)
    {
        log_write("\t\tVolume recognizes symbolic link permissions.\n");
        flags -= ST_SYMPERM;
    }

    if(flags & ST_NODEVMTIME)
    {
        log_write("\t\tVolume does not update modification times for devices.\n");
        flags -= ST_NODEVMTIME;
    }

    if(flags & ST_SOFTDEP)
    {
        log_write("\t\tVolume uses soft dependencies.\n");
        flags -= ST_SOFTDEP;
    }

    if(flags & ST_LOG)
    {
        log_write("\t\tVolume uses logging.\n");
        flags -= ST_LOG;
    }

    if(flags & ST_EXTATTR)
    {
        log_write("\t\tVolume has extended attributes enabled.\n");
        flags -= ST_EXTATTR;
    }

    if(flags & ST_EXRDONLY)
    {
        log_write("\t\tVolume is exported read-only.\n");
        flags -= ST_EXRDONLY;
    }

    if(flags & ST_EXPORTED)
    {
        log_write("\t\tVolume is exported.\n");
        flags -= ST_EXPORTED;
    }

    if(flags & ST_DEFEXPORTED)
    {
        log_write("\t\tVolume is exported to the world.\n");
        flags -= ST_DEFEXPORTED;
    }

    if(flags & ST_EXPORTANON)
    {
        log_write("\t\tVolume uses anon id.\n");
        flags -= ST_EXPORTANON;
    }

    if(flags & ST_EXKERB)
    {
        log_write("\t\tVolume is exported with Kerberos ID.\n");
        flags -= ST_EXKERB;
    }

    if(flags & ST_EXNORESPORT)
    {
        log_write("\t\tVolume export does not enforce reserved ports.\n");
        flags -= ST_EXNORESPORT;
    }

    if(flags & ST_EXPUBLIC)
    {
        log_write("\t\tVolume is exported publicly.\n");
        flags -= ST_EXPUBLIC;
    }

    if(flags & ST_LOCAL)
    {
        log_write("\t\tVolume is local.\n");
        flags -= ST_LOCAL;
    }

    if(flags & ST_QUOTA)
    {
        log_write("\t\tVolume has quotas enabled.\n");
        flags -= ST_QUOTA;
    }

    if(flags & ST_ROOTFS)
    {
        log_write("\t\tVolume is the root filesystem.\n");
        flags -= ST_ROOTFS;
    }

    if(flags & ST_DISCARD)
    {
        log_write("\t\tVolume is TRIMmed/DISCARDed.\n");
        flags -= ST_DISCARD;
    }

    if(flags & ST_AUTOMOUNTED)
    {
        log_write("\t\tVolume is automounted.\n");
        flags -= ST_AUTOMOUNTED;
    }

    if(flags) { log_write("\t\tRemaining flags: 0x%08lX\n", flags); }
}
#endif
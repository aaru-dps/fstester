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

#ifndef AARU_FSTESTER_SETTER_SRC_BSD_ATTR_H_
#define AARU_FSTESTER_SETTER_SRC_BSD_ATTR_H_

#include <sys/stat.h>

typedef struct
{
    char         filename[16];
    char         contents[256];
    char         description[256];
    unsigned int attr;
} bsd_attr_tests_t;

#if defined(__FreeBSD__)
#define KNOWN_BSD_ATTRS 17
#elif defined(__DragonFly__)
#define KNOWN_BSD_ATTRS 15
#elif defined(__NetBSD__)
#define KNOWN_BSD_ATTRS 10
#else
#define KNOWN_BSD_ATTRS 7
#endif

#ifndef UF_NODUMP
#define UF_NODUMP 0x00000001 /* Do not dump the file. */
#endif

#ifndef UF_IMMUTABLE
#define UF_IMMUTABLE 0x00000002 /* The file may not be changed. */
#endif

#ifndef UF_APPEND
#define UF_APPEND 0x00000004 /* The file may only be appended to. */
#endif

#ifndef UF_OPAQUE
#define UF_OPAQUE 0x00000008 /* directory is opaque wrt. union */
#endif

#ifndef SF_ARCHIVED
#define SF_ARCHIVED 0x00010000 /* file is archived */
#endif

#ifndef SF_IMMUTABLE
#define SF_IMMUTABLE 0x00020000 /* The file may not be changed. */
#endif

#ifndef SF_APPEND
#define SF_APPEND 0x00040000 /* The file may only be appended to. */
#endif

#if defined(__FreeBSD__) || defined(__DragonFly__)
#ifndef UF_NOUNLINK
#define UF_NOUNLINK 0x00000010 /* file may not be removed or renamed */
#endif

#ifndef SF_NOUNLINK
#define SF_NOUNLINK 0x00100000 /* file may not be removed or renamed */
#endif
#endif // FreeBSD or DragonFly BSD

#if defined(__FreeBSD__) || defined(__NetBSD__)
#ifndef SF_SNAPSHOT
#define SF_SNAPSHOT 0x00200000 /* snapshot inode */
#endif
#endif // FreeBSD or NetBSD

#if defined(__NetBSD__)
#ifndef SF_LOG
#define SF_LOG 0x00400000 /* WAPBL log file inode */
#endif

#ifndef SF_SNAPINVAL
#define SF_SNAPINVAL 0x00800000 /* snapshot is invalid */
#endif
#endif // NetBSD

#if defined(__FreeBSD__)
#ifndef UF_SYSTEM
#define UF_SYSTEM 0x00000080 /* Windows system file bit */
#endif

#ifndef UF_SPARSE
#define UF_SPARSE 0x00000100 /* sparse file */
#endif

#ifndef UF_OFFLINE
#define UF_OFFLINE 0x00000200 /* file is offline */
#endif

#ifndef UF_REPARSE
#define UF_REPARSE 0x00000400 /* Windows reparse point file bit */
#endif

#ifndef UF_ARCHIVE
#define UF_ARCHIVE 0x00000800 /* file needs to be archived */
#endif

#ifndef UF_READONLY
#define UF_READONLY 0x00001000 /* Windows readonly file bit */
#endif

#ifndef UF_HIDDEN
#define UF_HIDDEN 0x00008000 /* file is hidden */
#endif
#endif // FreeBSD

#if defined(__DragonFly__)
#ifndef UF_NOHISTORY
#define UF_NOHISTORY 0x00000040 /* do not retain history/snapshots */
#endif

#ifndef UF_CACHE
#define UF_CACHE 0x00000080 /* enable data swapcache */
#endif

#ifndef UF_XLINK
#define UF_XLINK 0x00000100 /* cross-link (hardlink) boundary */
#endif

#ifndef SF_NOHISTORY
#define SF_NOHISTORY 0x00400000 /* do not retain history/snapshots */
#endif

#ifndef SF_NOCACHE
#define SF_NOCACHE 0x00800000 /* disable data swapcache */
#endif

#ifndef SF_XLINK
#define SF_XLINK 0x01000000 /* cross-link (hardlink) boundary */
#endif
#endif // DragonFly BSD

static const bsd_attr_tests_t darwin_attrs[KNOWN_BSD_ATTRS] = {
    {"NODUMP", "This file is now not dumpable", "File with no dump flag", UF_NODUMP},
    {"IMMUTABLE", "This file is now immutable", "File with immutable flag", UF_IMMUTABLE},
    {"APPEND", "This file is now append only", "File with append only flag", UF_APPEND},
    {"ARCHIVED", "This file is now archived", "File with archived flag", SF_ARCHIVED},
    {"SF_IMMUTABLE",
     "This file is now immutable, and only the super-user change change that",
     "File with super-usr immutable flag",
     SF_IMMUTABLE},
    {"SF_APPEND",
     "This file is now append only, and only the super-user change change that",
     "File with super-user append only flag",
     SF_APPEND},
    {"OPAQUE", "This directory is opaque when viewed through a union stack", "File with opaque flag", UF_OPAQUE},

#if defined(__FreeBSD__) || defined(__DragonFly__)
    {"NOUNLINK", "This file may not be removed or renamed", "File with no unlink flag", UF_NOUNLINK},
    {"SF_NOUNLINK", "This file may not be removed or renamed", "File with super-user no unlink flag", SF_NOUNLINK},
#endif

#if(defined(__FreeBSD__) || defined(__NetBSD__)) && !defined(__DragonFly__)
    {"SF_SNAPSHOT", "This file is a snapshot", "File with super-user snapshot flag", SF_SNAPSHOT},
#endif

#if defined(__NetBSD__)
    {"SF_LOG", "This file is a WAPBL log file", "File with super-user log flag", SF_LOG},
    {"SF_SNAPINVAL", "This file is an invalid snapshot", "File with super-user invalid snapshot flag", SF_SNAPINVAL},
#endif

#if defined(__FreeBSD__) && !defined(__DragonFly__)
    {"SYSTEM", "This file is a system file for Windows", "File with system flag", UF_SYSTEM},
    {"SPARSE", "This file is sparse", "File with sparse flag", UF_SPARSE},
    {"OFFLINE", "This file is available offline for Windows", "File with offline flag", UF_OFFLINE},
    {"REPARSE", "This file is a Windows reparse point", "File with reparse flag", UF_REPARSE},
    {"ARCHIVE", "This file is must be archived", "File with archive flag", UF_ARCHIVE},
    {"READONLY", "This file is read-only for Windows", "File with read-only flag", UF_READONLY},
    {"HIDDEN", "This file is hidden", "File with hidden flag", UF_HIDDEN},
#endif

#if defined(__DragonFly__)
    {"NOHISTORY", "This file will not retain history/snapshots", "File with no history flag", UF_NOHISTORY},
    {"CACHE", "This file has data swapcache enabled", "File with cache flag", UF_CACHE},
    {"XLINK", "This file is a cross link boundary", "File with crosslink flag", UF_XLINK},
    {"SF_NOHISTORY",
     "This file will not retain history/snapshots",
     "File with super-user no history flag",
     SF_NOHISTORY},
    {"SF_NOCACHE", "This file must not have data swapcache enabled", "File with super-user no cache flag", SF_NOCACHE},
    {"SF_XLINK", "This file is a cross link boundary", "File with super-user crosslink flag", SF_XLINK},
#endif
};

#endif // AARU_FSTESTER_SETTER_SRC_BSD_ATTR_H_

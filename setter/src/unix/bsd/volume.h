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

#ifndef AARU_FSTESTER_SETTER_SRC_BSD_VOLUME_H_
#define AARU_FSTESTER_SETTER_SRC_BSD_VOLUME_H_

#if defined(HAVE_SYS_STATVFS_H)
#include <sys/statvfs.h>
#endif

#if defined(HAVE_SYS_MOUNT_H)
#include <sys/mount.h>
#endif

#if defined(__NetBSD__)
#ifndef ST_RDONLY
#define ST_RDONLY 0x00000001 /* read only filesystem */
#endif

#ifndef ST_SYNCHRONOUS
#define ST_SYNCHRONOUS 0x00000002 /* file system written synchronously */
#endif

#ifndef ST_NOEXEC
#define ST_NOEXEC 0x00000004 /* can't exec from filesystem */
#endif

#ifndef ST_NOSUID
#define ST_NOSUID 0x00000008 /* don't honor setuid bits on fs */
#endif

#ifndef ST_NODEV
#define ST_NODEV 0x00000010 /* don't interpret special files */
#endif

#ifndef ST_UNION
#define ST_UNION 0x00000020 /* union with underlying filesystem */
#endif

#ifndef ST_ASYNC
#define ST_ASYNC 0x00000040 /* file system written asynchronously */
#endif

#ifndef ST_NOCOREDUMP
#define ST_NOCOREDUMP 0x00008000 /* don't write core dumps to this FS */
#endif

#ifndef ST_RELATIME
#define ST_RELATIME 0x00020000 /* only update access time if mod/ch */
#endif

#ifndef ST_IGNORE
#define ST_IGNORE 0x00100000 /* don't show entry in df */
#endif

#ifndef ST_DISCARD
#define ST_DISCARD 0x00800000 /* use DISCARD/TRIM if supported */
#endif

#ifndef ST_EXTATTR
#define ST_EXTATTR 0x01000000 /* enable extended attributes */
#endif

#ifndef ST_LOG
#define ST_LOG 0x02000000 /* Use logging */
#endif

#ifndef ST_NOATIME
#define ST_NOATIME 0x04000000 /* Never update access times in fs */
#endif

#ifndef ST_AUTOMOUNTED
#define ST_AUTOMOUNTED 0x10000000 /* mounted by automountd(8) */
#endif

#ifndef ST_SYMPERM
#define ST_SYMPERM 0x20000000 /* recognize symlink permission */
#endif

#ifndef ST_NODEVMTIME
#define ST_NODEVMTIME 0x40000000 /* Never update mod times for devs */
#endif

#ifndef ST_SOFTDEP
#define ST_SOFTDEP 0x80000000 /* Use soft dependencies */
#endif

#ifndef ST_EXRDONLY
#define ST_EXRDONLY 0x00000080 /* exported read only */
#endif

#ifndef ST_EXPORTED
#define ST_EXPORTED 0x00000100 /* file system is exported */
#endif

#ifndef ST_DEFEXPORTED
#define ST_DEFEXPORTED 0x00000200 /* exported to the world */
#endif

#ifndef ST_EXPORTANON
#define ST_EXPORTANON 0x00000400 /* use anon uid mapping for everyone */
#endif

#ifndef ST_EXKERB
#define ST_EXKERB 0x00000800 /* exported with Kerberos uid mapping */
#endif

#ifndef ST_EXNORESPORT
#define ST_EXNORESPORT 0x08000000 /* don't enforce reserved ports (NFS) */
#endif

#ifndef ST_EXPUBLIC
#define ST_EXPUBLIC 0x10000000 /* public export (WebNFS) */
#endif

#ifndef ST_LOCAL
#define ST_LOCAL 0x00001000 /* filesystem is stored locally */
#endif

#ifndef ST_QUOTA
#define ST_QUOTA 0x00002000 /* quotas are enabled on filesystem */
#endif

#ifndef ST_ROOTFS
#define ST_ROOTFS 0x00004000 /* identifies the root filesystem */
#endif
#endif // NetBSD

#if defined(__FreeBSD__)
#ifndef MNT_RDONLY
#define MNT_RDONLY 0x0000000000000001ULL /* read only filesystem */
#endif

#ifndef MNT_SYNCHRONOUS
#define MNT_SYNCHRONOUS 0x0000000000000002ULL /* fs written synchronously */
#endif

#ifndef MNT_NOEXEC
#define MNT_NOEXEC 0x0000000000000004ULL /* can't exec from filesystem */
#endif

#ifndef MNT_NOSUID
#define MNT_NOSUID 0x0000000000000008ULL /* don't honor setuid fs bits */
#endif

#ifndef MNT_NFS4ACLS
#define MNT_NFS4ACLS 0x0000000000000010ULL /* enable NFS version 4 ACLs */
#endif

#ifndef MNT_UNION
#define MNT_UNION 0x0000000000000020ULL /* union with underlying fs */
#endif

#ifndef MNT_ASYNC
#define MNT_ASYNC 0x0000000000000040ULL /* fs written asynchronously */
#endif

#ifndef MNT_SUIDDIR
#define MNT_SUIDDIR 0x0000000000100000ULL /* special SUID dir handling */
#endif

#ifndef MNT_SOFTDEP
#define MNT_SOFTDEP 0x0000000000200000ULL /* using soft updates */
#endif

#ifndef MNT_NOSYMFOLLOW
#define MNT_NOSYMFOLLOW 0x0000000000400000ULL /* do not follow symlinks */
#endif

#ifndef MNT_GJOURNAL
#define MNT_GJOURNAL 0x0000000002000000ULL /* GEOM journal support enabled */
#endif

#ifndef MNT_MULTILABEL
#define MNT_MULTILABEL 0x0000000004000000ULL /* MAC support for objects */
#endif

#ifndef MNT_ACLS
#define MNT_ACLS 0x0000000008000000ULL /* ACL support enabled */
#endif

#ifndef MNT_NOATIME
#define MNT_NOATIME 0x0000000010000000ULL /* dont update file access time */
#endif

#ifndef MNT_NOCLUSTERR
#define MNT_NOCLUSTERR 0x0000000040000000ULL /* disable cluster read */
#endif

#ifndef MNT_NOCLUSTERW
#define MNT_NOCLUSTERW 0x0000000080000000ULL /* disable cluster write */
#endif

#ifndef MNT_SUJ
#define MNT_SUJ 0x0000000100000000ULL /* using journaled soft updates */
#endif

#ifndef MNT_AUTOMOUNTED
#define MNT_AUTOMOUNTED 0x0000000200000000ULL /* mounted by automountd(8) */
#endif

#ifndef MNT_UNTRUSTED
#define MNT_UNTRUSTED 0x0000000800000000ULL /* filesys metadata untrusted */
#endif

#ifndef MNT_EXRDONLY
#define MNT_EXRDONLY 0x0000000000000080ULL /* exported read only */
#endif

#ifndef MNT_EXPORTED
#define MNT_EXPORTED 0x0000000000000100ULL /* filesystem is exported */
#endif

#ifndef MNT_DEFEXPORTED
#define MNT_DEFEXPORTED 0x0000000000000200ULL /* exported to the world */
#endif

#ifndef MNT_EXPORTANON
#define MNT_EXPORTANON 0x0000000000000400ULL /* anon uid mapping for all */
#endif

#ifndef MNT_EXKERB
#define MNT_EXKERB 0x0000000000000800ULL /* exported with Kerberos */
#endif

#ifndef MNT_EXPUBLIC
#define MNT_EXPUBLIC 0x0000000020000000ULL /* public export (WebNFS) */
#endif

#ifndef MNT_LOCAL
#define MNT_LOCAL 0x0000000000001000ULL /* filesystem is stored locally */
#endif

#ifndef MNT_QUOTA
#define MNT_QUOTA 0x0000000000002000ULL /* quotas are enabled on fs */
#endif

#ifndef MNT_ROOTFS
#define MNT_ROOTFS 0x0000000000004000ULL /* identifies the root fs */
#endif

#ifndef MNT_USER
#define MNT_USER 0x0000000000008000ULL /* mounted by a user */
#endif

#ifndef MNT_IGNORE
#define MNT_IGNORE 0x0000000000800000ULL /* do not show entry in df */
#endif

#ifndef MNT_VERIFIED
#define MNT_VERIFIED 0x0000000400000000ULL /* filesystem is verified */
#endif
#endif // FreeBSD

#if defined(__DragonFly__)
#ifndef MNT_RDONLY
#define MNT_RDONLY 0x00000001 /* read only filesystem */
#endif

#ifndef MNT_SYNCHRONOUS
#define MNT_SYNCHRONOUS 0x00000002 /* file system written synchronously */
#endif

#ifndef MNT_NOEXEC
#define MNT_NOEXEC 0x00000004 /* can't exec from filesystem */
#endif

#ifndef MNT_NOSUID
#define MNT_NOSUID 0x00000008 /* don't honor setuid bits on fs */
#endif

#ifndef MNT_NODEV
#define MNT_NODEV 0x00000010 /* don't interpret special files */
#endif

#ifndef MNT_AUTOMOUNTED
#define MNT_AUTOMOUNTED 0x00000020 /* mounted by automountd(8) */
#endif

#ifndef MNT_ASYNC
#define MNT_ASYNC 0x00000040 /* file system written asynchronously */
#endif

#ifndef MNT_SUIDDIR
#define MNT_SUIDDIR 0x00100000 /* special handling of SUID on dirs */
#endif

#ifndef MNT_SOFTDEP
#define MNT_SOFTDEP 0x00200000 /* soft updates being done */
#endif

#ifndef MNT_NOSYMFOLLOW
#define MNT_NOSYMFOLLOW 0x00400000 /* do not follow symlinks */
#endif

#ifndef MNT_TRIM
#define MNT_TRIM 0x01000000 /* Enable online FS trimming */
#endif

#ifndef MNT_NOATIME
#define MNT_NOATIME 0x10000000 /* disable update of file access time */
#endif

#ifndef MNT_NOCLUSTERR
#define MNT_NOCLUSTERR 0x40000000 /* disable cluster read */
#endif

#ifndef MNT_NOCLUSTERW
#define MNT_NOCLUSTERW 0x80000000 /* disable cluster write */
#endif

#ifndef MNT_EXRDONLY
#define MNT_EXRDONLY 0x00000080 /* exported read only */
#endif

#ifndef MNT_EXPORTED
#define MNT_EXPORTED 0x00000100 /* file system is exported */
#endif

#ifndef MNT_DEFEXPORTED
#define MNT_DEFEXPORTED 0x00000200 /* exported to the world */
#endif

#ifndef MNT_EXPORTANON
#define MNT_EXPORTANON 0x00000400 /* use anon uid mapping for everyone */
#endif

#ifndef MNT_EXKERB
#define MNT_EXKERB 0x00000800 /* exported with Kerberos uid mapping */
#endif

#ifndef MNT_EXPUBLIC
#define MNT_EXPUBLIC 0x20000000 /* public export (WebNFS) */
#endif

#ifndef MNT_LOCAL
#define MNT_LOCAL 0x00001000 /* filesystem is stored locally */
#endif

#ifndef MNT_QUOTA
#define MNT_QUOTA 0x00002000 /* quotas are enabled on filesystem */
#endif

#ifndef MNT_ROOTFS
#define MNT_ROOTFS 0x00004000 /* identifies the root filesystem */
#endif

#ifndef MNT_USER
#define MNT_USER 0x00008000 /* mounted by a user */
#endif

#ifndef MNT_IGNORE
#define MNT_IGNORE 0x00800000 /* do not show entry in df */
#endif
#endif // DragonFly BSD

#endif // AARU_FSTESTER_SETTER_SRC_BSD_VOLUME_H_

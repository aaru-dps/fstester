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

#endif // AARU_FSTESTER_SETTER_SRC_BSD_VOLUME_H_

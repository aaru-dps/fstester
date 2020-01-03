/****************************************************************************
The Disc Image Chef
-----------------------------------------------------------------------------

Filename       : unix.h
Author(s)      : Natalia Portillo

Component      : fstester.setter

--[ Description ] -----------------------------------------------------------

Contains UNIX definitions

--[ License ] ---------------------------------------------------------------
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as
     published by the Free Software Foundation, either version 3 of the
     License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warraty of
     MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
Copyright (C) 2011-2020 Natalia Portillo
*****************************************************************************/

#ifndef SETTER_UNIX_H
#define SETTER_UNIX_H

#if defined(unix) || defined(UNIX) || defined(__unix) || defined(__unix__) || defined(__UNIX__)

#ifndef ADFS_SUPER_MAGIC
#define ADFS_SUPER_MAGIC 0xadf5
#endif

#ifndef AFFS_SUPER_MAGIC
#define AFFS_SUPER_MAGIC 0xadff
#endif

#ifndef AFS_SUPER_MAGIC
#define AFS_SUPER_MAGIC 0x5346414f
#endif

#ifndef ANON_INODE_FS_MAGIC
#define ANON_INODE_FS_MAGIC 0x09041934
#endif

#ifndef AUTOFS_SUPER_MAGIC
#define AUTOFS_SUPER_MAGIC 0x0187
#endif

#ifndef BDEVFS_MAGIC
#define BDEVFS_MAGIC 0x62646576
#endif

#ifndef BEFS_SUPER_MAGIC
#define BEFS_SUPER_MAGIC 0x42465331
#endif

#ifndef BFS_MAGIC
#define BFS_MAGIC 0x1badface
#endif

#ifndef BINFMTFS_MAGIC
#define BINFMTFS_MAGIC 0x42494e4d
#endif

#ifndef BPF_FS_MAGIC
#define BPF_FS_MAGIC 0xcafe4a11
#endif

#ifndef BTRFS_SUPER_MAGIC
#define BTRFS_SUPER_MAGIC 0x9123683e
#endif

#ifndef BTRFS_TEST_MAGIC
#define BTRFS_TEST_MAGIC 0x73727279
#endif

#ifndef CGROUP_SUPER_MAGIC
#define CGROUP_SUPER_MAGIC 0x27e0eb
#endif

#ifndef CGROUP2_SUPER_MAGIC
#define CGROUP2_SUPER_MAGIC 0x63677270
#endif

#ifndef CIFS_MAGIC_NUMBER
#define CIFS_MAGIC_NUMBER 0xff534d42
#endif

#ifndef CODA_SUPER_MAGIC
#define CODA_SUPER_MAGIC 0x73757245
#endif

#ifndef COH_SUPER_MAGIC
#define COH_SUPER_MAGIC 0x012ff7b7
#endif

#ifndef CRAMFS_MAGIC
#define CRAMFS_MAGIC 0x28cd3d45
#endif

#ifndef DEBUGFS_MAGIC
#define DEBUGFS_MAGIC 0x64626720
#endif

#ifndef DEVFS_SUPER_MAGIC
#define DEVFS_SUPER_MAGIC 0x1373
#endif

#ifndef DEVPTS_SUPER_MAGIC
#define DEVPTS_SUPER_MAGIC 0x1cd1
#endif

#ifndef ECRYPTFS_SUPER_MAGIC
#define ECRYPTFS_SUPER_MAGIC 0xf15f
#endif

#ifndef EFIVARFS_MAGIC
#define EFIVARFS_MAGIC 0xde5e81e4
#endif

#ifndef EFS_SUPER_MAGIC
#define EFS_SUPER_MAGIC 0x00414a53
#endif

#ifndef EXT_SUPER_MAGIC
#define EXT_SUPER_MAGIC 0x137d
#endif

#ifndef EXT2_OLD_SUPER_MAGIC
#define EXT2_OLD_SUPER_MAGIC 0xef51
#endif

#ifndef EXT2_SUPER_MAGIC
#define EXT2_SUPER_MAGIC 0xef53
#endif

#ifndef F2FS_SUPER_MAGIC
#define F2FS_SUPER_MAGIC 0xf2f52010
#endif

#ifndef FUSE_SUPER_MAGIC
#define FUSE_SUPER_MAGIC 0x65735546
#endif

#ifndef FUTEXFS_SUPER_MAGIC
#define FUTEXFS_SUPER_MAGIC 0xbad1dea
#endif

#ifndef HFS_SUPER_MAGIC
#define HFS_SUPER_MAGIC 0x4244
#endif

#ifndef HOSTFS_SUPER_MAGIC
#define HOSTFS_SUPER_MAGIC 0x00c0ffee
#endif

#ifndef HPFS_SUPER_MAGIC
#define HPFS_SUPER_MAGIC 0xf995e849
#endif

#ifndef HUGETLBFS_MAGIC
#define HUGETLBFS_MAGIC 0x958458f6
#endif

#ifndef ISOFS_SUPER_MAGIC
#define ISOFS_SUPER_MAGIC 0x9660
#endif

#ifndef JFFS2_SUPER_MAGIC
#define JFFS2_SUPER_MAGIC 0x72b6
#endif

#ifndef JFS_SUPER_MAGIC
#define JFS_SUPER_MAGIC 0x3153464a
#endif

#ifndef MINIX_SUPER_MAGIC
#define MINIX_SUPER_MAGIC 0x137f
#endif

#ifndef MINIX_SUPER_MAGIC2
#define MINIX_SUPER_MAGIC2 0x138f
#endif

#ifndef MINIX2_SUPER_MAGIC
#define MINIX2_SUPER_MAGIC 0x2468
#endif

#ifndef MINIX2_SUPER_MAGIC2
#define MINIX2_SUPER_MAGIC2 0x2478
#endif

#ifndef MINIX3_SUPER_MAGIC
#define MINIX3_SUPER_MAGIC 0x4d5a
#endif

#ifndef MQUEUE_MAGIC
#define MQUEUE_MAGIC 0x19800202
#endif

#ifndef MSDOS_SUPER_MAGIC
#define MSDOS_SUPER_MAGIC 0x4d44
#endif

#ifndef MTD_INODE_FS_MAGIC
#define MTD_INODE_FS_MAGIC 0x11307854
#endif

#ifndef NCP_SUPER_MAGIC
#define NCP_SUPER_MAGIC 0x564c
#endif

#ifndef NFS_SUPER_MAGIC
#define NFS_SUPER_MAGIC 0x6969
#endif

#ifndef NILFS_SUPER_MAGIC
#define NILFS_SUPER_MAGIC 0x3434
#endif

#ifndef NSFS_MAGIC
#define NSFS_MAGIC 0x6e736673
#endif

#ifndef NTFS_SB_MAGIC
#define NTFS_SB_MAGIC 0x5346544e
#endif

#ifndef OCFS2_SUPER_MAGIC
#define OCFS2_SUPER_MAGIC 0x7461636f
#endif

#ifndef OPENPROM_SUPER_MAGIC
#define OPENPROM_SUPER_MAGIC 0x9fa1
#endif

#ifndef OVERLAYFS_SUPER_MAGIC
#define OVERLAYFS_SUPER_MAGIC 0x794c7630
#endif

#ifndef PIPEFS_MAGIC
#define PIPEFS_MAGIC 0x50495045
#endif

#ifndef PROC_SUPER_MAGIC
#define PROC_SUPER_MAGIC 0x9fa0
#endif

#ifndef PSTOREFS_MAGIC
#define PSTOREFS_MAGIC 0x6165676c
#endif

#ifndef QNX4_SUPER_MAGIC
#define QNX4_SUPER_MAGIC 0x002f
#endif

#ifndef QNX6_SUPER_MAGIC
#define QNX6_SUPER_MAGIC 0x68191122
#endif

#ifndef RAMFS_MAGIC
#define RAMFS_MAGIC 0x858458f6
#endif

#ifndef REISERFS_SUPER_MAGIC
#define REISERFS_SUPER_MAGIC 0x52654973
#endif

#ifndef ROMFS_MAGIC
#define ROMFS_MAGIC 0x7275
#endif

#ifndef SECURITYFS_MAGIC
#define SECURITYFS_MAGIC 0x73636673
#endif

#ifndef SELINUX_MAGIC
#define SELINUX_MAGIC 0xf97cff8c
#endif

#ifndef SMACK_MAGIC
#define SMACK_MAGIC 0x43415d53
#endif

#ifndef SMB_SUPER_MAGIC
#define SMB_SUPER_MAGIC 0x517b
#endif

#ifndef SOCKFS_MAGIC
#define SOCKFS_MAGIC 0x534f434b
#endif

#ifndef SQUASHFS_MAGIC
#define SQUASHFS_MAGIC 0x73717368
#endif

#ifndef SYSFS_MAGIC
#define SYSFS_MAGIC 0x62656572
#endif

#ifndef SYSV2_SUPER_MAGIC
#define SYSV2_SUPER_MAGIC 0x012ff7b6
#endif

#ifndef SYSV4_SUPER_MAGIC
#define SYSV4_SUPER_MAGIC 0x012ff7b5
#endif

#ifndef TMPFS_MAGIC
#define TMPFS_MAGIC 0x01021994
#endif

#ifndef TRACEFS_MAGIC
#define TRACEFS_MAGIC 0x74726163
#endif

#ifndef UDF_SUPER_MAGIC
#define UDF_SUPER_MAGIC 0x15013346
#endif

#ifndef UFS_MAGIC
#define UFS_MAGIC 0x00011954
#endif

#ifndef USBDEVICE_SUPER_MAGIC
#define USBDEVICE_SUPER_MAGIC 0x9fa2
#endif

#ifndef V9FS_MAGIC
#define V9FS_MAGIC 0x01021997
#endif

#ifndef VXFS_SUPER_MAGIC
#define VXFS_SUPER_MAGIC 0xa501fcf5
#endif

#ifndef XENFS_SUPER_MAGIC
#define XENFS_SUPER_MAGIC 0xabba1974
#endif

#ifndef XENIX_SUPER_MAGIC
#define XENIX_SUPER_MAGIC 0x012ff7b4
#endif

#ifndef XFS_SUPER_MAGIC
#define XFS_SUPER_MAGIC 0x58465342
#endif

#ifndef _XIAFS_SUPER_MAGIC
#define _XIAFS_SUPER_MAGIC 0x012fd16d
#endif

#ifndef ST_RDONLY
#define ST_RDONLY 1
#endif

#ifndef ST_NOSUID
#define ST_NOSUID 2
#endif

#ifndef ST_NODEV
#define ST_NODEV 4
#endif

#ifndef ST_NOEXEC
#define ST_NOEXEC 8
#endif

#ifndef ST_SYNCHRONOUS
#define ST_SYNCHRONOUS 16
#endif

#ifndef ST_MANDLOCK
#define ST_MANDLOCK 64
#endif

#ifndef ST_WRITE
#define ST_WRITE 128
#endif

#ifndef ST_APPEND
#define ST_APPEND 256
#endif

#ifndef ST_IMMUTABLE
#define ST_IMMUTABLE 512
#endif

#ifndef ST_NOATIME
#define ST_NOATIME 1024
#endif

#ifndef ST_NODIRATIME
#define ST_NODIRATIME 2048
#endif

#define DATETIME_FORMAT "This file is dated %s for %s\n"
#define LESSDATETIME "2106/02/07 06:28:15 or unknown"
#define MAXDATETIME "2038/01/19 03:14:07"
#define MINDATETIME "1970/01/01 00:00:00"
#define Y2KDATETIME "2000/01/01 00:00:00"
#define Y1KDATETIME "1999/12/31 23:59:59"
#define LESSTIMESTAMP 0xFFFFFFFF
#define MAXTIMESTAMP 0x7FFFFFFF
#define MINTIMESTAMP 0x00000000
#define Y2KTIMESTAMP 0x386D4380
#define Y1KTIMESTAMP 0x386D437F

#endif

#endif // SETTER_UNIX_H

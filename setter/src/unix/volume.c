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
#include <stddef.h>
#include <stdio.h>

#ifdef HAVE_SYS_STATFS_H
#include <sys/statfs.h>
#endif

#ifdef HAVE_SYS_STATVFS_H
#include <sys/statvfs.h>
#endif

#if defined(HAVE_SYS_MOUNT_H)
#include <sys/mount.h>
#include <sys/param.h>
#endif

#include "../include/defs.h"
#include "../log.h"
#include "volume.h"

#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)
#include "linux/linux.h"
#elif defined(__APPLE__) && defined(__MACH__)
#include "darwin/darwin.h"
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)
#include "bsd/bsd.h"
#endif

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
#ifdef HAVE_SYS_STATVFS_H
    struct statvfs buf;
#else
    struct statfs buf;
#endif
    int ret;

#ifdef HAVE_SYS_STATVFS_H
    ret = statvfs(path, &buf);
#else
    ret = statfs(path, &buf);
#endif

    if(ret)
    {
        log_write("Error %d querying volume information.\n", errno);
        return;
    }

    log_write("Volume information:\n");
    log_write("\tPath: %s\n", path);

#ifdef USE_STATFS_FTYPENAME
    log_write("\tFilesystem: %s\n", buf.f_fstypename);
#else
    log_write("\tFilesystem: ");
    switch(buf.f_type)
    {
        case ADFS_SUPER_MAGIC: log_write("ADFS"); break;
        case AFFS_SUPER_MAGIC: log_write("Amiga FFS"); break;
        case AFS_SUPER_MAGIC: log_write("AFS"); break;
        case ANON_INODE_FS_MAGIC: log_write("anonymous inode fs"); break;
        case AUTOFS_SUPER_MAGIC: log_write("autofs"); break;
        case BDEVFS_MAGIC: log_write("bdevfs"); break;
        case BEFS_SUPER_MAGIC: log_write("BeFS"); break;
        case BFS_MAGIC: log_write("bfs"); break;
        case BINFMTFS_MAGIC: log_write("binfmtfs"); break;
        case BPF_FS_MAGIC: log_write("bpffs"); break;
        case BTRFS_SUPER_MAGIC:
        case BTRFS_TEST_MAGIC: log_write("btrfs"); break;
        case CGROUP_SUPER_MAGIC: log_write("cgroup"); break;
        case CGROUP2_SUPER_MAGIC: log_write("cgroup2"); break;
        case CIFS_MAGIC_NUMBER: log_write("CIFS"); break;
        case CODA_SUPER_MAGIC: log_write("CODA"); break;
        case COH_SUPER_MAGIC: log_write("Coherent"); break;
        case CRAMFS_MAGIC: log_write("cramfs"); break;
        case DEBUGFS_MAGIC: log_write("debufs"); break;
        case DEVFS_SUPER_MAGIC: log_write("devfs"); break;
        case DEVPTS_SUPER_MAGIC: log_write("devpts"); break;
        case ECRYPTFS_SUPER_MAGIC: log_write("ecryptfs"); break;
        case EFIVARFS_MAGIC: log_write("efivars"); break;
        case EFS_SUPER_MAGIC: log_write("EFS"); break;
        case EXT_SUPER_MAGIC: log_write("ext"); break;
        case EXT2_OLD_SUPER_MAGIC: log_write("ext2"); break;
        case EXT2_SUPER_MAGIC: log_write("ext2/3/4"); break;
        case F2FS_SUPER_MAGIC: log_write("f2fs"); break;
        case FUSE_SUPER_MAGIC: log_write("fuse"); break;
        case FUTEXFS_SUPER_MAGIC: log_write("futexfs"); break;
        case HFS_SUPER_MAGIC: log_write("HFS"); break;
        case HOSTFS_SUPER_MAGIC: log_write("hostfs"); break;
        case HPFS_SUPER_MAGIC: log_write("HPFS"); break;
        case HUGETLBFS_MAGIC: log_write("hugetlbfs"); break;
        case ISOFS_SUPER_MAGIC: log_write("ISO9660"); break;
        case JFFS2_SUPER_MAGIC: log_write("jffs2"); break;
        case JFS_SUPER_MAGIC: log_write("JFS"); break;
        case MINIX_SUPER_MAGIC:
        case MINIX_SUPER_MAGIC2: log_write("minix"); break;
        case MINIX2_SUPER_MAGIC:
        case MINIX2_SUPER_MAGIC2: log_write("minix2"); break;
        case MINIX3_SUPER_MAGIC: log_write("minix3"); break;
        case MQUEUE_MAGIC: log_write("mqueue"); break;
        case MSDOS_SUPER_MAGIC: log_write("msdos/vfat"); break;
        case MTD_INODE_FS_MAGIC: log_write("mtd inodefs"); break;
        case NCP_SUPER_MAGIC: log_write("NCP"); break;
        case NFS_SUPER_MAGIC: log_write("NFS"); break;
        case NILFS_SUPER_MAGIC: log_write("nilfs"); break;
        case NSFS_MAGIC: log_write("nsfs"); break;
        case NTFS_SB_MAGIC: log_write("NTFS"); break;
        case OCFS2_SUPER_MAGIC: log_write("OCFS2"); break;
        case OPENPROM_SUPER_MAGIC: log_write("OpenPROM"); break;
        case OVERLAYFS_SUPER_MAGIC: log_write("overlayfs"); break;
        case PIPEFS_MAGIC: log_write("pipefs"); break;
        case PROC_SUPER_MAGIC: log_write("proc"); break;
        case PSTOREFS_MAGIC: log_write("pstorefs"); break;
        case QNX4_SUPER_MAGIC: log_write("qnx4"); break;
        case QNX6_SUPER_MAGIC: log_write("qnx6"); break;
        case RAMFS_MAGIC: log_write("ramfs"); break;
        case REISERFS_SUPER_MAGIC: log_write("Reiser"); break;
        case ROMFS_MAGIC: log_write("romfs"); break;
        case SECURITYFS_MAGIC: log_write("securityfs"); break;
        case SELINUX_MAGIC: log_write("SELinux"); break;
        case SMACK_MAGIC: log_write("smack"); break;
        case SMB_SUPER_MAGIC: log_write("SMB"); break;
        case SOCKFS_MAGIC: log_write("sockfs"); break;
        case SQUASHFS_MAGIC: log_write("squashfs"); break;
        case SYSFS_MAGIC: log_write("sysfs"); break;
        case SYSV2_SUPER_MAGIC: log_write("System V Release 2"); break;
        case SYSV4_SUPER_MAGIC: log_write("System V Release 4"); break;
        case TMPFS_MAGIC: log_write("tmpfs"); break;
        case TRACEFS_MAGIC: log_write("tracefs"); break;
        case UDF_SUPER_MAGIC: log_write("UDF"); break;
        case UFS_MAGIC: log_write("UFS"); break;
        case USBDEVICE_SUPER_MAGIC: log_write("usbdevice"); break;
        case V9FS_MAGIC: log_write("V9"); break;
        case VXFS_SUPER_MAGIC: log_write("vxfs"); break;
        case XENFS_SUPER_MAGIC: log_write("xenfs"); break;
        case XENIX_SUPER_MAGIC: log_write("XENIX"); break;
        case XFS_SUPER_MAGIC: log_write("XFS"); break;
        case _XIAFS_SUPER_MAGIC: log_write("xia"); break;
        default: log_write("unknown type -> 0x%lX", buf.f_type);
    }
    log_write("\n");
#endif

    log_write("\tBytes per block: %ld\n", buf.f_bsize);
    log_write("\tVolume size: %llu bytes\n", ((unsigned long long)buf.f_blocks) * buf.f_bsize);
    log_write("\tVolume free: %llu bytes\n", ((unsigned long long)buf.f_bfree) * buf.f_bsize);

#ifdef USE_STATFS_FNAMELEN
    log_write("\tMaximum component length: %ld\n", buf.f_namelen);
#elif USE_STATFS_NAMEMAX
    log_write("\tMaximum component length: %ld\n", buf.f_namemax);
#endif

#if HAVE_SYS_STATVFS_H
    if(buf.f_flag)
    {
#if defined(__NetBSD__)
        NetBsdPrintStatvfsFlags(buf.f_flag);
#else
        log_write("\tFlags: 0x%08lX\n", buf.f_flag);
#endif
    }
#else
    if(buf.f_flags)
    {
#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)
        LinuxPrintStatfsFlags(buf.f_flags);
#elif defined(__APPLE__) && defined(__MACH__)
        DarwinPrintStatfsFlags(buf.f_flags);
#else
        log_write("\tFlags: 0x%08lX\n", buf.f_flags);
#endif
    }
#endif

    *clusterSize = buf.f_bsize;

#if defined(__APPLE__) && defined(__MACH__)
    DarwinVolumeAttributes(path);
#endif
}

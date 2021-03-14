/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

Filename       : volume.c
Author(s)      : Natalia Portillo

--[ Description ] -----------------------------------------------------------

Contains common implementations for UNIX family and compatibles

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
#include <sys/statfs.h>

#include "../include/defs.h"
#include "unix.h"

void GetVolumeInfo(const char* path, size_t* clusterSize)
{
    struct statfs buf;
    int           ret;

    ret = statfs(path, &buf);

    if(ret)
    {
        printf("Error %d querying volume information.\n", errno);
        return;
    }

    printf("Volume information:\n");
    printf("\tPath: %s\n", path);

    printf("\tFilesystem: ");
    switch(buf.f_type)
    {
        case ADFS_SUPER_MAGIC: printf("ADFS"); break;
        case AFFS_SUPER_MAGIC: printf("Amiga FFS"); break;
        case AFS_SUPER_MAGIC: printf("AFS"); break;
        case ANON_INODE_FS_MAGIC: printf("anonymous inode fs"); break;
        case AUTOFS_SUPER_MAGIC: printf("autofs"); break;
        case BDEVFS_MAGIC: printf("bdevfs"); break;
        case BEFS_SUPER_MAGIC: printf("BeFS"); break;
        case BFS_MAGIC: printf("bfs"); break;
        case BINFMTFS_MAGIC: printf("binfmtfs"); break;
        case BPF_FS_MAGIC: printf("bpffs"); break;
        case BTRFS_SUPER_MAGIC:
        case BTRFS_TEST_MAGIC: printf("btrfs"); break;
        case CGROUP_SUPER_MAGIC: printf("cgroup"); break;
        case CGROUP2_SUPER_MAGIC: printf("cgroup2"); break;
        case CIFS_MAGIC_NUMBER: printf("CIFS"); break;
        case CODA_SUPER_MAGIC: printf("CODA"); break;
        case COH_SUPER_MAGIC: printf("Coherent"); break;
        case CRAMFS_MAGIC: printf("cramfs"); break;
        case DEBUGFS_MAGIC: printf("debufs"); break;
        case DEVFS_SUPER_MAGIC: printf("devfs"); break;
        case DEVPTS_SUPER_MAGIC: printf("devpts"); break;
        case ECRYPTFS_SUPER_MAGIC: printf("ecryptfs"); break;
        case EFIVARFS_MAGIC: printf("efivars"); break;
        case EFS_SUPER_MAGIC: printf("EFS"); break;
        case EXT_SUPER_MAGIC: printf("ext"); break;
        case EXT2_OLD_SUPER_MAGIC: printf("ext2"); break;
        case EXT2_SUPER_MAGIC: printf("ext2/3/4"); break;
        case F2FS_SUPER_MAGIC: printf("f2fs"); break;
        case FUSE_SUPER_MAGIC: printf("fuse"); break;
        case FUTEXFS_SUPER_MAGIC: printf("futexfs"); break;
        case HFS_SUPER_MAGIC: printf("HFS"); break;
        case HOSTFS_SUPER_MAGIC: printf("hostfs"); break;
        case HPFS_SUPER_MAGIC: printf("HPFS"); break;
        case HUGETLBFS_MAGIC: printf("hugetlbfs"); break;
        case ISOFS_SUPER_MAGIC: printf("ISO9660"); break;
        case JFFS2_SUPER_MAGIC: printf("jffs2"); break;
        case JFS_SUPER_MAGIC: printf("JFS"); break;
        case MINIX_SUPER_MAGIC:
        case MINIX_SUPER_MAGIC2: printf("minix"); break;
        case MINIX2_SUPER_MAGIC:
        case MINIX2_SUPER_MAGIC2: printf("minix2"); break;
        case MINIX3_SUPER_MAGIC: printf("minix3"); break;
        case MQUEUE_MAGIC: printf("mqueue"); break;
        case MSDOS_SUPER_MAGIC: printf("msdos/vfat"); break;
        case MTD_INODE_FS_MAGIC: printf("mtd inodefs"); break;
        case NCP_SUPER_MAGIC: printf("NCP"); break;
        case NFS_SUPER_MAGIC: printf("NFS"); break;
        case NILFS_SUPER_MAGIC: printf("nilfs"); break;
        case NSFS_MAGIC: printf("nsfs"); break;
        case NTFS_SB_MAGIC: printf("NTFS"); break;
        case OCFS2_SUPER_MAGIC: printf("OCFS2"); break;
        case OPENPROM_SUPER_MAGIC: printf("OpenPROM"); break;
        case OVERLAYFS_SUPER_MAGIC: printf("overlayfs"); break;
        case PIPEFS_MAGIC: printf("pipefs"); break;
        case PROC_SUPER_MAGIC: printf("proc"); break;
        case PSTOREFS_MAGIC: printf("pstorefs"); break;
        case QNX4_SUPER_MAGIC: printf("qnx4"); break;
        case QNX6_SUPER_MAGIC: printf("qnx6"); break;
        case RAMFS_MAGIC: printf("ramfs"); break;
        case REISERFS_SUPER_MAGIC: printf("Reiser"); break;
        case ROMFS_MAGIC: printf("romfs"); break;
        case SECURITYFS_MAGIC: printf("securityfs"); break;
        case SELINUX_MAGIC: printf("SELinux"); break;
        case SMACK_MAGIC: printf("smack"); break;
        case SMB_SUPER_MAGIC: printf("SMB"); break;
        case SOCKFS_MAGIC: printf("sockfs"); break;
        case SQUASHFS_MAGIC: printf("squashfs"); break;
        case SYSFS_MAGIC: printf("sysfs"); break;
        case SYSV2_SUPER_MAGIC: printf("System V Release 2"); break;
        case SYSV4_SUPER_MAGIC: printf("System V Release 4"); break;
        case TMPFS_MAGIC: printf("tmpfs"); break;
        case TRACEFS_MAGIC: printf("tracefs"); break;
        case UDF_SUPER_MAGIC: printf("UDF"); break;
        case UFS_MAGIC: printf("UFS"); break;
        case USBDEVICE_SUPER_MAGIC: printf("usbdevice"); break;
        case V9FS_MAGIC: printf("V9"); break;
        case VXFS_SUPER_MAGIC: printf("vxfs"); break;
        case XENFS_SUPER_MAGIC: printf("xenfs"); break;
        case XENIX_SUPER_MAGIC: printf("XENIX"); break;
        case XFS_SUPER_MAGIC: printf("XFS"); break;
        case _XIAFS_SUPER_MAGIC: printf("xia"); break;
        default: printf("unknown type -> 0x%lX", buf.f_type);
    }
    printf("\n");

    printf("\tBytes per block: %ld\n", buf.f_bsize);
    printf("\tVolume size: %llu bytes\n", ((unsigned long long)buf.f_blocks) * buf.f_bsize);
    printf("\tVolume free: %llu bytes\n", ((unsigned long long)buf.f_bfree) * buf.f_bsize);
    printf("\tMaximum component length: %ld\n", buf.f_namelen);

    if(buf.f_flags)
    {
        printf("\tFlags:\n");

        if(buf.f_flags & ST_RDONLY)
        {
            printf("\t\tVolume is read-only.\n");
            buf.f_flags -= ST_RDONLY;
        }

        if(buf.f_flags & ST_NOSUID)
        {
            printf("\t\tVolume ignores suid and sgid bits.\n");
            buf.f_flags -= ST_NOSUID;
        }

        if(buf.f_flags & ST_NODEV)
        {
            printf("\t\tVolume disallows access to device special files.\n");
            buf.f_flags -= ST_NODEV;
        }

        if(buf.f_flags & ST_NOEXEC)
        {
            printf("\t\tVolume disallows program execution.\n");
            buf.f_flags -= ST_NOEXEC;
        }

        if(buf.f_flags & ST_SYNCHRONOUS)
        {
            printf("\t\tVolume writes are synced at once.\n");
            buf.f_flags -= ST_SYNCHRONOUS;
        }

        if(buf.f_flags & ST_MANDLOCK)
        {
            printf("\t\tVolume allows mandatory locks.\n");
            buf.f_flags -= ST_MANDLOCK;
        }

        if(buf.f_flags & ST_WRITE)
        {
            printf("\t\tVolume writes on file/directory/symlink.\n");
            buf.f_flags -= ST_WRITE;
        }

        if(buf.f_flags & ST_APPEND)
        {
            printf("\t\tVolume appends.\n");
            buf.f_flags -= ST_APPEND;
        }

        if(buf.f_flags & ST_IMMUTABLE)
        {
            printf("\t\tVolume is immutable.\n");
            buf.f_flags -= ST_IMMUTABLE;
        }

        if(buf.f_flags & ST_NOATIME)
        {
            printf("\t\tVolume does not update access times.\n");
            buf.f_flags -= ST_NOATIME;
        }

        if(buf.f_flags & ST_NODIRATIME)
        {
            printf("\t\tVolume does not update directory access times.\n");
            buf.f_flags -= ST_NODIRATIME;
        }

        if(buf.f_flags) { printf("\t\tRemaining flags: 0x%08lX\n", buf.f_flags); }
    }

    *clusterSize = buf.f_bsize;
}

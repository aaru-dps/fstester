/****************************************************************************
The Disc Image Chef
-----------------------------------------------------------------------------

Filename       : win32.c
Author(s)      : Natalia Portillo

Component      : fstester.setter.os2

--[ Description ] -----------------------------------------------------------

Contains 32-bit and 64-bit Windows code

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
Copyright (C) 2011-2018 Natalia Portillo
*****************************************************************************/

#if defined(unix) || defined(UNIX) || defined(__unix) || defined(__unix__) || defined(__UNIX__)

#include "unix.h"

#include "consts.h"
#include "defs.h"
#include "linux.h"

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <utime.h>

void GetOsInfo()
{
    struct utsname buf;
    int            ret;

    ret = uname(&buf);

    if(ret)
    {
        printf("Error %d retrieving OS information.\n", errno);
        return;
    }

    printf("OS information:\n");
    printf("\tOS name: %s\n", buf.sysname);
    printf("\tRelease: %s\n", buf.release);
    printf("\tVersion: %s\n", buf.version);
    printf("\tMachine: %s\n", buf.machine);
}

void GetVolumeInfo(const char *path, size_t *clusterSize)
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

void FileAttributes(const char *path)
{
    // Operating system dependent
}

void FilePermissions(const char *path)
{
    int   ret;
    FILE *file;
    int   rc;
    int   cRc;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("PERMS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("PERMS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating attributes files.\n");

    file = fopen("NONE", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with no permissions.\n");
        fclose(file);
        cRc = chmod("NONE", 0);
    }
    printf("\tFile with no permissions: name = \"%s\", rc = %d, cRc = %d\n", "NONE", rc, cRc);

    file = fopen("04000", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with set-user-ID.\n");
        fclose(file);
        cRc = chmod("04000", 04000);
    }
    printf("\tFile with set-user-ID: name = \"%s\", rc = %d, cRc = %d\n", "04000", rc, cRc);

    file = fopen("02000", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with set-group-ID.\n");
        fclose(file);
        cRc = chmod("02000", 02000);
    }
    printf("\tFile with set-group-ID: name = \"%s\", rc = %d, cRc = %d\n", "02000", rc, cRc);

    file = fopen("01000", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with sticky bit.\n");
        fclose(file);
        cRc = chmod("01000", 01000);
    }
    printf("\tFile with sticky bit: name = \"%s\", rc = %d, cRc = %d\n", "01000", rc, cRc);

    file = fopen("00400", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with read by owner.\n");
        fclose(file);
        cRc = chmod("00400", 00400);
    }
    printf("\tFile with read by owner: name = \"%s\", rc = %d, cRc = %d\n", "00400", rc, cRc);

    file = fopen("00200", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with write by owner.\n");
        fclose(file);
        cRc = chmod("00200", 00200);
    }
    printf("\tFile with write by owner: name = \"%s\", rc = %d, cRc = %d\n", "00200", rc, cRc);

    file = fopen("00100", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with execute by owner.\n");
        fclose(file);
        cRc = chmod("00100", 00100);
    }
    printf("\tFile with execute by owner: name = \"%s\", rc = %d, cRc = %d\n", "00100", rc, cRc);

    file = fopen("00040", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with read by group.\n");
        fclose(file);
        cRc = chmod("00040", 00040);
    }
    printf("\tFile with read by group: name = \"%s\", rc = %d, cRc = %d\n", "00040", rc, cRc);

    file = fopen("00020", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with write by group.\n");
        fclose(file);
        cRc = chmod("00020", 00020);
    }
    printf("\tFile with write by group: name = \"%s\", rc = %d, cRc = %d\n", "00020", rc, cRc);

    file = fopen("00010", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with execute by group.\n");
        fclose(file);
        cRc = chmod("00010", 00010);
    }
    printf("\tFile with execute by group: name = \"%s\", rc = %d, cRc = %d\n", "00010", rc, cRc);

    file = fopen("00004", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with read by others.\n");
        fclose(file);
        cRc = chmod("00004", 00004);
    }
    printf("\tFile with read by others: name = \"%s\", rc = %d, cRc = %d\n", "00004", rc, cRc);

    file = fopen("00002", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with write by others.\n");
        fclose(file);
        cRc = chmod("00002", 00002);
    }
    printf("\tFile with write by others: name = \"%s\", rc = %d, cRc = %d\n", "00002", rc, cRc);

    file = fopen("00001", "w+");
    rc   = 0;
    cRc  = 0;
    if(!file) { rc = errno; }
    else
    {
        fprintf(file, "File with execute by others.\n");
        fclose(file);
        cRc = chmod("00001", 00001);
    }
    printf("\tFile with execute by others: name = \"%s\", rc = %d, cRc = %d\n", "00001", rc, cRc);
}

void ExtendedAttributes(const char *path)
{
#if defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux)
    LinuxExtendedAttributes(path);
#endif
}

void ResourceFork(const char *path)
{
    // Not supported
}

void Filenames(const char *path)
{
    int   ret;
    FILE *h;
    int   rc, wRc, cRc;
    char  message[300];
    int   pos = 0;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("FILENAME", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("FILENAME");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating files with different filenames.\n");

    for(pos = 0; filenames[pos]; pos++)
    {
        h   = fopen(filenames[pos], "w+");
        rc  = 0;
        wRc = 0;
        cRc = 0;

        if(!h) { rc = errno; }
        else
        {
            memset(&message, 0, 300);
            sprintf((char *)&message, FILENAME_FORMAT, filenames[pos]);

            ret = fprintf(h, (const char *)&message);
            if(ret < 0) { wRc = errno; }

            ret = fclose(h);
            if(ret) { cRc = errno; }
        }

        printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d\n", filenames[pos], rc, wRc, cRc);
    }
}

void Timestamps(const char *path)
{
    char           message[300];
    int            ret;
    time_t         ftLastAccessTime;
    time_t         ftLastWriteTime;
    FILE *         h;
    int            rc, wRc, cRc, tRc;
    struct utimbuf times;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("TIMES", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("TIMES");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating timestamped files.\n");

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MAXATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, MAXDATETIME, "access");
        times.actime = MAXTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MAXATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MAXMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, MAXDATETIME, "modification");
        times.modtime = MAXTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MAXMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MAXMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MINATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, MINDATETIME, "access");
        times.actime = MINTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MINATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("MINMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, MINDATETIME, "modification");
        times.modtime = MINTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("MINMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "MINMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y1KATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, Y1KDATETIME, "access");
        times.actime = Y1KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y1KATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y1KMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, Y1KDATETIME, "modification");
        times.modtime = Y1KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y1KMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y1KMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y2KATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, Y2KDATETIME, "access");
        times.actime = Y2KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y2KATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("Y2KMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, Y1KDATETIME, "modification");
        times.modtime = Y2KTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("Y2KMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "Y2KMTIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("LESSATIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, LESSDATETIME, "access");
        times.actime = LESSTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("LESSATIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "LESSATIME", rc, wRc, cRc, tRc);

    memset(&times, 0, sizeof(struct utimbuf));
    h   = fopen("LESSMTIME", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    tRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        memset(&message, 0, 300);
        sprintf((char *)message, DATETIME_FORMAT, LESSDATETIME, "modification");
        times.modtime = LESSTIMESTAMP;

        ret = fprintf(h, message);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }

        ret = utime("LESSMTIME", &times);
        if(ret) { tRc = errno; }
    }
    printf("\tFile name = \"%s\", rc = %d, wRc = %d, cRc = %d, tRc = %d\n", "LESSMTIME", rc, wRc, cRc, tRc);
}

void DirectoryDepth(const char *path)
{
    int  ret;
    char filename[9];
    long pos = 2;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("DEPTH", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("DEPTH");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating deepest directory tree.\n");

    while(!ret)
    {
        memset(&filename, 0, 9);
        sprintf(&filename, "%08ld", pos);
        ret = mkdir(filename, 0755);

        if(!ret) ret = chdir(filename);

        pos++;

        // This can continue until the disk fills, the kernel crashes, or some other nasty success
        if(pos >= 1000) break;
    }

    printf("\tCreated %ld levels of directory hierarchy\n", pos);
}

void Fragmentation(const char *path, size_t clusterSize)
{
    size_t         halfCluster             = clusterSize / 2;
    size_t         quarterCluster          = clusterSize / 4;
    size_t         twoCluster              = clusterSize * 2;
    size_t         threeQuartersCluster    = halfCluster + quarterCluster;
    size_t         twoAndThreeQuartCluster = threeQuartersCluster + twoCluster;
    unsigned char *buffer;
    long           i;
    int            ret;
    FILE *         h;
    int            rc, wRc, cRc;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("FRAGS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("FRAGS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Writing fragmented files:\n");

    h   = fopen("HALFCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(halfCluster);
        memset(buffer, 0, halfCluster);

        for(i = 0; i < halfCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, halfCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "HALFCLST", halfCluster, rc, wRc, cRc);

    h   = fopen("QUARCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(quarterCluster);
        memset(buffer, 0, quarterCluster);

        for(i = 0; i < quarterCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, quarterCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "QUARCLST", quarterCluster, rc, wRc, cRc);

    h   = fopen("TWOCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWOCLST", twoCluster, rc, wRc, cRc);

    h   = fopen("TRQTCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, threeQuartersCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TRQTCLST",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = fopen("TWTQCLST", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoAndThreeQuartCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "TWTQCLST",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);

    h   = fopen("TWO1", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO1", twoCluster, rc, wRc, cRc);

    h   = fopen("TWO2", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO2", twoCluster, rc, wRc, cRc);

    h   = fopen("TWO3", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoCluster);
        memset(buffer, 0, twoCluster);

        for(i = 0; i < twoCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tDeleting \"TWO2\".\n");
    ret = unlink("TWO2");
    if(!ret) { rc = errno; }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n", "TWO3", twoCluster, rc, wRc, cRc);

    h   = fopen("FRAGTHRQ", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(threeQuartersCluster);
        memset(buffer, 0, threeQuartersCluster);

        for(i = 0; i < threeQuartersCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, threeQuartersCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tDeleting \"TWO1\".\n");
    ret = unlink("TWO1");
    if(!ret) { rc = errno; }
    printf("\tDeleting \"TWO3\".\n");
    ret = unlink("TWO3");
    if(!ret) { rc = errno; }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "FRAGTHRQ",
           threeQuartersCluster,
           rc,
           wRc,
           cRc);

    h   = fopen("FRAGSIXQ", "w+");
    rc  = 0;
    wRc = 0;
    cRc = 0;
    if(h == NULL) { rc = errno; }
    else
    {
        buffer = malloc(twoAndThreeQuartCluster);
        memset(buffer, 0, twoAndThreeQuartCluster);

        for(i = 0; i < twoAndThreeQuartCluster; i++) buffer[i] = clauniaBytes[i % CLAUNIA_SIZE];

        ret = fwrite(buffer, twoAndThreeQuartCluster, 1, h);
        if(ret < 0) { wRc = errno; }

        ret = fclose(h);
        if(ret) { cRc = errno; }
        free(buffer);
    }

    printf("\tFile name = \"%s\", size = %d, rc = %d, wRc = %d, cRc = %d\n",
           "FRAGSIXQ",
           twoAndThreeQuartCluster,
           rc,
           wRc,
           cRc);
}

void Sparse(const char *path)
{
    // Needs OS specific implementations
}

void Links(const char *path)
{
    FILE *h;
    int   ret;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("LINKS", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("LINKS");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating links.\n");

    h = fopen("TARGET", "w+");

    if(h == NULL)
    {
        printf("Error %d creating target file.\n", errno);
        return;
    }

    fprintf(h, "This is the target for the links.\n");

    fclose(h);

    ret = link("TARGET", "HARD");

    if(ret) { printf("Error %d creating hard link.\n", errno); }

    ret = symlink("TARGET", "SYMBOLIC");

    if(ret) { printf("Error %d creating symbolic link.\n", errno); }
}

void MillionFiles(const char *path)
{
    char  filename[9];
    long  pos = 0;
    FILE *h;
    int   ret;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("MILLION", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("MILLION");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating lots of files.\n");

    for(pos = 0; pos < 100000; pos++)
    {
        memset(&filename, 0, 9);
        sprintf(filename, "%08ld", pos);

        h = fopen(filename, "w+");
        if(h == NULL) { break; }

        fclose(h);
    }

    printf("\tCreated %ld files\n", pos);
}

void DeleteFiles(const char *path)
{
    char  filename[9];
    long  pos = 0;
    FILE *h;
    int   ret;

    ret = chdir(path);

    if(ret)
    {
        printf("Error %d changing to specified path.\n", errno);
        return;
    }

    ret = mkdir("DELETED", 0755);

    if(ret)
    {
        printf("Error %d creating working directory.\n", errno);
        return;
    }

    ret = chdir("DELETED");

    if(ret)
    {
        printf("Error %d changing to working directory.\n", errno);
        return;
    }

    printf("Creating and deleting files.\n");

    for(pos = 0; pos < 64; pos++)
    {
        memset(&filename, 0, 9);
        sprintf(filename, "%lX", pos);
        h = fopen(filename, "w+");
        if(h == NULL) { break; }

        fclose(h);
        unlink(filename);
    }
}

#endif
